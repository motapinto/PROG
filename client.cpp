#include "client.h"

Client::Client() { 
    this->nif = 0; 
    this->family_num = 0; 
    this->money_spent = 0;
}

Client::Client(std::string name, std::string address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num, unsigned int money_spent) {    
    this->client_name = name;
    this->client_address.setAddress(address);
    this->nif = nif;
    this->family_num = family_num;
    this->money_spent = money_spent;

    for(unsigned int i = 0; i < tour_packs_bought.size(); i++) {
      packs_purchased.insert(tour_packs_bought.at(i));
    }
}

void Client::setName (std::string new_name) { 
    this->client_name = new_name; 
}

void Client::setAddress(std::string address) { 
    this->client_address.setAddress(address); 
}

void Client::setTourPacks(std::vector <unsigned int> packs) { 
  packs_purchased.clear();

  for(unsigned int i = 0; i < packs.size(); i++) {
    packs_purchased.insert(packs.at(i));
  }
}

void Client::setTourPacks(std::string packs, char delim) { 
  std::vector<unsigned int> packs_bought;
  packs_purchased.clear();

  if(packs == "-"){
      return;
  } 

  if(decompose(packs, packs_bought, delim) == true){
    packs_purchased.insert(packs_bought.begin(), packs_bought.end());
  }
  else {
    throw ClientException(NULL);
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
    std::vector <unsigned int> packs;
    std::set <unsigned int>::iterator it;

    for(it = packs_purchased.begin(); it != packs_purchased.end(); it++) {
        packs.push_back(*it);
    }

    return packs; 
}

unsigned int Client::getNif(void) const{ 
    return this->nif; 
}

unsigned int Client::getFamilyNum(void) const{ 
    return this->family_num; 
}

unsigned int Client::getNumOfBuys(void) const{ 
    return this->packs_purchased.size(); 
}

unsigned int Client::getMoneySpent(void) const{ 
    return this->money_spent; 
}

Client &Client::operator = (Client client){
    client_name = client.client_name;
    client_address = client.client_address;
    packs_purchased = client.packs_purchased;
    nif = client.nif;
    family_num = client.family_num;
    money_spent = client.money_spent;

    return *this;
}

bool Client::operator == (Client client){
    return (client_name == client.client_name &&
        client_address == client.client_address &&
        packs_purchased == client.packs_purchased &&
        nif == client.nif &&
        family_num == client.family_num &&
        money_spent == client.money_spent);
}

bool Client::operator == (unsigned int nif){
  return nif == this->nif;
}



std::ostream& operator << (std::ostream& os, const Client &client){
    os << "Name: " << client.client_name << std::endl;
    os << "Address: " << client.client_address << std::endl;
    os << "Tour Packs Bought: ";
    if(client.packs_purchased.size() == 0) os << "None";
    else 
      for(auto it = client.packs_purchased.begin(); it != client.packs_purchased.end(); it++){
        os << *it << " ";
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
    if(client.packs_purchased.size() != 0) {
      for(auto it = client.packs_purchased.begin(); it != client.packs_purchased.end(); it++){
          if(it == client.packs_purchased.begin()){
            os << *it;
          }
          else 
            os << " ; " << *it;
      }
      
      os << std::endl;
    }
    os << client.money_spent << std::endl;

    return os;
}

std::ifstream& operator >> (std::ifstream& is, Client &client){
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
          if(value_check < '0' || value_check > '9'){
            if(string_to_int(str_aux, value_check) == false)
              throw ClientException(NULL);
            if(value_check <= -1) //verify value
              throw ClientException(NULL);
            client.money_spent = value_check;
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
          return is;
      }
      line_count++;
    }

    throw ClientException(NULL);
    return is;
}
