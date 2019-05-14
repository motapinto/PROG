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
  checkPack(final_date, init_date, num_sold, people_limit, cities);
  
  this->init_date.setDate(init_date);
  this->final_date.setDate(final_date);
  this->destination = destination;
  this->cities = cities;
  this->available = available;
  this->id = id;
  this->price = price;
  this->people_limit = people_limit;
  this->num_sold = num_sold;

} 

Date TravelPack::getInitDate(void) const{ 
  return this->init_date; 
}

Date TravelPack::getFinalDate(void) const{ 
  return this->final_date; 
}

string TravelPack::getDestination(void) const{ 
  return this->destination; 
}

vector<string> TravelPack::getCities(void) const{ 
  return this->cities; 
}

unsigned int TravelPack::getPackId(void) const{ 
  return this->id;
}

unsigned int TravelPack::getPrice(void) const{ 
  return this->price; 
}

unsigned int TravelPack::getPeopleLimit(void) const{ 
  return this->people_limit; 
}

unsigned int TravelPack::getNumberSold(void) const{ 
  return this->num_sold; 
}

bool TravelPack::getAvailability(void) const{
  return this->available;
}

void TravelPack::setInitDate(string init_date, bool check){ 
  Date init(init_date);

  if(check)
    checkPack(this->final_date, init, this->num_sold, this->people_limit, this->cities);
  this->init_date.setDate(init_date);
}

void TravelPack::setFinalDate(string final_date, bool check){ 
  Date final(final_date);

  if(check)
    checkPack(final, this->init_date, this->num_sold, this->people_limit, this->cities);
  this->final_date.setDate(final_date);
}

void TravelPack::setDestination(string destination){ 
  this->destination = destination; 
}

void TravelPack::setCities(vector<string> cities, bool check){
  if(check) 
    checkPack(this->final_date, this->init_date, this->num_sold, this->people_limit, cities);
  this->cities = cities; 
}

void TravelPack::setPackId(unsigned int id){ 
  this->id = id; 
}

void TravelPack::setPrice(unsigned int price){ 
  this->price = price; 
}

void TravelPack::setPeopleLimit(unsigned int people_limit, bool check){ 
  if(check)
    checkPack(this->final_date, this->init_date, this->num_sold, people_limit, this->cities);
  this->people_limit = people_limit; 
}

void TravelPack::setNumberSold(unsigned int num_sold, bool check){ 
  if(check)
    checkPack(this->final_date, this->init_date, num_sold, this->people_limit, this->cities);
  this->num_sold = num_sold; 
}

void TravelPack::setAvailability(bool available){
  this->available = available;
}

bool TravelPack::repeatedCities(vector<string> cities) const {
  for(size_t i = 0; i < cities.size(); i++){
    for(size_t j = i+1; j < cities.size(); j++){
      if(cities.at(i) == cities.at(j))
        return true;
    }
  }
  return false;
}

void TravelPack::checkPack(Date final_date, Date init_date, unsigned int num_sold, unsigned int people_limit, vector<string> cities) const {
        cout << init_date.getDay() << "\n" << init_date.getMonth() << "\n" << init_date.getYear() << endl;
    if( final_date < init_date)
      throw new TPackException(NULL);
    if(num_sold > people_limit)
      throw new TPackException(NULL);
    if(repeatedCities(cities))
      throw new TPackException(NULL);
}

TravelPack TravelPack::operator = (const TravelPack pack){
  this->init_date = pack.getInitDate();
  this->final_date = pack.getFinalDate();
  this->destination = pack.getDestination();
  this->cities = pack.getCities();
  this->id = pack.getPackId();
  this->price = pack.getPrice();
  this->people_limit = pack.getPeopleLimit();
  this->num_sold = pack.getNumberSold();

  return *this;
}

bool TravelPack::operator == (const TravelPack pack){
  if(this->init_date == pack.getInitDate() &&
      this->final_date == pack.getFinalDate() &&
      this->destination == pack.getDestination() &&
      this->cities == pack.getCities() &&
      this->id == pack.getPackId() &&
      this->price == pack.getPrice() &&
      this->people_limit == pack.getPeopleLimit() &&
      this->num_sold == pack.getNumberSold() )
        return true; 

  return false;
}

bool TravelPack::operator == (const unsigned int id){
  if(this->id == id) return true;

  return false;
}

std::ostream& operator << (std::ostream& os, const TravelPack& pack){
  
  os << "ID: " << pack.id << std::endl;
  os << "Destination: " << pack.destination << std::endl;
  os << "Route: ";
  if(pack.cities.size() > 0){
      os << pack.cities.at(0);
    for(size_t i = 1; i < pack.cities.size(); i++)
      os  << ", " << pack.cities.at(i);
  }
  os << std::endl;
  os << "Initial Date: " << pack.init_date << std::endl;
  os << "Final Date: " << pack.final_date << std::endl;
  os << "Price: " << pack.price << std::endl;
  os << "Number of seats total: " << pack.people_limit << std::endl;
  os << "Number of seats sold: " << pack.num_sold << std::endl;
  os << "Available: ";
  if(pack.available) 
    os << "Yes\n";
  else 
    os << "No\n";

  return os;
}

std::ofstream& operator << (std::ofstream& os, const TravelPack& pack){
  if(pack.available) os << pack.id << "\n";
  else os << -pack.id << "\n";
  os << pack.destination;
  if(pack.cities.size() != 0){
    os << " - ";
    if(pack.cities.size() > 0){
      os << pack.cities.at(0);
      for(size_t i = 1; i < pack.cities.size(); i++)
        os << ", " << pack.cities.at(i);
    }
  }
  os << "\n";
  os << pack.init_date << "\n";
  os << pack.final_date << "\n";
  os << pack.price << "\n";
  os << pack.people_limit << "\n";
  os << pack.num_sold << "\n";

  return os;
}