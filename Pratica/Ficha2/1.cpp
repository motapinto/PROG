#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <exception>

#define uint unsigned int

using namespace std;

class Date
{
    public:

        Date();
        Date(unsigned int day, unsigned int month,unsigned int year);
        Date(string date); // yearMonthDay must be in format "dd/mm/yyyy"
        void setDay(unsigned int day) ;
        void setMonth(unsigned int month) ;
        void setYear(unsigned int year) ;
        void setDate(unsigned int year, unsigned int month, unsigned int day) ;
        void setDate(string date) ;
        
        unsigned int getYear() const;
        unsigned int getMonth() const;
        unsigned int getDay() const;
        string getDate() const; // returns the date in format "dd/mm/yyy"
        void show() const; // shows the date on the screen in format "dd/mm/yyy"

        bool isValid();
        void checkDate(string &date);
    
    private:

        uint daysOf(uint month, uint &year);
        unsigned int year;
        unsigned int month;
        unsigned int day;
}; 

class DateException: public exception
{
    private:
        string str;

    public:
        DateException(string str) {
            this->str = str;
        }

    virtual const char* what() const throw() {
        return this->str.c_str();
    }
} ;


Date::Date() {
    time_t current_time = time(0);
    tm *time_now = localtime(&current_time);
    
    this->day = time_now->tm_mday;
    this->month = time_now->tm_mon;
    this->year = time_now->tm_year;
}

Date::Date(unsigned int year, unsigned int month,unsigned int day) {
    string date;

    while(!isValid()) {
        std::cerr << "Date invalid, try again: ";
        getline(cin, date);
        this->setDate(date);
    }
}

Date::Date(string date) {

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

bool Date::isValid() {
    return true;
}


int main() {

    string date;
    cout << "New date(dd/mm/yyyy):";
    getline(cin, date);

    Date mydate(date);
    mydate.show();


    //Date d1; not possible because... default constructor didn't exist before this exercise


}