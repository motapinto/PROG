#include "address.h"

Address::Address() { 
    this->door_num = 0;
}

Address::Address(std::string address){
    checkAddress(address, this->street_name, this->postal_code, this->city, this->floor_num, this->door_num);
}

Address::Address(std::string street_name, std::string postal_code, std::string city, std::string floor_num, unsigned int door_num){
    std::string address;

    address = street_name + " / " + std::to_string(door_num) + " / " + floor_num  
    + " / " + postal_code + " / " +  city;

    checkAddress(address, this->street_name, this->postal_code, this->city, this->floor_num, this->door_num);
}

std::string Address::getAddress(void) const{
  std::string address;

  address = this->street_name + " / " + std::to_string(this->door_num) + " / " + this->floor_num  
  + " / " + this->postal_code + " / " +  this->city;

  return address; 
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

void Address::setAddress(std::string address){
    checkAddress(address, this->street_name, this->postal_code, this->city, this->floor_num, this->door_num);
}

void Address::setStreet(std::string street){ 
    this->street_name = street; 
}

void Address::setPostalCode(std::string postal_code){ 
    std::string address;

    address = this->street_name + " / " + std::to_string(this->door_num) + " / " + this->floor_num  
    + " / " + postal_code + " / " +  this->city;

    checkAddress(address, this->street_name, postal_code, this->city, this->floor_num, this->door_num);
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

Address& Address::operator = (const Address address){
  street_name = address.street_name;
  postal_code = address.postal_code;
  city = address.city;
  floor_num = address.floor_num;
  door_num = address.door_num;

  return *this;
}

bool Address::operator == (const Address address){
  return(  street_name == address.street_name &&
        postal_code == address.postal_code &&
        city == address.city &&
        floor_num == address.floor_num &&
        door_num == address.door_num);
}

std::ostream& operator << (std::ostream& os, const Address &address){
  os << address.street_name << " / " << address.door_num << " / " << address.floor_num << " / " << address.postal_code << " / " << address.city;

  return os;
}

void Address::checkAddress(std::string &address, std::string &street_name, std::string &postal_code, std::string &city, std::string &floor_num, unsigned int &door_num) const{
    std::vector <std::string> elements;
    std::vector <unsigned int> vec;

    decompose(address, elements, '/');
    if(elements.size() != 5)
        throw AddressException(NULL);

    street_name = elements.at(0);
    door_num    = stoi(elements.at(1));
    floor_num   = elements.at(2);

    //verify postal code string
    if(decompose(elements[3], vec, '-') == false || vec.size() != 2 || vec.at(0) > 9999 || vec.at(1) > 999) 
        throw AddressException(NULL);

    postal_code = elements.at(3);
    city        = elements.at(4);
}

