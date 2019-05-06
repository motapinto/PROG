#include "client.h"

using namespace std;

Client::Client() { 
  this->nif = 0; 
  this->family_num = 0; 
  this->tour_packs_bought.resize(0); 
}

Client::Client(string name, string address, vector<int> tour_packs_bought, unsigned int nif, unsigned int family_num) {
    this->client_name = name;
    this->client_address.setAddress(address);
    if(verifyPacksBought(tour_packs_bought)) this->tour_packs_bought = tour_packs_bought;
    else this->tour_packs_bought.resize(0);
    this->nif = nif;
    this->family_num = family_num;

    this->checkClient();
}

int Client::packPos(int id) {
  for(size_t i = 0; i < tour_packs_bought.size(); i++)
      if(tour_packs_bought.at(i) == id)
        return id;
  
  return -1;
}

void Client::addPack(int pack_id){
  if(packPos(pack_id == -1))
    this->tour_packs_bought.push_back(pack_id);
}

void Client::removePack(int pack_id){
  if(int pos = packPos(pack_id) != -1) 
    this->tour_packs_bought.erase(tour_packs_bought.begin() + pos);
}

void Client::setName (string new_name) { 
  this->client_name = new_name; 
}

void Client::setAddress(string address) { 
  this->client_address.setAddress(address); 
}

void Client::setTourPacks(vector <int> packs) { 
  this->tour_packs_bought = packs; 
  this->checkClient();
}

void Client::setNif(unsigned int nif) { 
  this->nif = nif; 
}

void Client::setFamilyNum(unsigned int family_num) {
  this->family_num = family_num;
  this->checkClient();
}

string Client::getName(void) const{ 
  return this->client_name; 
}

Address Client::getAddress(void) const{ 
  return this->client_address; 
}

vector <int> Client::getTourPacksBought(void) const{ 
  return this->tour_packs_bought; 
}

unsigned int Client::getNif(void) const{ 
  return this->nif; 
}

unsigned int Client::getFamilyNum(void) const{ 
  return this->family_num; 
}

unsigned int Client::getNumOfBuys(void) const{ 
  return this->tour_packs_bought.size(); 
}

bool Client::verifyPacksBought(vector<int> packs){
  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = i+1; j < packs.size(); j++){
      if(packs.at(i) == packs.at(j))
        return false;
    }
  }
  return true;
}

void Client::checkClient() {

    if(this->verifyPacksBought(this->tour_packs_bought) == false)
      throw ClientException(NULL);
}

Client Client::operator = (Client client){
  this->client_name = client.getName();
  this->client_address = client.getAddress();
  this->tour_packs_bought = client.getTourPacksBought();
  this->nif = client.getNif();
  this->family_num = client.getNumOfBuys();

  return *this;
}