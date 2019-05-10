#pragma once

#include <vector>
#include <string>
#include "address.h"

class Client {
    public:
        Client();
        Client(std::string name, Address address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num, unsigned int money_spent);
        Client(std::string name, std::string address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num, unsigned int money_spent);
        bool addPack(unsigned int pack_id);

        void setName (std::string new_name);
        void setAddress(std::string address);
        void setTourPacks(std::vector <unsigned int> packs);
        void setTourPacks(std::string packs, char delim);
        void setNif(unsigned int nif);
        void setFamilyNum(unsigned int family_num);
        void setMoneySpent(unsigned int money_spent);

        std::string getName(void) const;
        Address getAddress(void) const;
        std::vector <unsigned int> getTourPacksBought(void) const;
        unsigned int getNif(void) const;
        unsigned int getFamilyNum(void) const;
        unsigned int getNumOfBuys(void) const;
        unsigned int getMoneySpent(void) const;

        Client operator = (Client client);
    private:
        friend class Agency;
        std::string client_name;
        Address client_address;
        std::vector<unsigned int> tour_packs_bought;
        unsigned int nif, family_num, money_spent;
        bool verifyPacksBought(std::vector<unsigned int> packs);
} ;


