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
    if(init > final_date)
      throw TPackException(NULL);

  this->init_date.setDate(init_date);
}

void TravelPack::setFinalDate(string final_date, bool check){ 
  Date fin(final_date);

  if(check)
    if(init_date > fin)
      throw TPackException(NULL);

  this->final_date.setDate(final_date);
}

void TravelPack::setDestination(string destination){ 
  this->destination = destination; 
}

void TravelPack::setCities(vector<string> cities, bool check){
  if(check) 
    repeatedCities(cities);

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
    if(people_limit < num_sold)
      throw TPackException(NULL);

  this->people_limit = people_limit; 
}

void TravelPack::setNumberSold(unsigned int num_sold, bool check){ 
  if(check)
    if(people_limit < num_sold)
      throw TPackException(NULL);

  this->num_sold = num_sold; 
}

void TravelPack::setAvailability(bool available){
  this->available = available;
}

void TravelPack::repeatedCities(vector<string> cities) const {
  for(size_t i = 0; i < cities.size(); i++){
    for(size_t j = i+1; j < cities.size(); j++){
      if(cities.at(i) == cities.at(j))
        throw TPackException(NULL);
    }
  }
}

void TravelPack::checkPack(Date final_date, Date init_date, unsigned int num_sold, unsigned int people_limit, vector<string> cities) const {
    if( final_date < init_date)
      throw new TPackException(NULL);
    if(num_sold > people_limit)
      throw new TPackException(NULL);
    repeatedCities(cities);
}

TravelPack& TravelPack::operator = (const TravelPack pack){
  this->init_date = pack.getInitDate();
  this->final_date = pack.getFinalDate();
  this->destination = pack.getDestination();
  this->cities = pack.getCities();
  this->id = pack.getPackId();
  this->price = pack.getPrice();
  this->people_limit = pack.getPeopleLimit();
  this->num_sold = pack.getNumberSold();
  this->available = pack.getAvailability();

  return *this;
}

bool TravelPack::operator == (const TravelPack pack){
  return (this->init_date == pack.init_date &&
      this->final_date == pack.final_date &&
      this->destination == pack.destination &&
      this->cities == pack.cities &&
      this->id == pack.id &&
      this->price == pack.price &&
      this->people_limit == pack.people_limit &&
      this->num_sold == pack.num_sold); 

}

bool TravelPack::operator == (const unsigned int id){
  return this->id == id;
}

bool TravelPack::operator < (const TravelPack pack){
  return id < pack.id;
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

std::ifstream& operator >> (std::ifstream& is, TravelPack &pack){
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
        if(string_to_int(str_aux, value_check) == false)
          throw TPackException(NULL);
        if(value_check < 0){
          pack.available = false;
          pack.id = -value_check;
        }
        else {
          pack.available = true;
          pack.id = value_check;
        }
        value_check = -1;
        break;

      case 1:
        //separate destination from cities
        decompose(str_aux, pack.cities, '-'); 
        if(pack.cities.size() == 0 || pack.cities.size() > 2) throw TPackException(NULL);
        pack.destination = pack.cities.at(0);

        //separate all cities if they exist
        if(pack.cities.size() == 2) decompose(pack.cities.at(1), pack.cities, ',');
        else pack.cities.resize(0); //eliminate all elements of cities
        break;

      case 2:
        pack.init_date.setDate(str_aux);
        break;

      case 3:
        pack.final_date.setDate(str_aux);
        break;

      case 4:
        if(string_to_int(str_aux, value_check) == false)
          throw TPackException(NULL);
        if(value_check <= -1)
          throw TPackException(NULL);
        pack.price = value_check;
        value_check = -1;
        break;
      
      case 5:
        if(string_to_int(str_aux, value_check) == false)
          throw TPackException(NULL);
        if(value_check <= -1)
          throw TPackException(NULL);
        pack.people_limit = value_check;
        value_check = -1;
        break;
      
      case 6:
        if(string_to_int(str_aux, value_check) == false)
          throw TPackException(NULL);
        if(value_check <= -1)
          throw TPackException(NULL);
        pack.num_sold = value_check;
        value_check = -1;

        pack.checkPack(pack.final_date, pack.init_date, pack.num_sold, pack.people_limit, pack.cities);

        return is;
    }

    line_count++;
  }

  throw TPackException(NULL);
  return is;
}
