#include "date.h"

Date::Date(){
  time_t current_time = time(0);
  tm *time_now = localtime(&current_time);
    
  this->day = time_now->tm_mday;
  this->month = time_now->tm_mon;
  this->year = time_now->tm_year;
}

Date::Date(unsigned int year, unsigned int month,unsigned int day){
    std::string date;
    date = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
    
    checkDate(date); //throws exceptions if date is not valid

    this->day = stoi(date.substr(6,2)); //if no exceptions is thrown then associate day 
    this->month = stoi(date.substr(4,2));//if no exceptions is thrown then associate month 
    this->year = stoi(date.substr(0, 4));//if no exceptions is thrown then associate year 
}

Date::Date(std::string date){
    checkDate(date); //throws exceptions if date is not valid
    
    this->day = stoi(date.substr(6,2)); //if no exceptions is thrown then associate day 
    this->month = stoi(date.substr(4,2)); //if no exceptions is thrown then associate day 
    this->year = stoi(date.substr(0, 4)); //if no exceptions is thrown then associate day 
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
  this->day = date.getDay();
  this->month = date.getMonth();
  this->year = date.getYear();

  return *this;
}

std::ostream& operator << (std::ostream& os, const Date& date){

  os << date.year << "/" << date.month << "/" << date.day;
  return os;
}

void Date::setYear (unsigned int year){
    std::string date;
    date = std::to_string(year) + "/" + std::to_string(this->month) + "/" + std::to_string(this->day);

    checkDate(date);
    this->year = year;
}

void Date::setMonth (unsigned int month){
    std::string date;
    date = std::to_string(this->year) + "/" + std::to_string(month) + "/" + std::to_string(this->day);

    checkDate(date);
    this->month = month;
}

void Date::setDay (unsigned int day){
    std::string date;
    date = std::to_string(this->year) + "/" + std::to_string(this->month) + "/" + std::to_string(day);

    checkDate(date);
    this->day = day;
}

void Date::setDate(std::string date){
    checkDate(date);
    this->day = stoi(date.substr(6,2));
    this->month = stoi(date.substr(4,2));
    this->year = stoi(date.substr(0, 4));
}

void Date::setDate (unsigned int year, unsigned int month, unsigned int day){
    
    std::string date;
    date = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);

    checkDate(date);
    this->day = stoi(date.substr(6,2));
    this->month = stoi(date.substr(4,2));
    this->year = stoi(date.substr(0, 4));
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
  std::string date =  std::to_string(this->year) + "/" + std::to_string(this->month) + "/" + std::to_string(this->day);
  return date;
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

void Date::checkDate(std::string date) {
  unsigned int day, month, year;

  if (date.size() == 10 && date.at(4) == '/' && date.at(7) == '/')
  {
        day = stoi(date.substr(8, 2));
        month = stoi(date.substr(5, 2));
        year = stoi(date.substr(0, 4));

        if(day < 1 || day > daysOf(month, year) || 
        month < 1 || month > 12 || year < 2000 || year > 2100) 
        { 
          throw new DateException(NULL);
        }
  }

  else 
  {
    throw new DateException(NULL);
  }

}
