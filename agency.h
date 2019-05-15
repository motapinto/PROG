#include "client.h"
#include "travelpack.h" 

#include <map>
 
class Agency {
    public:
        Agency(); 
        Agency(std::string name, std::string url, std::string agency_address, std::vector <TravelPack> tour_pack, std::vector <Client> client_list, unsigned int nif);
        
        int clientPos(unsigned int nif);
        bool addClient(std::string name, std::string address, std::vector <unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num);
        bool changeClient(Client &client, unsigned int nif);
        bool removeClient(unsigned int nif);
        bool purchasePack(unsigned int client_nif, unsigned int pack_id);

        bool addTravelPack(std::string init_date, std::string final_date, std::string destination, std::vector<std::string> cities, bool available, unsigned int id, unsigned int price, unsigned int people_limit, unsigned int num_sold);
        bool changeTravelPack(TravelPack &pack, unsigned int id);
        bool removeTravelPack(unsigned int id);

        bool searchClientNif(unsigned int nif, Client &client);
        std::vector<Client> searchClientName(std::string name);

        bool searchTravelPackId(unsigned int id, TravelPack &pack);
        std::vector<TravelPack> searchTravelPackDestination(std::string destination);
        std::vector<TravelPack> searchTravelPackCity(std::string city);
        std::vector<TravelPack> searchTravelPackDates(std::string initial_date, std::string final_date);
        std::vector<TravelPack> searchTravelPackDates(Date initial_date, Date final_date);
        
        std::multimap<unsigned int, std::string> mostVisitedPlaces();

        void setName(const std::string &name);
        void setUrl(const std::string &url);
        void setAddress(const Address &address);
        void setAddress(const std::string &address);
        void setTourPack(const std::vector <TravelPack> &tour_pack);
        void setClientList(const std::vector <Client> &client_list);
        void setNif(const unsigned int &nif);

        std::string getName(void);
        std::string getUrl(void);
        Address getAddress(void);
        std::vector <TravelPack> getTourPacks(void);
        std::vector <Client> getClientList(void);
        unsigned int getNif(void);

        friend std::ofstream& operator << (std::ofstream& os, const Agency& agency); //acede aos parametros da classe
        friend std::ostream& operator << (std::ostream& os, const Agency& agency); //acede aos parametros da classe

        friend std::ifstream& operator >> (std::ifstream& is, Agency &agency);

    private:
        std::string name, url;
        Address agency_address;
        std::vector <Client> client_list;
        std::vector <TravelPack> tour_pack;  
        unsigned int nif;

        bool verifyCities(const std::vector<std::string> cities);
        unsigned int sumSold(const unsigned int nif);
        unsigned int sumSold(const std::set<unsigned int> &tour_packs, const unsigned int family_num);
        unsigned int sumSold(const std::vector<unsigned int> &tour_packs, const unsigned int family_num);
        bool verifyPacks(const std::vector<unsigned int> &packs, const unsigned int family_num);
        bool verifyClientPacks(const std::vector<unsigned int> &packs);
        bool verifyPacks(const std::set<unsigned int> &packs, const unsigned int family_num);
        bool verifyClientPacks(const std::set<unsigned int> &packs);
} ;
