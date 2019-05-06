#pragma once
#include "address.h"

class Client {
    public:
        Client();
        Client(std::string name, std::string address, std::vector<int> tour_packs_bought, unsigned int nif, unsigned int family_num);
        
        void addPack(int pack_id);
        void removePack(int pack_id);
        int packPos(int id);
        void show(std::ostream &fp) const;

        void setName (std::string new_name);
        void setAddress(std::string address);
        void setTourPacks(std::vector <int> packs);
        void setNif(unsigned int nif);
        void setFamilyNum(unsigned int family_num);

        std::string getName(void) const;
        Address getAddress(void) const;
        std::vector <int> getTourPacksBought(void) const;
        unsigned int getNif(void) const;
        unsigned int getFamilyNum(void) const;
        unsigned int getNumOfBuys(void) const;

        Client operator = (Client client);

    private:
        std::string client_name;
        Address client_address;
        std::vector<int> tour_packs_bought;
        unsigned int nif, family_num;

        bool verifyPacksBought(std::vector<int> packs);
        void checkClient(void) ;
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


