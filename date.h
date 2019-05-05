#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <exception>

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

    void setYear(unsigned int year) ;
    void setMonth(unsigned int month) ;
    void setDay(unsigned int day) ;
    void setDate(unsigned int year, unsigned int month, unsigned int day) ;
    void setDate(std::string date);

    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    std::string getDate() const; // returns the date in format "yyyy/mm/dd"
    
    unsigned int daysOf(unsigned int month, unsigned int &year);

    void show() const; // shows the date on the screen in format "yyyy/mm/dd"
    void checkDate(std::string &date) ;
    bool validSet(std::string date);
    bool validSet(unsigned int year, unsigned int month, unsigned int day);
    bool validConstruct(std::string date);
    bool validConstruct(unsigned int year, unsigned int month, unsigned int day); 


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

    virtual const char* what() const throw() {
        return this->str.c_str();
    }
} ;