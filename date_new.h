#include <string>

class Date
{
  public:
    Date();
    Date(unsigned int year, unsigned int month,unsigned int day);
    Date(std::string yearMonthDay); // yearMonthDay must be in format "yyyy/mm/dd"
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
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    std::string getDate() const; // returns the date in format "yyyy/mm/dd"
    void show() const; // shows the date on the screen in format "yyyy/mm/dd"
    bool isValid() const;
  private:
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int monthDay(unsigned int month, unsigned int year) const;
}; 