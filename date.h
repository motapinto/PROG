#pragma once
#include "UtilityFunctions.h"

class Date
{
  public:
    Date();
    Date(unsigned int year, unsigned int month,unsigned int day);
    Date(std::string date); // yearMonthDay must be in format "yyyy/mm/dd"

    bool operator > (const Date date);
    bool operator >= (const Date date);
    bool operator < (const Date date);
    bool operator <= (const Date date);
    bool operator == (const Date date);
    bool operator != (const Date date);
    Date operator = (const Date date);
    friend std::ostream& operator << (std::ostream& os, const Date& date); //acede aos parametros da classe

    void setYear(unsigned int year) ;
    void setMonth(unsigned int month) ;
    void setDay(unsigned int day) ;
    void setDate(unsigned int year, unsigned int month, unsigned int day) ;
    void setDate(std::string date);

    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    std::string getDate() const; // returns the date in format "yyyy/mm/dd"
    
    unsigned int daysOf(unsigned int month, unsigned int &year) const;
    void checkDate(std::string date) const;

  private:
    unsigned int year;
    unsigned int month;
    unsigned int day;
}; 

class DateException: public std::exception
{
    private:
        std::string str;

    public:
        DateException(std::string str) {
            this->str = str;
        }

        virtual ~DateException() throw() {}

    virtual const char* what() const throw() {
        return this->str.c_str();
    }
} ;