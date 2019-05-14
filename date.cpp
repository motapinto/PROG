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
    
    checkDate(date, this->day, this->month, this->year); //throws exceptions if date is not valid
}

Date::Date(std::string date){
    checkDate(date, this->day, this->month, this->year); //throws exceptions if date is not valid
}

bool Date::operator > (const Date date){
    if(this->year == date.getYear()) {
        if(this->month > date.getMonth()) return true;
        if(this->month < date.getMonth()) return false;

        if(this->day > date.getDay()) return true;
        else return false;
    }

    if(this->year > date.getYear()) {
      return true;
    }

    return false;
}

bool Date::operator >= (const Date date){
    if(*this == date)  return true;
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
    date = year + "/" + std::to_string(this->month) + "/" + std::to_string(this->day);

    checkDate(date, this->day, this->month, this->year); //throws exceptions if date is not valid
}

void Date::setMonth (unsigned int month){
    std::string date;
    date = this->year + "/" + std::to_string(month) + "/" + std::to_string(this->day);

    checkDate(date, this->day, this->month, this->year); //throws exceptions if date is not valid
}

void Date::setDay (unsigned int day){
    std::string date;
    date = this->year + "/" + std::to_string(this->month) + "/" + std::to_string(day);

    checkDate(date, this->day, this->month, this->year); //throws exceptions if date is not valid
}

void Date::setDate(std::string date){
    checkDate(date, this->day, this->month, this->year); //throws exceptions if date is not valid
}

void Date::setDate (unsigned int year, unsigned int month, unsigned int day){
    std::string date;
    date = std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
    
    checkDate(date, this->day, this->month, this->year); //throws exceptions if date is not valid
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

std::string Date::getDate() const{ 
  std::string date =  std::to_string(this->year) + "/" + std::to_string(this->month) + "/" + std::to_string(this->day);
  return date;
}

unsigned int Date::daysOf(unsigned int month, unsigned int &year) const{
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

void Date::checkDate(std::string &date, unsigned int &day, unsigned int &month, unsigned int &year) const{
    std::vector <unsigned int> elements;
    
    // decompose method already converts substrings delimited by '/' in uint vector
    if(!decompose(date, elements, '/')) {
        throw DateException(NULL);
    }

    if(elements.size() != 3) {
        throw DateException(NULL);
    }

    if(elements.at(2) < 1 || elements.at(2) > daysOf(elements.at(1), elements.at(0)) || 
      elements.at(1) < 1 || elements.at(1) > 12 || 
      elements.at(0) < 2000 || elements.at(0) > 2100) { 
        throw new DateException(NULL);
    }

    day     = elements.at(2);
    month   = elements.at(1);
    year    = elements.at(0);

}
