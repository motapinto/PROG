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
      if(this->client_list.at(i).nif == nif) {
        for(size_t k = 0; k < tour_packs_bought.size(); k++){ //decrement number of sold packs
          for(size_t j = 0; j < tour_pack.size(); j++){
            if(tour_pack.at(j).id == tour_packs_bought.at(k)){
              if(tour_pack.at(j).num_sold > 0){
                tour_pack.at(j).num_sold--;
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
    if(this->client_list.at(i).nif == nif) return false;
    
  if(verifyPacksBought(tour_packs_bought) == false) return false;

  for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).id == tour_packs_bought.at(i)){
        if(tour_pack.at(j).num_sold < tour_pack.at(j).people_limit){
          tour_pack.at(j).num_sold++;
          break;
        }
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
    if(this->client_list.at(i).nif == nif) return false;

  if(verifyPacksBought(tour_packs_bought) == false) return false;

  for(size_t i = 0; i < tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).id == tour_packs_bought.at(i)){
        if(tour_pack.at(j).num_sold < tour_pack.at(j).people_limit){
          tour_pack.at(j).num_sold++;
          break;
        }
      }
    }
  }


  Client new_client(name, address, tour_packs_bought, nif, family_num);

  this->client_list.push_back(new_client);
  return true;
}
bool Agency::addClient(Client &client){
  //Check if there is already a client with the same nif
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).nif == client.nif) return false;
    

  if(!verifyPacksBought(client.tour_packs_bought)) return false;

  for(size_t i = 0; i < client.tour_packs_bought.size(); i++){ //increment number of sold packs
    for(size_t j = 0; j < tour_pack.size(); j++){
      if(tour_pack.at(j).id == client.tour_packs_bought.at(i)){
        if(tour_pack.at(j).num_sold < tour_pack.at(j).people_limit){
          tour_pack.at(j).num_sold++;
          break;
        }
      }
    }
  }
  this->client_list.push_back(client);
  return true;
}

bool Agency::addTravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold){
  //Check if there is already a pack with the same id
  Date init(init_date), fin(final_date);

  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).id == id) return false;

  if(!init.validSet(init_date)) return false;
  if(!fin.validSet(final_date)) return false;

  if(fin < init) return false;

  if(!verifyCities(cities)) return false;

  TravelPack pack(init, fin, destination, cities, available, id, price, people_limit, num_sold);

  this->tour_pack.push_back(pack);
  return true;
}
bool Agency::addTravelPack(Date &init_date, Date &final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold){
  //Check if there is already a pack with the same id

  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).id == id) return false;

  if(final_date < init_date) return false;

  if(!verifyCities(cities)) return false;


  TravelPack pack(init_date, final_date, destination, cities, available, id, price, people_limit, num_sold);

  this->tour_pack.push_back(pack);
  return true;
}
bool Agency::addTravelPack(TravelPack pack){
  //Check if there is already a pack with the same id
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).id == pack.id) return false;

  if(pack.final_date < pack.init_date) return false;

  if(!verifyCities(pack.cities)) return false;

  this->tour_pack.push_back(pack);
  return true;
}

bool Agency::changeClient(Client &client, unsigned int nif) {
  Client search_aux;

  for(size_t i= 0; i < this->client_list.size(); i++){
    if(this->client_list.at(i).nif == nif) {

        if(client.nif != this->client_list.at(i).nif)
          if(searchClientNif(client.nif, search_aux))
            return false;

        if(!verifyPacksBought(client.tour_packs_bought)) return false;
              
        //remove old travel packs
        for(size_t k = 0; k < this->client_list.at(i).tour_packs_bought.size(); k++){ //decrement number of sold packs
          for(size_t j = 0; j < tour_pack.size(); j++){
            if(tour_pack.at(j).id == this->client_list.at(i).tour_packs_bought.at(k)){
              if(tour_pack.at(j).num_sold > 0){
                tour_pack.at(j).num_sold--;
                break;
              }
            }
          }
        }
        //add new travel packs

        for(size_t i = 0; i < client.tour_packs_bought.size(); i++){ //increment number of sold packs
          for(size_t j = 0; j < tour_pack.size(); j++){
            if(tour_pack.at(j).id == client.tour_packs_bought.at(i)){
              if(tour_pack.at(j).num_sold < tour_pack.at(j).people_limit){
                tour_pack.at(j).num_sold++;
                break;
              }
            }
          }
        }

        this->client_list.at(i) = client;
        return true;
      }
  }
  return false;
}

bool Agency::changeClient(Client &client, string name) {
  Client search_aux;

  for(size_t i= 0; i < this->client_list.size(); i++)
      if(this->client_list.at(i).client_name == name) {

          if(client.nif != this->client_list.at(i).nif)
            if(searchClientNif(client.nif, search_aux))
              return false;

          if(!verifyPacksBought(client.tour_packs_bought)) return false;
               
          //remove old travel packs
          for(size_t k = 0; k < this->client_list.at(i).tour_packs_bought.size(); k++){ //decrement number of sold packs
            for(size_t j = 0; j < tour_pack.size(); j++){
              if(tour_pack.at(j).id == this->client_list.at(i).tour_packs_bought.at(k)){
                if(tour_pack.at(j).num_sold > 0){
                  tour_pack.at(j).num_sold--;
                  break;
                }
              }
            }
          }
          //add new travel packs

          for(size_t i = 0; i < client.tour_packs_bought.size(); i++){ //increment number of sold packs
            for(size_t j = 0; j < tour_pack.size(); j++){
              if(tour_pack.at(j).id == client.tour_packs_bought.at(i)){
                if(tour_pack.at(j).num_sold < tour_pack.at(j).people_limit){
                  tour_pack.at(j).num_sold++;
                  break;
                }
              }
            }
          }

          this->client_list.at(i) = client;
          return true;
      }
  return false;
}

bool Agency::changeTravelPack(TravelPack &pack, unsigned int id){

  for(size_t i= 0; i < this->tour_pack.size(); i++){
      if(this->tour_pack.at(i).getPackId() == id) {
          if(!verifyCities(pack.cities)) return false;
          //Initial date is higher than final date
          if(pack.init_date > pack.final_date) return false; 
          if(pack.num_sold > pack.people_limit) return false;
          this->tour_pack.at(i).destination = pack.destination;
          this->tour_pack.at(i).init_date = pack.init_date;
          this->tour_pack.at(i).final_date = pack.final_date;
          this->tour_pack.at(i).cities = pack.cities;
          this->tour_pack.at(i).available = pack.available;
          this->tour_pack.at(i).price = pack.price;
          this->tour_pack.at(i).people_limit = pack.people_limit;
          this->tour_pack.at(i).num_sold = pack.num_sold;
          return true;
      }
  }
  return false;
}

void Agency::removeTravelPack(unsigned int id) {
    //Remove from agency
    for(size_t i= 0; i < this->tour_pack.size(); i++){
        if(this->tour_pack.at(i).id == id) {
             this->tour_pack.erase(this->tour_pack.begin()+i);
            break;
        }
    }

    //Remove from each client
    for(size_t i= 0; i < this->client_list.size(); i++){
        for(size_t j = 0; j < this->client_list.at(i).tour_packs_bought.size(); j++) {
            if(this->client_list.at(i).tour_packs_bought.at(j) == id) { 
                this->client_list.at(i).getTourPacksBought().erase(this->client_list.at(i).getTourPacksBought().begin()+j);
            }
        }
    }
    return;
}

bool Agency::searchClientNif(unsigned int nif, Client &client){
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).nif == nif){
      client = this->client_list.at(i);
      return true;
    }

  return false;
}
vector<Client> Agency::searchClientName(string name){
  vector<Client> vec;
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).client_name == name)
      vec.push_back(this->client_list.at(i));

  return vec;
}
vector<Client> Agency::searchClientAddress(string address){
  vector<Client> vec;
  for(size_t i = 0; i < this->client_list.size(); i++)
    if(this->client_list.at(i).client_address.getAddressString() == address)
      vec.push_back(this->client_list.at(i));

  return vec;
}

bool Agency::searchTravelPackId(unsigned int id, TravelPack &pack){
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).id == id){
      pack = this->tour_pack.at(i);
      return true;
    }

  return false;
}
vector<TravelPack> Agency::searchTravelPackDestination(string destination){
  vector<TravelPack> vec;
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if(this->tour_pack.at(i).destination == destination)
      vec.push_back(this->tour_pack.at(i));

  return vec;
}
vector<TravelPack> Agency::searchTravelPackDates(string init_date, string final_date){
  vector<TravelPack> vec;

  Date init(init_date), fin(final_date);
  if(!init.validSet(init_date)) return vec;
  if(!fin.validSet(final_date)) return vec;
  
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if( this->tour_pack.at(i).init_date >= init_date && this->tour_pack.at(i).final_date <= final_date )
      vec.push_back(this->tour_pack.at(i));

  return vec;
}
vector<TravelPack> Agency::searchTravelPackDates(Date init_date, Date final_date){
  vector<TravelPack> vec;

  if(init_date > final_date) return vec;
  
  for(size_t i = 0; i < this->tour_pack.size(); i++)
    if( this->tour_pack.at(i).init_date >= init_date && this->tour_pack.at(i).final_date <= final_date )
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