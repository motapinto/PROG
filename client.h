#pragma once

#include <vector>
#include <string>
#include "address.h"

class Client {
    public:
        Client();
        Client(std::string name, Address address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num);
        Client(std::string name, std::string address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num);
        bool addPack(unsigned int pack_id);

        void setName (std::string new_name);
        void setAddress(Address address);
        bool setAddress(std::string address);
        bool setTourPacks(std::vector <unsigned int> packs);
        bool setTourPacks(std::string packs, char delim);
        void setNif(unsigned int nif);
        void setFamilyNum(unsigned int family_num);

        std::string getName(void);
        Address getAddress(void);
        std::vector <unsigned int> getTourPacksBought(void);
        unsigned int getNif(void);
        unsigned int getFamilyNum(void);
        unsigned int getNumOfBuys(void);

        Client operator = (Client client);
    private:
        std::string client_name;
        Address client_address;
        std::vector<unsigned int> tour_packs_bought;
        unsigned int nif, family_num;
        bool verifyPacksBought(std::vector<unsigned int> packs);
} ;


