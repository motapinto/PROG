#include "client.h"

Client::Client() { 
  this->nif = 0; 
  this->family_num = 0; 
  this->money_spent = 0;
  this->tour_packs_bought.resize(0); 
}

Client::Client(std::string name, std::string address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num, unsigned int money_spent) {
    repeatedPacks(tour_packs_bought);

    this->client_name = name;
    this->client_address.setAddress(address);
    this->tour_packs_bought = tour_packs_bought;
    this->nif = nif;
    this->family_num = family_num;
    this->money_spent = money_spent;
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
  repeatedPacks(packs);
  this->tour_packs_bought = packs; 
}

void Client::setTourPacks(std::string packs, char delim) { 
  std::vector<unsigned int> packs_bought;

  if(packs.compare("-") == 0){
    this->tour_packs_bought.resize(0); //eliminate previous values
    throw ClientException(NULL);
  } 

  if(decompose(packs, packs_bought, delim) == true){
      repeatedPacks(packs_bought);
      this->tour_packs_bought = packs_bought;
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

void Client::repeatedPacks(std::vector<unsigned int> packs) const {
  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = i+1; j < packs.size(); j++){
      if(packs.at(i) == packs.at(j))
        throw ClientException(NULL);
    }
  }
  return;
}

Client Client::operator = (Client client){
  this->client_name = client.getName();
  this->client_address = client.getAddress();
  this->tour_packs_bought = client.getTourPacksBought();
  this->nif = client.getNif();
  this->family_num = client.getNumOfBuys();

  return *this;
}

std::ostream& operator << (std::ostream& os, const Client &client){
  os << "Name: " << client.client_name << std::endl;
  os << "Address: " << client.client_address << std::endl;
  os << "Tour Packs Bought: ";
  if(client.tour_packs_bought.size() == 0) os << "None";
  else for(size_t i = 0; i < client.tour_packs_bought.size(); i++){
    os << client.tour_packs_bought.at(i) << " ";
  }
  os << std::endl;
  os << "NIF: " << client.nif << std::endl;
  os << "Family Number: " << client.family_num << std::endl;
  os << "Money Spent: " << client.money_spent << std::endl;

  return os;
}

std::ofstream& operator << (std::ofstream& os, const Client &client){
  os << client.client_name << std::endl;
  os << client.nif << std::endl;
  os << client.family_num << std::endl;
  os << client.client_address << std::endl;
  if(client.tour_packs_bought.size() != 0) {
    os << client.tour_packs_bought.at(0);
    for(size_t i = 1; i < client.tour_packs_bought.size(); i++)
      os << " ; " << client.tour_packs_bought.at(i);
    
    os << std::endl;
  }
  os << client.money_spent << std::endl;

  return os;
}

std::ifstream& operator >> (std::ifstream& is, Client &client){
  size_t line_count = 0;
  int value_check = -1;
  std::string str_aux;

  while(getline(is, str_aux) && !is.eof()){
    if(str_aux.size() > 0){
      if(str_aux.at(str_aux.size() - 1) == '\r') str_aux.pop_back();
      if(str_aux.at(0) == '\r') str_aux.erase(0, 1);
    } 
    Trim(str_aux);
    switch (line_count) {
      case 0:
        client.client_name = str_aux;
        
        break;

      case 1:
        if(string_to_int(str_aux, value_check) == false)
          throw ClientException(NULL);
        if(value_check <= -1)
          throw ClientException(NULL);

        client.nif = value_check;
        value_check = -1;        
        break;

      case 2:
        if(string_to_int(str_aux, value_check) == false)
          throw ClientException(NULL);
        if(value_check <= -1) //verify value
          throw ClientException(NULL);
         
        client.family_num = value_check;        
        value_check = -1;
        break;

      case 3:
        try{
          client.client_address.setAddress(str_aux);
        }
        catch (std::string){
          throw ClientException(NULL);
        }
        break;

      case 4:
        value_check = is.peek();
        if(value_check < '0' && value_check > '9'){
          if(string_to_int(str_aux, value_check) == false)
            throw ClientException(NULL);
          if(value_check <= -1) //verify value
            throw ClientException(NULL);
          client.money_spent = value_check;
          client.repeatedPacks(client.tour_packs_bought);
          return is;
        }
        else
          client.setTourPacks(str_aux, ';');
        break;

      case 5:
        if(string_to_int(str_aux, value_check) == false)
          throw ClientException(NULL);
        if(value_check <= -1) //verify value
          throw ClientException(NULL);
        
        client.money_spent = value_check;    
        client.repeatedPacks(client.tour_packs_bought);
        return is;
    }
  }

  throw ClientException(NULL);
  return is;
}
