#include "client.h"

Client::Client() { 
  this->nif = 0; 
  this->family_num = 0; 
  this->money_spent = 0;
  this->tour_packs_bought.resize(0); 
}

Client::Client(std::string name, std::string address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num, unsigned int money_spent) {
    checkClient(tour_packs_bought);

    this->client_name = name;
    this->client_address.setAddress(address);
    this->tour_packs_bought = tour_packs_bought;
    this->nif = nif;
    this->family_num = family_num;
    this->money_spent = money_spent;
}

void Client::show(std::ostream &fp) const {
  fp << "Name: " << client_name << std::endl;
  fp << "Address: " ; client_address.show(fp);
  fp << "Tour Packs Bought: ";
  if(tour_packs_bought.size() == 0) fp << "None";
  else for(size_t i = 0; i < tour_packs_bought.size(); i++){
    fp << tour_packs_bought.at(i) << " ";
  }
  fp << std::endl;
  fp << "NIF: " << nif << std::endl;
  fp << "Family Number: " << family_num << std::endl;
}

int Client::packPos(unsigned int id) {
  for(size_t i = 0; i < this->tour_packs_bought.size(); i++)
      if(this->tour_packs_bought.at(i) == id)
        return i;
  
  return -1;
}

void Client::addPack(unsigned int pack_id){
  if(packPos(pack_id) == -1)
    this->tour_packs_bought.push_back(pack_id);
}

void Client::removePack(int pack_id){
  if(int pos = packPos(pack_id) != -1) 
    this->tour_packs_bought.erase(tour_packs_bought.begin() + pos);
}

void Client::setName (std::string new_name) { 
  this->client_name = new_name; 
}

void Client::setAddress(std::string address) { 
  this->client_address.setAddress(address); 
}

void Client::setTourPacks(std::vector <unsigned int> packs) { 
  checkClient(packs);
  this->tour_packs_bought = packs; 
}

void Client::setTourPacks(std::string packs, char delim) { 
  std::vector<unsigned int> packs_bought;

   if(packs.compare("-") == 0){
    this->tour_packs_bought.resize(0); //eliminate previous values
    throw ClientException(NULL);
  } 

   if(decompose(packs, packs_bought, delim) == true){
    if(!repeatedPacks(packs_bought)){
      this->tour_packs_bought = packs_bought;
    }
  }
}

void Client::setNif(unsigned int nif) { 
  this->nif = nif; 
}

void Client::setFamilyNum(unsigned int family_num) {
  this->family_num = family_num;
}

void Client::setMoneySpent(unsigned int money_spent) {
  this->money_spent = money_spent;
}

std::string Client::getName(void) const{ 
  return this->client_name; 
}

Address Client::getAddress(void) const{ 
  return this->client_address; 
}

std::vector <unsigned int> Client::getTourPacksBought(void) const{ 
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

unsigned int Client::getMoneySpent(void) const{ 
  return this->money_spent; 
}

bool Client::repeatedPacks(std::vector<unsigned int> packs) const {
  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = i+1; j < packs.size(); j++){
      if(packs.at(i) == packs.at(j))
        return true;
    }
  }
  return false;
}

Client Client::operator = (Client client){
  this->client_name = client.getName();
  this->client_address = client.getAddress();
  this->tour_packs_bought = client.getTourPacksBought();
  this->nif = client.getNif();
  this->family_num = client.getNumOfBuys();

  return *this;
}

void Client::checkClient(std::vector<unsigned int> tour_packs_bought) {
  //repeated packs
  if(repeatedPacks(tour_packs_bought))
      throw ClientException(NULL);
}