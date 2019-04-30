#include <string>

struct Date{
  unsigned int day;
  unsigned int month;
  unsigned int year;
} ;

int setDate(Date &date, std::string s);

std::string getDate(Date date);

int getIntDate(Date date);
