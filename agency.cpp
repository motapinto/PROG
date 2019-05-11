#include "agency.h"

Agency::Agency(){ 
  name.resize(0);
  url.resize(0);
  client_list.resize(0);
  tour_pack.resize(0);
  nif = 0; 
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
  for(size_t pos = 0; pos < client_list.size(); pos++){
    if(client_list.at(pos).getNif() == nif) 
      return pos;
  }
  return -1;
}

void Agency::show(std::ostream &fp) const{
  std::cout<< "Name: " << name << std::endl;
  std::cout<< "URL: " << url << std::endl;
  std::cout<< "Address: " <<  agency_address.getAddress() << std::endl;
  std::cout<< "NIF: " << nif << std::endl;
}

void Agency::addClient(std::string name, std::string address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num) {
  //Check if there is already a client with the same nif
  if(clientPos(nif) != -1)
    //ERROR
    return;
    
  if(verifyPacksBought(tour_packs_bought) == false) 
    //ERROR
    return;

  for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == tour_packs_bought.at(i))
          tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
    }
  }

  Client new_client(name, address, tour_packs_bought, nif, family_num, sumSold(tour_packs_bought));
  client_list.push_back(new_client);
}

void Agency::removeClient(unsigned int nif) {

  if(int pos = clientPos(nif) != -1) {
    for(size_t k = 0; k < client_list.at(pos).tour_packs_bought.size(); k++){ //decrement number of sold packs
      for(size_t j = 0; j < tour_pack.size(); j++){
        if(tour_pack.at(j).getPackId() == client_list.at(pos).tour_packs_bought.at(k))
            tour_pack.at(j).num_sold--;
      }
    }
  
    client_list.erase(client_list.begin()+pos);
  }
}

void Agency::changeClient(Client &client, unsigned int old_nif) {
  Client search_aux;
  int pos = clientPos(nif);

  for(size_t i = 0; i < client_list.size(); i++){
    if(client_list.at(i).nif == old_nif) continue;

    if(client_list.at(i).nif == client.nif) //ERROR
      return;
  }

  //ERROR
  if(pos == -1) return;
    
  //remove old travel packs
  for(size_t k = 0; k < client_list.at(pos).tour_packs_bought.size(); k++){ //decrement number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == client_list.at(pos).tour_packs_bought.at(k)){
            tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() - 1);
      }
    }
  }
          
  //add new travel packs
  if(verifyPacksBought(client.tour_packs_bought) == false){
    for(size_t k = 0; k < client_list.at(pos).tour_packs_bought.size(); k++){ //decrement number of sold packs
      for(size_t j = 0; j < tour_pack.size(); j++){
        if(tour_pack.at(j).getPackId() == client_list.at(pos).tour_packs_bought.at(k)){
              tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() - 1);
        }
      }
    }
    //ERROR
    return;
  } 
          
  for(size_t i = 0; i < client.tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == client.tour_packs_bought.at(i))
        tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
    }
  }

  client_list.at(pos).nif = client.nif;

  client_list.at(pos).client_name = client.client_name;
  client_list.at(pos).client_address = client.client_address;

  client_list.at(pos).tour_packs_bought = client.tour_packs_bought;
  client_list.at(pos).family_num = client.family_num;
}

void Agency::addTravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold){
  //Check if there is already a pack with the same id
  Date date_aux;

  for(size_t i = 0; i < tour_pack.size(); i++)
    if(tour_pack.at(i).getPackId() == id) 
      return;
      //throw...


  if(!verifyCities(cities)) 
    return;
    //throw...

  TravelPack pack(init_date, final_date, destination, cities, available, id, price, people_limit, num_sold);
  tour_pack.push_back(pack);
}

void Agency::changeTravelPack(TravelPack &pack, unsigned int id){

  for(size_t i= 0; i < tour_pack.size(); i++){
    if(tour_pack.at(i).getPackId() == id) {
        //ERROR
        if(!verifyCities(pack.cities)) return ;
        if(pack.num_sold > pack.people_limit) return ;
        tour_pack.at(i).destination = pack.destination;
        tour_pack.at(i).init_date = pack.init_date;
        tour_pack.at(i).final_date = pack.final_date;
        tour_pack.at(i).cities = pack.cities;
        for(size_t j = 0; j < client_list.size(); j++)
          for(size_t l = 0; l < client_list.at(j).tour_packs_bought.size(); l++)
            if(client_list.at(j).tour_packs_bought.at(l) == tour_pack.at(i).id)
              client_list.at(j).money_spent += pack.price - tour_pack.at(i).price;

        tour_pack.at(i).price = pack.getPrice();
        tour_pack.at(i).people_limit = pack.people_limit;
        tour_pack.at(i).num_sold = pack.num_sold;
    }
  }

}

void Agency::removeTravelPack(unsigned int id) {
    //Remove from agency
    for(size_t i= 0; i < tour_pack.size(); i++){
      if(tour_pack.at(i).id == id) {
        for(size_t j = 0; j < client_list.size(); j++)
          for(size_t l = 0; l < client_list.at(j).tour_packs_bought.size(); l++)
            if(client_list.at(j).tour_packs_bought.at(l) == tour_pack.at(i).id)
              client_list.at(j).money_spent -= tour_pack.at(i).price;

        tour_pack.erase(tour_pack.begin()+i);
        break;
      }
    }

    //Remove from each client
    for(size_t i= 0; i < client_list.size(); i++){
        std::vector <unsigned int> client_packs = client_list.at(i).tour_packs_bought;
        for(size_t j = 0; j < client_list.at(i).tour_packs_bought.size(); j++) {
            if(client_list.at(i).tour_packs_bought.at(j) == id) { 
                client_list.at(i).tour_packs_bought.erase(client_list.at(i).tour_packs_bought.begin()+j);
            }
        }
    }
    return;
}

bool Agency::searchClientNif(unsigned int nif, Client &client){
  for(size_t i = 0; i < client_list.size(); i++)
    if(client_list.at(i).getNif() == nif){
      client = client_list.at(i);
      return true;
    }

  return false;
}

std::vector<Client> Agency::searchClientName(std::string name){
  std::vector<Client> vec;
  for(size_t i = 0; i < client_list.size(); i++)
    if(client_list.at(i).getName() == name)
      vec.push_back(client_list.at(i));

  return vec;
}

bool Agency::searchTravelPackId(unsigned int id, TravelPack &pack){
  for(size_t i = 0; i < tour_pack.size(); i++)
    if(tour_pack.at(i).getPackId() == id){
      pack = tour_pack.at(i);
      return true;
    }

  return false;
}

std::vector <TravelPack> Agency::searchTravelPackDestination(std::string destination){
  std::vector<TravelPack> vec;
  for(size_t i = 0; i < tour_pack.size(); i++)
    if(tour_pack.at(i).getDestination() == destination)
      vec.push_back(tour_pack.at(i));

  return vec;
}

std::vector<TravelPack> Agency::searchTravelPackCity(std::string city){
  std::vector<TravelPack> vec;
  for(size_t i = 0; i < tour_pack.size(); i++){
    if(tour_pack.at(i).cities.size() == 0){
      if(tour_pack.at(i).destination == city)
        vec.push_back(tour_pack.at(i));
    }
    else
      for(size_t j = 0; j < tour_pack.at(i).cities.size(); j++)
        if(tour_pack.at(i).cities.at(j) == city){
          vec.push_back(tour_pack.at(i));
          break;
        }
  }

  return vec;
}

std::vector <TravelPack> Agency::searchTravelPackDates(std::string init_date, std::string final_date){
  std::vector<TravelPack> vec;
  Date date_init(init_date);
  Date date_final(final_date);

  if(date_init > date_final) return vec;

  
  for(size_t i = 0; i < tour_pack.size(); i++)
    if( tour_pack.at(i).getInitDate() > date_init && tour_pack.at(i).getFinalDate() > date_final)
      vec.push_back(tour_pack.at(i));

  return vec;
}

std::vector <TravelPack> Agency::searchTravelPackDates(Date init_date, Date final_date){
  std::vector<TravelPack> vec;
  Date date_init(init_date);
  Date date_final(final_date);

  if(date_init > date_final) return vec;
  
  for(size_t i = 0; i < tour_pack.size(); i++)
    if(tour_pack.at(i).getInitDate() >= date_init && tour_pack.at(i).getFinalDate() <= date_final )
      vec.push_back(tour_pack.at(i));

  return vec;
}

std::multimap<unsigned int, std::string> Agency::mostVisitedPlaces(){
  std::map <std::string, unsigned int> mp;
  std::multimap <unsigned int, std::string> multimp;

  for(size_t i = 0; i < tour_pack.size(); i++){
    tour_pack.at(i).cities = tour_pack.at(i).getCities();
    if(tour_pack.at(i).cities.size() == 0)
      mp[tour_pack.at(i).getDestination()] += tour_pack.at(i).getNumberSold();
    else
      for(size_t j = 0; j < tour_pack.at(i).cities.size(); j++)
        mp[tour_pack.at(i).cities.at(j)] += tour_pack.at(i).getNumberSold();
  }

  for(auto iterator = mp.begin(); iterator != mp.end(); iterator++)
    multimp.insert(std::pair<unsigned int, std::string>( (*iterator).second, (*iterator).first ) );

  return multimp;
}

void Agency::setName(const std::string &name){ 
  this->name = name; 
}

void Agency::setUrl(const std::string &url){ 
  this->url = url; 
}

void Agency::setAddress(const Address &address){ 
  this->agency_address = address; 
}

void Agency::setAddress(const std::string &address){ 
  this->agency_address.setAddress(address); 
}

void Agency::setTourPack(const std::vector<TravelPack> &tour_pack){ 
  this->tour_pack = tour_pack; 
}

void Agency::setClientList(const std::vector<Client> &client_list){ 
  this->client_list = client_list; 
}

void Agency::setNif(const unsigned int &nif){ 
  this->nif = nif; 
}

std::string Agency::getName(void){ 
  return name; 
}

std::string Agency::getUrl(void){ 
  return url; 
}

Address Agency::getAddress(void){ 
  return agency_address; 
}

std::vector<TravelPack> Agency::getTourPacks(void){ 
  return tour_pack; 
}

std::vector<Client> Agency::getClientList(void){ 
  return client_list; 
}

unsigned int Agency::getNif(void){ 
  return nif; 
}

unsigned int Agency::sumSold(const unsigned int nif){
  unsigned int n_sold = 0;

  for(size_t i = 0; i < client_list.size(); i++){
    if(client_list.at(i).nif == nif){
      for(size_t k = 0; k < tour_pack.size(); k++)
        for(size_t j = 0; j < client_list.at(i).tour_packs_bought.size(); j++){
          if(client_list.at(i).tour_packs_bought.at(j) == tour_pack.at(k).id)
            n_sold+= tour_pack.at(k).price;
        }
    }
  }

  return n_sold;
}

unsigned int Agency::sumSold(const std::vector<unsigned int> &tour_packs){
  unsigned int n_sold = 0;

  for(size_t k = 0; k < this->tour_pack.size(); k++)
    for(size_t j = 0; j < tour_packs.size(); j++){
      if(tour_pack.at(j).id == this->tour_pack.at(k).id)
        n_sold+= this->tour_pack.at(k).price;
    }

  return n_sold;
}

bool Agency::verifyCities(const std::vector<std::string> cities){
  for(size_t i = 0; i < cities.size(); i++){
    for(size_t j = 0; j < cities.size(); j++){
      if(i == j) continue;
      if(cities.at(i) == cities.at(j))
        return false;
    }
  }
  return true;
}

bool Agency::verifyPacks(const std::vector<unsigned int> &packs){
  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).id == packs.at(i)){
        if( !((tour_pack.at(j).num_sold + 1) <= tour_pack.at(j).people_limit) ){
          return false;
        }
      }
    }
  }

  return true;
}

bool Agency::verifyPacksBought(const std::vector<unsigned int> &packs){
  TravelPack aux;

  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = 0; j < packs.size(); j++){
      if(i == j) continue;
      if(packs.at(i) == packs.at(j))
        return false;
    }
  }

  for(size_t i = 0; i < packs.size(); i++){
      if(!searchTravelPackId(packs.at(i), aux)) return false;
  }

  return true;
}