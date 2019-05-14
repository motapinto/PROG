#pragma once
#include "date.h"

class TravelPack {
    public:
        TravelPack();
        TravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold);
        
        int readPack(std::istream &input);
        void show(std::ostream &fp) const;

        Date getInitDate(void) const;
        Date getFinalDate(void) const;
        std::string getDestination(void) const;
        std::vector<std::string> getCities(void) const;
        unsigned int getPackId(void) const;
        unsigned int getPrice(void) const;
        unsigned int getPeopleLimit(void) const;
        unsigned int getNumberSold(void) const;
        bool getAvailability(void) const;
        
        void setInitDate(std::string init_date, bool check);
        void setFinalDate(std::string final_date, bool check);
        void setDestination(std::string destination);
        void setCities(std::vector<std::string> cities, bool check);
        void setPackId(unsigned int id);
        void setPrice(unsigned int price);
        void setPeopleLimit(unsigned int people_limit, bool check);
        void setNumberSold(unsigned int num_sold, bool check);
        void setAvailability(bool available);

        TravelPack operator = (const TravelPack pack);        
        bool operator == (const TravelPack pack);
        bool operator == (const unsigned int id);

        friend std::ofstream& operator << (std::ofstream& os, const TravelPack& pack); //acede aos parametros da classe
        friend std::ostream& operator << (std::ostream& os, const TravelPack& pack); //acede aos parametros da classe

        friend std::ifstream& operator >> (std::ifstream& is, TravelPack &pack);


    private:
        Date init_date, final_date;
        std::string destination;
        std::vector<std::string> cities;
        unsigned int id, price, people_limit, num_sold;
        bool available;

        //Private methods only inside public functions
        void repeatedCities(std::vector<std::string> cities) const;
        void checkPack(Date final_date, Date init_date, unsigned int num_sold, unsigned int people_limit, std::vector<std::string> cities) const;
        //Class Agency can now access all private members of TravelPack
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



