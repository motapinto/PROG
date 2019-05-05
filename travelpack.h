#pragma once

#include <vector>
#include <string>
#include "date.h"

class TravelPack {
    public:
        TravelPack();
        TravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold);
        TravelPack(Date &init_date, Date &final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold);
        int readPack(std::istream &input);
        
        Date getInitDate(void);
        Date getFinalDate(void);
        std::string getDestination(void);
        std::vector<std::string> getCities(void);
        bool getAvailability(void);
        unsigned int getPackId(void);
        unsigned int getPrice(void);
        unsigned int getPeopleLimit(void);
        unsigned int getNumberSold(void);
        
        int setInitDate(std::string init_date);
        int setFinalDate(std::string final_date);
        void setInitDate(Date init_date);
        void setFinalDate(Date final_date);
        void setCities(std::vector<std::string> cities);
        void setDestination(std::string destination);
        void setAvailability(bool available);
        void setPackId(unsigned int id);
        void setPrice(unsigned int price);
        void setPeopleLimit(unsigned int people_limit);
        void setNumberSold(unsigned int num_sold);

        TravelPack operator = (TravelPack pack);
    private:
        Date init_date, final_date;
        std::string destination;
        std::vector<std::string> cities;
        bool available;
        unsigned int id, price, people_limit, num_sold;
        bool verifyCities(std::vector<std::string> cities);
}  ; 


