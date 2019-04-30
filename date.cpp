#include "date.h"

Date::Date(){
  time_t current_time = time(0);
  tm *time_now = localtime(&current_time);
    
  this->day = time_now->tm_mday;
  this->month = time_now->tm_mon;
  this->year = time_now->tm_year;
}

Date::Date(unsigned int year, unsigned int month,unsigned int day){
    string date;

    while(!isValid()) {
        std::cerr << "Date invalid, try again: ";
        getline(cin, date);
        this->setDate(date);
    }
}

Date::Date(std::string date){

    try {
        checkDate(date);
        this->day = stoi(date.substr(6,2));
        this->month = stoi(date.substr(4,2));
        this->year = stoi(date.substr(0, 4));
    }

    catch(DateException) {
            std::cerr << "Date invalid, try again!\n";
            std::cout << "Date: ";
            getline(cin, date);
            this->setDate(date);
        }
    catch(const invalid_argument& ia) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
    catch(...) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
}

bool Date::operator > (const Date date){
  if(this->year == date.getYear()){
    if(this->month > date.getMonth()) return true;
    if(this->month < date.getMonth()) return false;

    if(this->day > date.getDay()) return true;
    else return false;
  }

  if(this->year > date.getYear()) return true;

  return false;
}

bool Date::operator >= (const Date date){
  if(*this == date) return true;
  if(*this > date) return true;

  return false;
}

bool Date::operator < (const Date date){
  if(this->year == date.getYear()){
    if(this->month > date.getMonth()) return false;
    if(this->month < date.getMonth()) return true;

    if(this->day < date.getDay()) return true;
    else return false;
  }

  if(this->year < date.getYear()) return true;

  return false;
}

bool Date::operator <= (const Date date){
  if(*this == date) return true;
  if(*this < date) return true;

  return false;

}

bool Date::operator == (const Date date){
  if(this->year != date.getYear()) return false;
  if(this->month != date.getMonth()) return false;
  if(this->day != date.getDay()) return false;

  return true;
}

bool Date::operator != (const Date date){
  if(this->year != date.getYear()) return true;
  if(this->month != date.getMonth()) return true;
  if(this->day != date.getDay()) return true;

  return false;
}

Date Date::operator = (const Date date){
  this->day = date.day;
  this->month = date.month;
  this->year = date.year;

  return *this;
}

void Date::setYear (uint year){
    string date;
    this->year = year;

    while(!this->isValid()) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
}
void Date::setDay (uint day){
    string date;
    this->day = day;

    while(!this->isValid()) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
}

void Date::setMonth (uint month){
    string date;
    this->month = month;

   while(!this->isValid()) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
}

void Date::setDate(string date){
    try {
        checkDate(date);
        this->day = stoi(date.substr(6,2));
        this->month = stoi(date.substr(4,2));
        this->year = stoi(date.substr(0, 4));
    }

    catch(DateException) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
    catch(const invalid_argument& ia) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
    catch(...) {
        std::cerr << "Date invalid, try again!\n";
        std::cout << "Date: ";
        getline(cin, date);
        this->setDate(date);
    }
}

void Date::setDate (unsigned int year, unsigned int month, unsigned int day){
    string date;

    this->year = year;
    this->month = month;
    this->day = day;

    while(!this->isValid()) {
        std::cerr << "Date is not valid, try again: ";
        getline(cin, date);
        this->setDate(date);
    }
}

unsigned int Date::getYear() const{ 
  return this->year; 
}

unsigned int Date::getMonth() const{ 
  return this->month; 
}

unsigned int Date::getDay() const{ 
  return this->day; 
}

std::string Date::getDate() const{ // returns the date in format "yyyy/mm/dd"
  std::string date;

  string date = to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);

  return date;
}

void Date::show() const{ // shows the date on the screen in format "yyyy/mm/dd"
  std::cout << std::setw(4) << this->year << '/' << std::setw(2) << this->month << '/' << std::setw(2) << this->day << std::endl;
}

bool Date::isValid() {
    if(this->day >= 1 && this->day <= this->daysOf(this->month, this->year) && 
        this->month >= 1 && this->month <= 12 && 
        this->year >= 1900 && this->year <=3000)
        return true;
    return false;
}

unsigned int Date::daysOf(unsigned int month, unsigned int &year) {
  switch (month) {
    case 2:
      if (year % 4 == 0 && year % 100 != 0 && year % 400 == 0)
        return 29;
      else
        return 28;

    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
    case 11:
      return 31;

    case 4:
    case 6:
    case 8:
    case 10:
    case 12:
      return 31;

    default:
      return 0;
  }
  return 0;
}

void Date::checkDate(string &date) {
    uint day, month, year;

    if (date.size() == 10 && date.at(2) == '/' && date.at(5) == '/')
    {
        day = stoi(date.substr(0, 2));
        month = stoi(date.substr(3, 2));
        year = stoi(date.substr(5, 4));

        this->setDate(day, month, year);
        if (!this->isValid())
        {
            throw new DateException("MY EXP");
        }
    }
    else {
        throw new DateException("MY EXP");
    }
}