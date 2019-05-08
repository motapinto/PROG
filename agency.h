#include "client.h"
#include "travelpack.h" 
 
class Agency {
    public:
        Agency(); 
        Agency(std::string name, std::string url, std::string agency_address, std::vector <TravelPack> tour_pack, std::vector <Client> client_list, unsigned int nif);
        
        int clientPos(unsigned int nif);
        
        void addClient(std::string name, std::string address, std::vector <unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num);
        void changeClient(Client &client, unsigned int nif);
        void removeClient(unsigned int nif);

        void addTravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, int id, unsigned int price, unsigned int people_limit, unsigned int num_sold);
        void changeTravelPack(TravelPack &pack, unsigned int id);
        void removeTravelPack(unsigned int id);

        bool searchTravelPackId(unsigned int id, TravelPack &pack);
        std::vector<TravelPack> searchTravelPackDestination(std::string destination);
        std::vector<TravelPack> searchTravelPackDates(std::string initial_date, std::string final_date);
        std::vector<TravelPack> searchTravelPackDates(Date initial_date, Date final_date);
        
        void setName(std::string name);
        void setUrl(std::string url);
        void setAddress(Address address);
        void setAddress(std::string address);
        void setTourPack(std::vector <TravelPack> tour_pack);
        void setClientList(std::vector <Client> client_list);
        void setNif(unsigned int nif);

        std::string getName(void);
        std::string getUrl(void);
        Address getAddress(void);
        std::vector <TravelPack> getTourPacks(void);
        std::vector <Client> getClientList(void);
        unsigned int getNif(void);


    private:
        std::string name, url;
        Address agency_address;
        std::vector <Client> client_list;
        std::vector <TravelPack> tour_pack;  
        unsigned int nif;

        bool verifyCities(std::vector<std::string> cities);
        bool verifyPacksBought(std::vector<unsigned int> packs);
        unsigned int sumSold(const unsigned int id);
        bool verifyPacks(const std::vector<unsigned int> &packs);
} ;
