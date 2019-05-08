#pragma once
#include "date.h"

class TravelPack {
    public:
        TravelPack();
        TravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, int id, unsigned int price, unsigned int people_limit, unsigned int num_sold);
        
        int readPack(std::istream &input);
        void show(std::ostream &fp) const;

        Date getInitDate(void) const;
        Date getFinalDate(void) const;
        std::string getDestination(void) const;
        std::vector<std::string> getCities(void) const;
        int getPackId(void) const;
        unsigned int getPrice(void) const;
        unsigned int getPeopleLimit(void) const;
        unsigned int getNumberSold(void) const;
        
        void setInitDate(std::string init_date);
        void setFinalDate(std::string final_date);
        void setDestination(std::string destination);
        void setCities(std::vector<std::string> cities);
        void setPackId(int id);
        void setPrice(unsigned int price);
        void setPeopleLimit(unsigned int people_limit);
        void setNumberSold(unsigned int num_sold);

        TravelPack operator = (TravelPack pack);        
        bool operator == (TravelPack pack);
        bool operator == (int id);

    private:
        Date init_date, final_date;
        std::string destination;
        std::vector<std::string> cities;
        int id, price, people_limit, num_sold;
        bool available;

        bool verifyCities(std::vector<std::string> cities);
        void checkPack() ;
        friend class Agency;
}  ; 

class TPackException: public std::exception
{
    private:
        std::string str;

    public:
        TPackException(std::string str) {
            this->str = str;
        }

        virtual ~TPackException() throw() {}

    virtual const char* what() const throw() {
        return this->str.c_str();
    }
} ;



