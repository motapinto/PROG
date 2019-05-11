#include "address.h"

Address::Address() { 
    this->street_name.resize(0);
    this->door_num = 0;
    this->floor_num.resize(0);
    this->postal_code.resize(0);
    this->city.resize(0);
}

Address::Address(std::string address){
    std::vector <std::string> elements;
    std::vector <unsigned int> vec;

    decompose(address, elements, '/');

    if(elements.size() != 5) {
        throw AddressException(NULL);
    }

    this->street_name = elements.at(0);
    this->door_num    = stoi(elements.at(1));
    this->floor_num   = elements.at(2);
    
    //verify postal code string
    if(decompose(elements[3], vec, '-') == false || vec.size() != 2 || vec.at(0) > 9999 || vec.at(1) > 999) 
        throw AddressException(NULL);

    this->postal_code = elements.at(3);
    this->city        = elements.at(4);
}

Address::Address(std::string street_name, std::string postal_code, std::string city, std::string floor_num, unsigned int door_num){
    this->street_name = street_name;
    this->postal_code = postal_code;
    this->city = city;
    this->floor_num = floor_num;
    this->door_num = door_num;
}

void Address::show(std::ostream &fp) const {
    fp << getAddress() << std::endl;
}

void Address::setAddress(std::string address){
    std::vector <std::string> elements;
    std::vector <unsigned int> vec;

    decompose(address, elements, '/');
    if(elements.size() != 5)
        throw AddressException(NULL);

    this->street_name = elements[0];
    this->door_num    = stoi(elements[1]);
    this->floor_num   = elements[2];

    //verify postal code string
    if(decompose(elements[3], vec, '-') == false || vec.size() != 2 || vec.at(0) > 9999 || vec.at(1) > 999) 
        throw AddressException(NULL);

    this->postal_code = elements[3];
    this->city        = elements[4];
}

std::string Address::getStreet(void) const{ 
    return this->street_name; 
}

std::string Address::getPostalCode(void) const{ 
    return this->postal_code; 
}

std::string Address::getCity(void) const{ 
    return this->city; 
}

std::string Address::getFloorNum(void) const{ 
    return this->floor_num; 
}

unsigned int Address::getDoorNum(void) const{ 
    return this->door_num; 
}

std::string Address::getAddress(void) const{
  std::string address;

  address = this->street_name + " / " + std::to_string(this->door_num) + " / " + this->floor_num  
  + " / " + this->postal_code + " / " +  this->city;

  return address; 
}

void Address::setStreet(std::string street){ 
    this->street_name = street; 
}

void Address::setPostalCode(std::string postal_code){ 
    this->postal_code = postal_code; 
}

void Address::setCity(std::string city){ 
    this->city = city; 
}

void Address::setFloorNum(std::string floor_num){ 
    this->floor_num = floor_num; 
}

void Address::setDoorNum(unsigned int door_num){
     this->door_num = door_num; 
}