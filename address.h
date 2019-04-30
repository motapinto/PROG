#include <string>
 
class Address {
    public:
        Address(std::string street_name, std::string postal_code, std::string city, std::string floor_num, unsigned int door_num);
        Address(); //defautl constructor
        bool setAddress(std::string &address);
        void setStreet(std::string &street);
        void setPostalCode(std::string &postal_code);
        void setCity(std::string &city);
        void setFloorNum(std::string &floor_num);
        void setDoorNum(unsigned int door_num);
        std::string getAddressString(void);
        std::string getStreet(void);
        std::string getPostalCode(void);
        std::string getCity(void);
        std::string getFloorNum(void);
        unsigned int getDoorNum(void);
    private:
        std::string street_name, postal_code, city, floor_num;  //floor_num : ("-" se não aplicável)
        unsigned int door_num;
} ;
