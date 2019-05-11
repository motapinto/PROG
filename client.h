#pragma once

#include <vector>
#include <string>
#include "address.h"

class Client {
    public:
        Client();
        Client(std::string name, std::string address, std::vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num, unsigned int money_spent);

        void show(std::ostream &fp) const;

        int packPos(unsigned int id);
        void addPack(unsigned int pack_id);
        void removePack(int pack_id);

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
        std::string client_name;
        Address client_address;
        std::vector<unsigned int> tour_packs_bought;
        unsigned int nif, family_num, money_spent;

        //Class Agency can now access all private members of Client
        friend class Agency;

        //Private methods only inside public functions
        bool repeatedPacks(std::vector<unsigned int> packs) const;
        void checkClient(std::vector<unsigned int> tour_packs_bought);
} ;

class ClientException: public std::exception
{
    private:
        std::string str;

    public:
        ClientException(std::string str) {
            this->str = str;
        }

        virtual ~ClientException() throw() {}

    virtual const char* what() const throw() {
        return this->str.c_str();
    }
} ;


