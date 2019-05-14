#include "UtilityFunctions.h"
 
class Address {
    public:
        Address(std::string street_name, std::string postal_code, std::string city, std::string floor_num, unsigned int door_num);
        Address(std::string address);
        Address();
        
        void setAddress(std::string address);
        void setStreet(std::string street);
        void setPostalCode(std::string postal_code);
        void setCity(std::string city);
        void setFloorNum(std::string floor_num);
        void setDoorNum(unsigned int door_num);

        std::string getAddress(void) const;
        std::string getStreet(void) const;
        std::string getPostalCode(void) const;
        std::string getCity(void) const;
        std::string getFloorNum(void) const;
        unsigned int getDoorNum(void) const;

        friend std::ostream& operator << (std::ostream& os, const Address &address); //acede aos parametros da classe
        

    private:
        std::string street_name, postal_code, city, floor_num;  //floor_num : ("-" se não aplicável)
        unsigned int door_num;

        void checkAddress(std::string &address, std::string &street_name, std::string &postal_code, std::string &city, std::string &floor_num, unsigned int &door_num) const;
} ;

class AddressException: public std::exception
{
    private:
        std::string str;

    public:
        AddressException(std::string str) {
            this->str = str;
        }

        virtual ~AddressException() throw() {}

    virtual const char* what() const throw() {
        return this->str.c_str();
    }
} ;
