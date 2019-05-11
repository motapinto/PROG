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

int TravelPack::readPack(istream &input){ //reads from input file and fills client class
    vector<string> elements;
    string str_aux;
    
    input >> this->id; //Number of family members
    input.ignore(); //ignore \n
    if(input)
      return 1;

    getline(input, str_aux); //Inicial date
    this->init_date.setDate(str_aux);
    if(input)
      return 2;

    getline(input, str_aux); //Final date
    this->final_date.setDate(str_aux);
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

void TravelPack::setInitDate(string init_date){ 
  checkPack(this->final_date, init_date, this->num_sold, this->people_limit, this->cities);
  this->init_date.setDate(init_date);
}

void TravelPack::setFinalDate(string final_date){ 
  checkPack(final_date, this->init_date, this->num_sold, this->people_limit, this->cities);
  this->final_date.setDate(final_date);
}

void TravelPack::setDestination(string destination){ 
  this->destination = destination; 
}

void TravelPack::setCities(vector<string> cities){ 
  checkPack(this->final_date, this->init_date, this->num_sold, this->people_limit, cities);
  this->cities = cities; 
}

void TravelPack::setPackId(unsigned int id){ 
  this->id = id; 
}

void TravelPack::setPrice(unsigned int price){ 
  this->price = price; 
}

void TravelPack::setPeopleLimit(unsigned int people_limit){ 
  checkPack(this->final_date, this->init_date, this->num_sold, people_limit, this->cities);
  this->people_limit = people_limit; 
}

void TravelPack::setNumberSold(unsigned int num_sold){ 
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
    if( final_date < init_date)
      throw new TPackException(NULL);

    if(num_sold > people_limit)
      throw new TPackException(NULL);

    if(repeatedCities(cities))
      throw new TPackException(NULL);
}

TravelPack TravelPack::operator = (TravelPack pack){
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

bool TravelPack::operator == (TravelPack pack){
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

void TravelPack::show(std::ostream &fp ) const{
  
  fp << "ID: " << id << endl;
  fp << "Destination: " << destination << endl;
  fp << "Route: ";
  if(cities.size() > 0){
      fp  << cities.at(0);
    for(size_t i = 1; i < cities.size(); i++)
      fp  << ", " << cities.at(i);
  }
  fp << endl;
  fp << "Initial Date: "; init_date.show(cout);
  fp << "Final Date: ";   final_date.show(cout);
  fp << "Price: " << price << endl;
  fp << "Number of seats total: " << people_limit << endl;
  fp << "Number of seats sold: " << num_sold << endl;
  fp << "Available: ";
  if(getAvailability() == true) 
    fp << "Yes\n";
  else 
    fp << "No\n";
}