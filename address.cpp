#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include "StringFunctions.h"
#include "address.h"

using namespace std;

Address::Address() { return; } //defautl constructor

Address::Address(string street_name, string postal_code, string city, string floor_num, unsigned int door_num) {
    this->street_name = street_name;
    this->postal_code = postal_code;
    this->city = city;
    this->floor_num = floor_num;
    this->door_num = door_num;
}

bool Address::setAddress(string &address){
    vector<string> elements;
    vector<unsigned int> vec;
    int door_num;

    decompose(address, elements);
    if(elements.size() != 5)
        return false;

    this->street_name = elements[0];

    //convert door number
    if(!string_to_int(elements[1], door_num)) return false;
    else if(door_num < 0) return false;
    this->door_num    = door_num;
    this->floor_num   = elements[2];

    //verify postal code string
    if(decompose(elements[3], vec, '-') == false) return false;
    else if(vec.size() != 2) return false;
    else if(vec.at(0) > 9999) return false;
    else if(vec.at(1) > 999) return false;
    this->postal_code = elements[3];
    this->city        = elements[4];

    return true;
}

void Address::setStreet(string &street){ this->street_name = street; }
void Address::setPostalCode(string &postal_code){ this->postal_code = postal_code; }
void Address::setCity(string &city){ this->city = city; }
void Address::setFloorNum(string &floor_num){ this->floor_num = floor_num; }
void Address::setDoorNum(unsigned int door_num){ this->door_num = door_num; }

string Address::getAddressString(void){
  string address;

  address += this->street_name;
  address.append(" / ");
  address.append(to_string(this->door_num));
  address.append(" / ");
  address += this->floor_num;
  address.append(" / ");
  address += this->postal_code;
  address.append(" / ");
  address += this->city;

  return address; 
}
string Address::getStreet(void){ return this->street_name; }
string Address::getPostalCode(void){ return this->postal_code; }
string Address::getCity(void){ return this->city; }
string Address::getFloorNum(void){ return this->floor_num; }
unsigned int Address::getDoorNum(void){ return this->door_num; }

