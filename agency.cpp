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

bool Agency::addClient(std::string name, std::string address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num) {
  //Check if there is already a client with the same nif
  if(clientPos(nif) != -1)
    return false;
    
  if(verifyPacks(tour_packs_bought, family_num) == false) {
    return false;
  } 

  for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == tour_packs_bought.at(i))
          tour_pack.at(j).num_sold += family_num;
    }
  }

  Client new_client(name, address, tour_packs_bought, nif, family_num, sumSold(tour_packs_bought, family_num));
  client_list.push_back(new_client);

  return true;
}

bool Agency::removeClient(unsigned int nif) {

  if(int pos = clientPos(nif) != -1) {
    for(auto it = client_list.at(pos).packs_purchased.begin(); it != client_list.at(pos).packs_purchased.end(); it++){ 
      for(size_t j = 0; j < tour_pack.size(); j++){
        if(tour_pack.at(j).getPackId() == *it)
            tour_pack.at(j).num_sold--;
      }
    }
  
    client_list.erase(client_list.begin()+pos);
    return true;
  }

  return false;
}

bool Agency::changeClient(Client &client, unsigned int old_nif) {
  Client search_aux;
  int pos = clientPos(nif);

  if(pos == -1) return false;

  for(size_t i = 0; i < client_list.size(); i++){
    if(client_list.at(i).nif == old_nif) continue;

    if(client_list.at(i).nif == client.nif)
      return false;
  }

    
  //remove old travel packs
  for(auto it = client_list.at(pos).packs_purchased.begin(); it != client_list.at(pos).packs_purchased.end(); it++){ //decrement number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).id == *it){
            tour_pack.at(j).num_sold -= client_list.at(pos).family_num;
      }
    }
  }

  //verify new packs   
  if(verifyPacks(client.packs_purchased, client.family_num) == false){
    for(auto it = client_list.at(pos).packs_purchased.begin(); it != client_list.at(pos).packs_purchased.end(); it++){ 
      for(size_t j = 0; j < tour_pack.size(); j++){
        if(tour_pack.at(j).id == *it){
              tour_pack.at(j).num_sold +=  client_list.at(pos).family_num;
        }
      }
    }
    return false;
  } 
          
  //add new travel packs
  client.money_spent = 0;
  for(auto it = client.packs_purchased.begin(); it != client.packs_purchased.end(); it++){ 
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).id == *it){
        tour_pack.at(j).num_sold += client.family_num;
        client.money_spent += tour_pack.at(j).price * client.family_num;
      }
    }
  }

  client_list.at(pos).nif = client.nif;

  client_list.at(pos).client_name = client.client_name;
  client_list.at(pos).client_address = client.client_address;

  client_list.at(pos).packs_purchased = client.packs_purchased;
  client_list.at(pos).family_num = client.family_num;

  return true;
}

bool Agency::purchasePack(unsigned int client_nif, unsigned int pack_id){
  Client *client = NULL;
  TravelPack *pack = NULL;
  for(size_t i = 0; i < client_list.size(); i++)
    if(client_list.at(i).nif == client_nif)
      client = &client_list.at(i);
    
  if(client == NULL) return false;

  for(auto it = client->packs_purchased.begin(); it != client->packs_purchased.end(); it++)
    if(*it == pack_id)
      return false;

  for(size_t i = 0; i < tour_pack.size(); i++)
    if(tour_pack.at(i).id == pack_id)
      pack = &tour_pack.at(i);
  
  if(pack == NULL) return false;

  if(!pack->available || (pack->num_sold + client->family_num) > pack->people_limit) return false;

  if(!client->packs_purchased.insert(pack_id).second) return false;
  client->money_spent += pack->price*client->family_num;
  pack->num_sold += client->family_num;

  return true;
}

bool Agency::addTravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold){
  //Check if there is already a pack with the same id
  Date date_aux;

  for(size_t i = 0; i < tour_pack.size(); i++)
    if(tour_pack.at(i).getPackId() == id) 
      return false;


  if(!verifyCities(cities)) 
    return false;;

  TravelPack pack(init_date, final_date, destination, cities, available, id, price, people_limit, num_sold);
  tour_pack.push_back(pack);

  return true;
}

bool Agency::changeTravelPack(TravelPack &pack, unsigned int id){

  for(size_t i= 0; i < tour_pack.size(); i++){
    if(tour_pack.at(i).getPackId() == id) {
        if(!verifyCities(pack.cities)) return false;
        if(pack.num_sold > pack.people_limit) return false;
        tour_pack.at(i).destination = pack.destination;
        tour_pack.at(i).init_date = pack.init_date;
        tour_pack.at(i).final_date = pack.final_date;
        tour_pack.at(i).cities = pack.cities;
        for(size_t j = 0; j < client_list.size(); j++)
          for(auto it = client_list.at(j).packs_purchased.begin(); it != client_list.at(j).packs_purchased.end(); it++)
            if(*it == tour_pack.at(i).id)
              client_list.at(j).money_spent += pack.price - tour_pack.at(i).price;

        tour_pack.at(i).price = pack.getPrice();
        tour_pack.at(i).people_limit = pack.people_limit;
        tour_pack.at(i).num_sold = pack.num_sold;
        return true;
    }
  }
  return false;
}

bool Agency::removeTravelPack(unsigned int id) {
    //Remove from agency
    for(size_t i= 0; i < tour_pack.size(); i++){
      if(tour_pack.at(i).id == id) {

        for(size_t j = 0; j < client_list.size(); j++)
          for(auto it = client_list.at(j).packs_purchased.begin(); it != client_list.at(j).packs_purchased.end(); it++)
            if(*it == tour_pack.at(i).id){
              client_list.at(j).money_spent -= tour_pack.at(i).price;
              client_list.at(j).packs_purchased.erase(it);
            }

        tour_pack.erase(tour_pack.begin()+i);
        return true;
      }
    }
    
  return false;
}

bool Agency::searchClientNif(unsigned int nif, Client &client){
  auto it = std::find(client_list.begin(), client_list.end(), nif);

  if(it == client_list.end()) return false;

  client = *it;

  return true;
}

std::vector<Client> Agency::searchClientName(std::string name){
  std::vector<Client> vec;
  for(size_t i = 0; i < client_list.size(); i++)
    if(client_list.at(i).getName() == name)
      vec.push_back(client_list.at(i));

  return vec;
}

bool Agency::searchTravelPackId(unsigned int id, TravelPack &pack){
  auto it = std::find(tour_pack.begin(), tour_pack.end(), id);

  if(it == tour_pack.end()) return false;

  pack = *it;

  return true;
}

std::vector <TravelPack> Agency::searchTravelPackDestination(std::string destination){
  std::vector<TravelPack> vec;
  for(size_t i = 0; i < tour_pack.size(); i++)
    if(tour_pack.at(i).destination == destination)
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
  for(size_t i = 0; i < tour_pack.size(); i++){
    if(!verifyCities(tour_pack.at(i).cities))
      return; //ERROR
    for(size_t j = i + 1; j < tour_pack.size(); j++)
      if(tour_pack.at(i).id == tour_pack.at(j).id)
        return; //ERROR
  }
  
  this->tour_pack = tour_pack; 
  std::sort(this->tour_pack.begin(), this->tour_pack.end());
}

void Agency::setClientList(const std::vector<Client> &client_list){ 
  for(size_t i = 0; i < client_list.size(); i++){
    if(!verifyClientPacks(client_list.at(i).packs_purchased))
      return; //ERROR
    if(client_list.at(i).money_spent != sumSold(client_list.at(i).packs_purchased, client_list.at(i).family_num))
      return; //ERROR
    for(size_t j = i + 1; j < client_list.size(); j++)
      if(client_list.at(i).nif == client_list.at(j).nif)
        return; //ERROR
  }

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
  for(size_t i = 0; i < client_list.size(); i++){
    if(client_list.at(i).nif == nif){
      return sumSold(client_list.at(i).packs_purchased, client_list.at(i).family_num);
    }
  }

  return 0;
}

unsigned int Agency::sumSold(const std::set<unsigned int> &tour_packs, const unsigned int family_num){
  unsigned int n_sold = 0;

  for(size_t k = 0; k < this->tour_pack.size(); k++)
    for(auto it : tour_packs){
      if(it == this->tour_pack.at(k).id)
        n_sold += this->tour_pack.at(k).price * family_num;
    }

  return n_sold;
}

unsigned int Agency::sumSold(const std::vector<unsigned int> &tour_packs, const unsigned int family_num){
  unsigned int n_sold = 0;

  for(size_t k = 0; k < this->tour_pack.size(); k++)
    for(size_t j = 0; j < tour_packs.size(); j++){
      if(tour_pack.at(j).id == this->tour_pack.at(k).id)
        n_sold+= this->tour_pack.at(k).price * family_num;
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

bool Agency::verifyPacks(const std::vector<unsigned int> &packs, const unsigned int family_num){
  TravelPack aux;

  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).id == packs.at(i)){
        if( !((tour_pack.at(j).num_sold + family_num) > tour_pack.at(j).people_limit) ){
          return false;
        }
      }
    }
  }

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

bool Agency::verifyClientPacks(const std::vector<unsigned int> &packs){
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

bool Agency::verifyPacks(const std::set<unsigned int> &packs, const unsigned int family_num){
  TravelPack aux;

  for(auto it = packs.begin(); it != packs.end(); it++){
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).id == *it){
        if( !((tour_pack.at(j).num_sold + family_num) > tour_pack.at(j).people_limit) ){
          return false;
        }
      }
    }
  }

  for(auto it = packs.begin(); it != packs.end(); it++){
      if(!searchTravelPackId(*it, aux)) return false;
  }

  return true;
}

bool Agency::verifyClientPacks(const std::set<unsigned int> &packs){
  TravelPack aux;

  for(auto it = packs.begin(); it != packs.end(); it++){
      if(!searchTravelPackId(*it, aux)) return false;
  }

  return true;
}

std::ostream& operator << (std::ostream& os, const Agency &agency){
  os << "Name: " << agency.name << std::endl;
  os << "URL: " << agency.url << std::endl;
  os << "Address: " << agency.agency_address << std::endl;
  os << "NIF: " << agency.nif << std::endl;

  return os;
} 

std::ofstream& operator << (std::ofstream& os, const Agency &agency){
  os << agency.name << "\n";
  os << agency.nif << "\n";
  os << agency.url << "\n";
  os << agency.agency_address << "\n";

  return os;
} 

std::ifstream& operator >> (std::ifstream& is, Agency &agency){
  size_t line_count = 0;
  int value_check = -1;
  std::string str_aux;

  while(getline(is, str_aux)){
    if(str_aux.size() > 0){
      if(str_aux.at(str_aux.size() - 1) == '\r') str_aux.pop_back();
      if(str_aux.at(0) == '\r') str_aux.erase(0, 1);
    } 
    Trim(str_aux);
    switch (line_count) {
      case 0:
        agency.name = str_aux;
        break;

      case 1:
        if(string_to_int(str_aux, value_check) == false){
          return is; //ERROR
        } 
        if(value_check <= -1){
          return is; //ERROR
        } 
        agency.nif = value_check;
        break;

      case 2:
        agency.url = str_aux;
        break;

      case 3:
        agency.agency_address.setAddress(str_aux);
        return is;
    }
    line_count++;
  }

  //ERROR
  return is;
}