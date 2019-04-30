#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include "date.hpp"

Date::Date(unsigned int year, unsigned int month,unsigned int day){
  this->year = year;
  this->month = month;
  this->day = day;
}
Date::Date(std::string yearMonthDay){ // yearMonthDay must be in format "yyyy/mm/dd"
  std::string str_aux;
  size_t pos = 0;

  pos = yearMonthDay.find('/');
  str_aux = yearMonthDay.substr(pos);
  this->year = stoi(str_aux);
  yearMonthDay.erase(0, pos+1);

  pos = yearMonthDay.find('/');
  str_aux = yearMonthDay.substr(pos);
  this->month = stoi(str_aux);
  yearMonthDay.erase(0, pos+1);

  pos = yearMonthDay.find('/');
  str_aux = yearMonthDay.substr(pos);
  this->day = stoi(str_aux);
}
Date::Date(){
  time_t now = time(0);
  tm* localtm = localtime(&now);

  this->year = localtm->tm_year + 1900;
  this->month = localtm->tm_mon + 1;
  this->day = localtm->tm_mday;
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


void Date::setYear(unsigned int year){ this->year = year; }
void Date::setMonth(unsigned int month) { this->month = month; }
void Date::setDay(unsigned int day) { this->day = day; }
void Date::setDate(unsigned int year, unsigned int month, unsigned int day) {
  this->year = year;
  this->month = month;
  this->day = day;
}
unsigned int Date::getYear() const{ return this->year; }
unsigned int Date::getMonth() const{ return this->month; }
unsigned int Date::getDay() const{ return this->day; }
std::string Date::getDate() const{ // returns the date in format "yyyy/mm/dd"
  std::string date;

  date.append(std::to_string(this->year));
  date.append("/");
  date.append(std::to_string(this->month));
  date.append("/");
  date.append(std::to_string(this->day));

  return date;
}
void Date::show() const{ // shows the date on the screen in format "yyyy/mm/dd"
  std::cout << std::setw(4) << this->year << '/' << std::setw(2) << this->month << '/' << std::setw(2) << this->day << std::endl;
}

bool Date::isValid() const {
  unsigned int func_ret = monthDay(this->month, this->year);

  if(func_ret == 0) return false;
  if(this->day > func_ret) return false;

  return true;
}

unsigned int Date::monthDay(unsigned int month, unsigned int year) const{
  switch (month)
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8: 
    case 10: 
    case 12: 
      return 31;

    case 2:
      if((year % 4) == 0 && (year % 400) == 0 && year % 100) return 29;
      return 28;

    case 4:
    case 6:
    case 9:
    case 11:
      return 30;

    default:
      break;
  }
  return 0;
}

