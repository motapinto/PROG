#include "agency.h"

Agency::Agency(){ 
  this->name.resize(0);
  this->url.resize(0);
  this->client_list.resize(0);
  this->tour_pack.resize(0);
  this->nif = 0; 
}

Agency::Agency(std::string name, std::string url, std::string agency_address, std::vector <TravelPack> tour_pack, std::vector <Client> client_list, unsigned int nif) {
    this->name = name;
    this->url = url;
    this->nif = nif;
    this->agency_address.setAddress(agency_address);
    this->tour_pack = tour_pack;
    this->client_list = client_list;
}

int Agency::clientPos(unsigned int nif) {
  for(size_t pos = 0; pos < this->client_list.size(); pos++){
    if(this->client_list.at(pos).getNif() == nif) 
      return pos;
  }
  return -1;
}

void Agency::addClient(std::string name, std::string address, std::vector<int> tour_packs_bought, unsigned int nif, unsigned int family_num) {
  //Check if there is already a client with the same nif
  if(clientPos(nif) != -1)
    return;
    
  if(verifyPacksBought(tour_packs_bought) == false) 
    return;

  for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == tour_packs_bought.at(i)){
        if(tour_pack.at(j).getNumberSold() < tour_pack.at(j).getPeopleLimit()){
          tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
          break;
        }
      }
    }
  }

  Client new_client(name, address, tour_packs_bought, nif,family_num);
  this->client_list.push_back(new_client);
}

void Agency::removeClient(unsigned int nif) {
  std::vector <int> tour_packs_bought;


  if(int pos = clientPos(nif) != -1) {
    tour_packs_bought = this->client_list.at(pos).getTourPacksBought();

    for(size_t k = 0; k < tour_packs_bought.size(); k++){ //decrement number of sold packs
          for(size_t j = 0; j < tour_pack.size(); j++){
            if(tour_pack.at(j).getPackId() == tour_packs_bought.at(k)){
              if(tour_pack.at(j).getNumberSold() > 0){
                tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() - 1);
                break;
              }
            }
          }
        }
  
    this->client_list.erase(this->client_list.begin()+pos);
  }
}

void Agency::changeClient(Client &client, unsigned int nif) {
  Client search_aux;
  std::vector<int> tour_packs_bought;
  int pos;
  

  if((pos = clientPos(nif)) == -1) {
    this->client_list.at(pos).setNif(client.getNif());
  }

  this->client_list.at(pos).setName(client.getName());
  this->client_list.at(pos).setAddress(client.getAddress().getAddress());

  
  //remove old travel packs
  tour_packs_bought = this->client_list.at(pos).getTourPacksBought();
  for(size_t k = 0; k < tour_packs_bought.size(); k++){ //decrement number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == tour_packs_bought.at(k)){
        if(tour_pack.at(j).getNumberSold() > 0){
            tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() - 1);
            break;
        }
      }
    }
  }
          
  //add new travel packs
  tour_packs_bought = client.getTourPacksBought();
  if(verifyPacksBought(tour_packs_bought) == false) 
    return ;
          
  for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == tour_packs_bought.at(i)){
        if(tour_pack.at(j).getNumberSold() < tour_pack.at(j).getPeopleLimit()){
          tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
          break;
        }
      }
    }
  }
          
  this->client_list.at(pos).setTourPacks(client.getTourPacksBought());
  this->client_list.at(pos).setFamilyNum(client.getFamilyNum());
}

void Agency::addTravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, int id, unsigned int price, unsigned int people_limit, unsigned int num_sold){
  //Check if there is already a pack with the same id
  Date date_aux;

  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getPackId() == id) 
      return;
      //throw...


  if(!verifyCities(cities)) 
    return;
    //throw...

  TravelPack pack(init_date, final_date, destination, cities, available, id, price, people_limit, num_sold);
  this->tour_pack.push_back(pack);
}

void Agency::changeTravelPack(TravelPack &pack, int id){

  for(size_t i= 0; i < this->tour_pack.size(); i++){
      if(this->tour_pack.at(i).getPackId() == id) {
          this->tour_pack.at(i).setDestination(pack.getDestination());
          //Initial date is higher than final date
          this->tour_pack.at(i).setInitDate(pack.getInitDate().getDate());
          this->tour_pack.at(i).setFinalDate(pack.getFinalDate().getDate());
          if(!verifyCities(pack.getCities())) return ;
          //throw...
          this->tour_pack.at(i).setCities(pack.getCities());
          this->tour_pack.at(i).setPrice(pack.getPrice());
          if(pack.getNumberSold() > pack.getPeopleLimit()) return ;
          //throw...
          this->tour_pack.at(i).setPeopleLimit(pack.getPeopleLimit());
          this->tour_pack.at(i).setNumberSold(pack.getNumberSold());
      }
  }
}

void Agency::removeTravelPack(int id) {
    //Remove from agency
    int pack_id;
    for(size_t i= 0; i < this->tour_pack.size(); i++){
        pack_id = this->tour_pack.at(i).getPackId();
        if(pack_id == id) {
             this->tour_pack.erase(this->tour_pack.begin()+i);
            break;
        }
    }

    //Remove from each client
    for(size_t i= 0; i < this->client_list.size(); i++){
        std::vector <int> client_packs = this->client_list.at(i).getTourPacksBought();
        for(size_t j = 0; j < client_packs.size(); j++) {
            if(client_packs.at(j) == id) { 
                this->client_list.at(i).getTourPacksBought().erase(this->client_list.at(i).getTourPacksBought().begin()+j);
            }
        }
    }
    return;
}

bool Agency::searchTravelPackId(int id, TravelPack &pack){
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getPackId() == id){
      pack = this->tour_pack.at(i);
      return true;
    }

  return false;
}

std::vector <TravelPack> Agency::searchTravelPackDestination(std::string destination){
  std::vector<TravelPack> vec;
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getDestination() == destination)
      vec.push_back(this->tour_pack.at(i));

  return vec;
}

std::vector <TravelPack> Agency::searchTravelPackDates(std::string init_date, std::string final_date){
  std::vector<TravelPack> vec;
  Date date_init(init_date);
  Date date_final(final_date);

  if(date_init > date_final) return vec;

  
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if( this->tour_pack.at(i).getInitDate() > date_init && this->tour_pack.at(i).getFinalDate() > date_final)
      vec.push_back(this->tour_pack.at(i));

  return vec;
}

std::vector <TravelPack> Agency::searchTravelPackDates(Date init_date, Date final_date){
  std::vector<TravelPack> vec;
  Date date_init(init_date);
  Date date_final(final_date);

  if(date_init > date_final) return vec;
  
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getInitDate() >= date_init && this->tour_pack.at(i).getFinalDate() <= date_final )
      vec.push_back(this->tour_pack.at(i));

  return vec;
}

void Agency::setName(std::string name){ 
  this->name = name; 
}

void Agency::setUrl(std::string url){ 
  this->url = url; 
}

void Agency::setAddress(Address address){ 
  this->agency_address = address; 
}

void Agency::setAddress(std::string address){ 
  this->agency_address.setAddress(address); 
}

void Agency::setTourPack(std::vector<TravelPack> tour_pack){ 
  this->tour_pack = tour_pack; 
}

void Agency::setClientList(std::vector<Client> client_list){ 
  this->client_list = client_list; 
}

void Agency::setNif(unsigned int nif){ 
  this->nif = nif; 
}

std::string Agency::getName(void){ 
  return this->name; 
}

std::string Agency::getUrl(void){ 
  return this->url; 
}

Address Agency::getAddress(void){ 
  return this->agency_address; 
}

std::vector<TravelPack> Agency::getTourPacks(void){ 
  return this->tour_pack; 
}

std::vector<Client> Agency::getClientList(void){ 
  return this->client_list; 
}

unsigned int Agency::getNif(void){ 
  return this->nif; 
}

bool Agency::verifyCities(std::vector<std::string> cities){
  for(size_t i = 0; i < cities.size(); i++){

    for(size_t j = 0; j < cities.size(); j++){
      if(i == j) continue;
      if(cities.at(i) == cities.at(j))
        return false;
    }
  }
  return true;
}

bool Agency::verifyPacksBought(std::vector<int> packs){
  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = 0; j < packs.size(); j++){
      if(i == j) continue;
      if(packs.at(i) == packs.at(j))
        return false;
    }
  }
  return true;
}