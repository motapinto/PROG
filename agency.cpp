#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include "StringFunctions.h"
#include "agency.h"

using namespace std;

Agency::Agency(string name, string url, Address agency_address, vector<TravelPack> tour_pack, vector<Client> client_list, unsigned int nif) {
    this->name = name;
    this->url = url;
    this->nif = nif;
    this->agency_address = agency_address;
    this->tour_pack = tour_pack;
    this->client_list = client_list;
}

Agency::Agency(){ this->nif = 0; }

void Agency::removeClient(unsigned int nif) {
  vector <unsigned int> tour_packs_bought;

  for(size_t i= 0; i < this->client_list.size(); i++){
      if(this->client_list.at(i).getNif() == nif) {
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
        this->client_list.erase(this->client_list.begin()+i);
        break;
      }
  }
  return;
}

bool Agency::addClient(string name, string address, vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num) {
  //Check if there is already a client with the same nif
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).getNif() == nif) return false;
    
  if(verifyPacksBought(tour_packs_bought) == false) return false;

  for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == tour_packs_bought.at(i)){
        if(tour_pack.at(j).getNumberSold() < tour_pack.at(j).getPeopleLimit()){
          tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
          break;
        }
        else 
          return false;
      }
    }
  }

  Client new_client(name, address, tour_packs_bought, nif,family_num);

  this->client_list.push_back(new_client);
  return true;
}
bool Agency::addClient(string name, Address address, vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num) {
  //Check if there is already a client with the same nif
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).getNif() == nif) return false;

  if(verifyPacksBought(tour_packs_bought) == false) return false;

  for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == tour_packs_bought.at(i)){
        if(tour_pack.at(j).getNumberSold() < tour_pack.at(j).getPeopleLimit()){
          tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
          break;
        }
        else 
          return false;
      }
    }
  }


  Client new_client(name, address, tour_packs_bought, nif, family_num);

  this->client_list.push_back(new_client);
  return true;
}
bool Agency::addClient(Client client){
  vector<unsigned int> packs_bought;
  //Check if there is already a client with the same nif
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).getNif() == client.getNif()) return false;
    
  packs_bought = client.getTourPacksBought();

  if(verifyPacksBought(packs_bought) == false) return false;

  for(size_t i = 0; i < packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).getPackId() == packs_bought.at(i)){
        if(tour_pack.at(j).getNumberSold() < tour_pack.at(j).getPeopleLimit()){
          tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
          break;
        }
        else 
          return false;
      }
    }
  }
  this->client_list.push_back(client);
  return true;
}

bool Agency::addTravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold){
  //Check if there is already a pack with the same id
  Date date_aux;
  int final_date_val;
  int init_date_val;

  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getPackId() == id) return false;

  if(!setDate(date_aux, final_date))return false;
  final_date_val = getIntDate(date_aux);

  if(!setDate(date_aux, init_date))return false;
  init_date_val = getIntDate(date_aux);

  if(final_date_val < init_date_val) return false;

  if(!verifyCities(cities)) return false;

  TravelPack pack(init_date, final_date, destination, cities, available, id, price, people_limit, num_sold);

  this->tour_pack.push_back(pack);
  return true;
}
bool Agency::addTravelPack(Date &init_date, Date &final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold){
  //Check if there is already a pack with the same id
  int final_date_val;
  int init_date_val;

  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getPackId() == id) return false;

  final_date_val = getIntDate(final_date);
  init_date_val = getIntDate(init_date);

  if(final_date_val < init_date_val) return false;

  if(!verifyCities(cities)) return false;


  TravelPack pack(init_date, final_date, destination, cities, available, id, price, people_limit, num_sold);

  this->tour_pack.push_back(pack);
  return true;
}
bool Agency::addTravelPack(TravelPack pack){
  //Check if there is already a pack with the same id
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getPackId() == pack.getPackId()) return false;

  int final_date_val;
  int init_date_val;

  final_date_val = getIntDate(pack.getFinalDate());
  init_date_val = getIntDate(pack.getInitDate());

  if(final_date_val < init_date_val) return false;

  if(!verifyCities(pack.getCities())) return false;

  this->tour_pack.push_back(pack);
  return true;
}

bool Agency::changeClient(Client &client, unsigned int nif) {
  Client search_aux;
  vector<unsigned int> tour_packs_bought;

  for(size_t i= 0; i < this->client_list.size(); i++){
      if(this->client_list.at(i).getNif() == nif) {
          if(client.getNif() != nif){
            if(searchClientNif(client.getNif(), search_aux) == false)
              this->client_list.at(i).setNif(client.getNif());
            else 
              return false;
          }
          this->client_list.at(i).setName(client.getName());
          this->client_list.at(i).setAddress(client.getAddress());
          //remove old travel packs
          tour_packs_bought = this->client_list.at(i).getTourPacksBought();
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
          if(verifyPacksBought(tour_packs_bought) == false) return false;
          
          for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
            for(size_t j = 0; j < tour_pack.size(); j++){
              if(tour_pack.at(j).getPackId() == tour_packs_bought.at(i)){
                if(tour_pack.at(j).getNumberSold() < tour_pack.at(j).getPeopleLimit()){
                  tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
                  break;
                }
                else 
                  return false;
              }
            }
          }
          this->client_list.at(i).setTourPacks(client.getTourPacksBought());
          this->client_list.at(i).setFamilyNum(client.getFamilyNum());
          return true;
      }
  }
  return false;
}

bool Agency::changeClient(Client &client, string name) {
  Client search_aux;
  vector<unsigned int> tour_packs_bought;

  for(size_t i= 0; i < this->client_list.size(); i++)
      if(this->client_list.at(i).getName() == name) {
          if(client.getNif() != nif){
            if(searchClientNif(client.getNif(), search_aux) == false)
              this->client_list.at(i).setNif(client.getNif());
            else 
              return false;
          }     
          this->client_list.at(i).setName(client.getName());
          this->client_list.at(i).setNif(client.getNif());
          this->client_list.at(i).setAddress(client.getAddress());
          //remove old travel packs
          tour_packs_bought = this->client_list.at(i).getTourPacksBought();
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
          if(verifyPacksBought(tour_packs_bought) == false) return false;

          for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
            for(size_t j = 0; j < tour_pack.size(); j++){
              if(tour_pack.at(j).getPackId() == tour_packs_bought.at(i)){
                if(tour_pack.at(j).getNumberSold() < tour_pack.at(j).getPeopleLimit()){
                  tour_pack.at(j).setNumberSold(tour_pack.at(j).getNumberSold() + 1);
                  break;
                }
                else 
                  return false;
              }
            }
          }
          this->client_list.at(i).setTourPacks(client.getTourPacksBought());
          this->client_list.at(i).setFamilyNum(client.getFamilyNum());
          return true;
      }
  return false;
}

bool Agency::changeTravelPack(TravelPack &pack, unsigned int id){

  for(size_t i= 0; i < this->tour_pack.size(); i++){
      if(this->tour_pack.at(i).getPackId() == id) {
          this->tour_pack.at(i).setDestination(pack.getDestination());
          //Initial date is higher than final date
          if(getIntDate(pack.getInitDate()) > getIntDate(pack.getFinalDate())) return false; 
          this->tour_pack.at(i).setInitDate(pack.getInitDate());
          this->tour_pack.at(i).setFinalDate(pack.getFinalDate());
          if(!verifyCities(pack.getCities())) return false;
          this->tour_pack.at(i).setCities(pack.getCities());
          this->tour_pack.at(i).setAvailability(pack.getAvailability());
          this->tour_pack.at(i).setPrice(pack.getPrice());
          if(pack.getNumberSold() > pack.getPeopleLimit()) return false;
          this->tour_pack.at(i).setPeopleLimit(pack.getPeopleLimit());
          this->tour_pack.at(i).setNumberSold(pack.getNumberSold());
          return true;
      }
  }
  return false;
}

void Agency::removeTravelPack(unsigned int id) {
    //Remove from agency
    unsigned int pack_id;
    for(size_t i= 0; i < this->tour_pack.size(); i++){
        pack_id = this->tour_pack.at(i).getPackId();
        if(pack_id == id) {
             this->tour_pack.erase(this->tour_pack.begin()+i);
            break;
        }
    }

    //Remove from each client
    for(size_t i= 0; i < this->client_list.size(); i++){
        vector <unsigned int> client_packs = this->client_list.at(i).getTourPacksBought();
        for(size_t j = 0; j < client_packs.size(); j++) {
            if(client_packs.at(j) == id) { 
                this->client_list.at(i).getTourPacksBought().erase(this->client_list.at(i).getTourPacksBought().begin()+j);
            }
        }
    }
    return;
}

bool Agency::searchClientNif(unsigned int nif, Client &client){
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).getNif() == nif){
      client = this->client_list.at(i);
      return true;
    }

  return false;
}
vector<Client> Agency::searchClientName(string name){
  vector<Client> vec;
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).getName() == name)
      vec.push_back(this->client_list.at(i));

  return vec;
}
vector<Client> Agency::searchClientAddress(string address){
  vector<Client> vec;
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).getAddress().getAddressString() == address)
      vec.push_back(this->client_list.at(i));

  return vec;
}

bool Agency::searchTravelPackId(unsigned int id, TravelPack &pack){
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getPackId() == id){
      pack = this->tour_pack.at(i);
      return true;
    }

  return false;
}
vector<TravelPack> Agency::searchTravelPackDestination(string destination){
  vector<TravelPack> vec;
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).getDestination() == destination)
      vec.push_back(this->tour_pack.at(i));

  return vec;
}
vector<TravelPack> Agency::searchTravelPackDates(string init_date, string final_date){
  vector<TravelPack> vec;
  Date date_aux; //used to compare
  setDate(date_aux, init_date);
  int init_date_int = getIntDate(date_aux); 
  setDate(date_aux, final_date);
  int final_date_int = getIntDate(date_aux); 
  
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if( getIntDate(this->tour_pack.at(i).getInitDate()) > init_date_int && getIntDate(this->tour_pack.at(i).getFinalDate()) > final_date_int )
      vec.push_back(this->tour_pack.at(i));

  return vec;
}
vector<TravelPack> Agency::searchTravelPackDates(Date init_date, Date final_date){
  vector<TravelPack> vec;
  int init_date_int = getIntDate(init_date); 
  int final_date_int = getIntDate(final_date); 

  if(init_date_int > final_date_int) return vec;
  
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if( getIntDate(this->tour_pack.at(i).getInitDate()) >= init_date_int && getIntDate(this->tour_pack.at(i).getFinalDate()) <= final_date_int )
      vec.push_back(this->tour_pack.at(i));

  return vec;
}

void Agency::setName(string name){ this->name = name; }
void Agency::setUrl(string url){ this->url = url; }
void Agency::setAddress(Address address){ this->agency_address = address; }
bool Agency::setAddress(string address){ return this->agency_address.setAddress(address); }
void Agency::setTourPack(vector<TravelPack> tour_pack){ this->tour_pack = tour_pack; }
void Agency::setClientList(vector<Client> client_list){ this->client_list = client_list; }
void Agency::setNif(unsigned int nif){ this->nif = nif; }
string Agency::getName(void){ return this->name; }
string Agency::getUrl(void){ return this->url; }
Address Agency::getAddress(void){ return this->agency_address; }
vector<TravelPack> Agency::getTourPacks(void){ return this->tour_pack; }
vector<Client> Agency::getClientList(void){ return this->client_list; }
unsigned int Agency::getNif(void){ return this->nif; }


bool Agency::verifyCities(vector<string> cities){
  for(size_t i = 0; i < cities.size(); i++){
    for(size_t j = 0; j < cities.size(); j++){
      if(i == j) continue;
      if(cities.at(i) == cities.at(j))
        return false;
    }
  }
  return true;
}

bool Agency::verifyPacksBought(vector<unsigned int> packs){
  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = 0; j < packs.size(); j++){
      if(i == j) continue;
      if(packs.at(i) == packs.at(j))
        return false;
    }
  }
  return true;
}