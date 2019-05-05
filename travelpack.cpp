#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include "StringFunctions.h"
#include "travelpack.h"

using namespace std;

TravelPack::TravelPack(){
  this->available = false; 
  this->id = 0; 
  this->price = 0; 
  this->people_limit = 0;
  this->num_sold = 0;
}

TravelPack::TravelPack(string init_date, string final_date, string destination, vector<string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold) {
    setDate(this->init_date, init_date);
    setDate(this->final_date, final_date);
    this->destination = destination;
    this->cities = cities;
    this->available = available;
    this->id = id;
    this->price = price;
    this->people_limit = people_limit;
    this->num_sold = num_sold;
} 

TravelPack::TravelPack(Date &init_date, Date &final_date, string destination, vector<string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold){
    this->init_date = init_date;
    this->final_date = final_date;
    this->destination = destination;
    this->cities = cities;
    this->available = available;
    this->id = id;
    this->price = price;
    this->people_limit = people_limit;
    this->num_sold = num_sold;
}

int TravelPack::readPack(istream &input){ //reads from input file and fills client class
    vector<string> elements;
    string str_aux;
    
    input >> this->id; //Number of family members
    input.ignore(); //ignore \n
    if(input)
      return 1;

    getline(input, str_aux); //Inicial date
    setDate(this->init_date, str_aux);
    if(input)
      return 2;

    getline(input, str_aux); //Final date
    setDate(this->final_date, str_aux);
    if(input)
      return 3;

    getline(input, str_aux);
    decompose(str_aux, elements, '-');
    if(elements.size() != 2)
      return 4;
    this->destination = elements.at(0);

    decompose(elements.at(1), elements, ',');
    for(int i = 0; i < 0; i++)
      this->cities.push_back(elements.at(i));
    if(input) //test input
      return 5;

    input >> this->price; //Price of the pack
    input.ignore(); //ignore \n
    if(input)
      return 6;

    input >> this->people_limit; //Number of people that could go
    input.ignore(); //ignore \n
    if(input)
      return 7;

    input >> this->num_sold; //Number of people that have bought
    input.ignore(); //ignore \n
    if(input)
      return 8;
    

    return 0;
}


Date TravelPack::getInitDate(void){ return this->init_date; }
Date TravelPack::getFinalDate(void){ return this->final_date; }
string TravelPack::getDestination(void){ return this->destination; }
vector<string> TravelPack::getCities(void){ return this->cities; }
bool TravelPack::getAvailability(void){ return this->available; }
unsigned int TravelPack::getPackId(void) { return this->id; }
unsigned int TravelPack::getPrice(void){ return this->price; }
unsigned int TravelPack::getPeopleLimit(void){ return this->people_limit; }
unsigned int TravelPack::getNumberSold(void){ return this->num_sold; }
int TravelPack::setInitDate(string init_date){ return setDate(this->init_date, init_date); }
int TravelPack::setFinalDate(string final_date){ return setDate(this->final_date, final_date); }
void TravelPack::setInitDate(Date init_date){ this->init_date = init_date; }
void TravelPack::setFinalDate(Date final_date){ this->final_date = final_date; }
void TravelPack::setDestination(string destination){ this->destination = destination; }
void TravelPack::setCities(vector<string> cities){ this->cities = cities; }
void TravelPack::setAvailability(bool available) { this->available = available; }
void TravelPack::setPackId(unsigned int id){ this->id = id; }
void TravelPack::setPrice(unsigned int price){ this->price = price; }
void TravelPack::setPeopleLimit(unsigned int people_limit){ this->people_limit = people_limit; }
void TravelPack::setNumberSold(unsigned int num_sold){ this->num_sold = num_sold; }


bool TravelPack::verifyCities(vector<string> cities){
  for(size_t i = 0; i < cities.size(); i++){
    for(size_t j = 0; j < cities.size(); j++){
      if(i == j) continue;
      if(cities.at(i) == cities.at(j))
        return false;
    }
  }
  return true;
}

TravelPack TravelPack::operator = (TravelPack pack){
  this->init_date = pack.getInitDate();
  this->final_date = pack.getFinalDate();
  this->destination = pack.getDestination();
  this->cities = pack.getCities();
  this->available = pack.getAvailability();
  this->id = pack.getPackId();
  this->price = pack.getPrice();
  this->people_limit = pack.getPeopleLimit();
  this->num_sold = pack.getNumberSold();

  return *this;
}
