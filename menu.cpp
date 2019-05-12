#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include "menu.h"
#include "agency.h"
#include "UtilityFunctions.h"

#define MAX_NIF 999999999
#define INT_MAX 2147483647

extern Agency agency;
extern bool modified_agency, modified_client, modified_travel_pack;

void print_first_lines(const char *array){
  std::cout << "\n==============================\n";
  std::cout << "\t" << array;
  std::cout << "\n==============================\n";
}

void print_last_line(){
  std::cout << "==============================\n\n";
}

void print_wait_menu(){
  std::string str_aux;
  std::cin.clear();
  fflush(stdin);
  std::cout << "\nPress enter to continue... ";
  getline(std::cin, str_aux);
  std::cout<< std::endl;
}

//Begin Agency

void print_address_struct(){
  std::cout<< "(Street Name) / (Door Number) / (Floor) / (Zip Code) / (City)\n";
}

void change_agency_name(){
  std::string str_aux;
  std::cout<< "Name: "; read_line(str_aux); 
  agency.setName(str_aux);
  modified_agency = true;
}

void change_agency_nif(){
  int nif = -1;
  std::string str_aux;

  std::cout<< "NIF: "; read_line(str_aux);
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "NIF: "; read_line(str_aux);
  }

  agency.setNif(nif);
  modified_agency = true;
}

void change_agency_address(){
  std::string str_aux;
  std::cout<< "Address: "; read_line(str_aux);

  while(1) {
    try {
      agency.setAddress(str_aux);
    }
    catch(std::string) {
      std::cout<< "Invalid input!\nAddress must be typed in the following way: \n";
      print_address_struct();
      std::cout<< "Address: "; read_line(str_aux);
    }
  }
  agency.setAddress(str_aux);
  modified_agency = true;
}

void change_agency_url(){
  std::string str_aux;

  std::cout<< "URL: "; read_line(str_aux);

  agency.setUrl(str_aux);  
  modified_agency = true;
}

void change_agency_all(){
  change_agency_name();
  change_agency_nif();
  change_agency_address();
  change_agency_url();
}

void change_agency_menu(){
  int answer = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Change Agency Menu");
    std::cout<< "1 - All\n";
    std::cout<< "2 - Name\n";
    std::cout<< "3 - NIF\n";
    std::cout<< "4 - Address\n";
    std::cout<< "5 - URL\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 5){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        change_agency_all();
        break;

      case 2:
        change_agency_name();
        break;

      case 3:
        change_agency_nif();
        break;

      case 4:
        change_agency_address();
        break;

      case 5:
        change_agency_url();
        break;

      default:
        break;
    }
  }
}

void print_total_gains(){
  std::vector<TravelPack> packs = agency.getTourPacks();
  long gains = 0, num_sold = 0;
  
  for(size_t i = 0; i < packs.size(); i++){
    num_sold += packs.at(i).getNumberSold();
    gains += packs.at(i).getNumberSold() * packs.at(i).getPrice();
  }

  std::cout<< std::endl << "Number of packs sold: " << num_sold << std::endl;
  std::cout<< "Total amount of gains: " << gains << std::endl << std::endl;
  print_wait_menu();
}

void agency_menu(){
  int answer = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Agency Menu");
    std::cout<< "1 - View\n";
    std::cout<< "2 - Change\n";
    std::cout<< "3 - Calculate Gains\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 3){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        agency.show(std::cout);
        print_wait_menu();
        break;

      case 2:
        change_agency_menu();
        break;

      case 3:
        print_total_gains();
        break;

      default:
        break;
    }
  }
}

//End Agency
//Begin Clients

int search_client_name(Client &client){
  std::vector<Client> vec;
  std::string name;

  std::cout<< "Name: "; read_line(name); 

  vec = agency.searchClientName(name);
  
  if(vec.size() == 1) client = vec.at(0);
  else if(vec.size() > 1) return 1;
  else return -1;

  return 0;
}

int search_client_nif(Client &client){
  int nif = 0;
  std::string str_aux;

  std::cout<< "NIF: ";
  read_line(str_aux);
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "NIF: ";
    read_line(str_aux);
  }



  if(!agency.searchClientNif(nif, client)) return -1;

  return 0;
}

void print_client_packs(Client &client){
  std::vector<unsigned int>tour_packs_ids = client.getTourPacksBought();
  TravelPack pack;

  if(tour_packs_ids.size() == 0) std::cout<< "This client does not have any purchased packs\n";
  else{
    for(size_t i = 0; i < tour_packs_ids.size(); i++){
      if(agency.searchTravelPackId(tour_packs_ids.at(i), pack) == false) std::cout<< "Travel Pack with ID: " << tour_packs_ids.at(i) << " could not be found\n";
      else pack.show(std::cout);
    }
  }
}

void print_client_selected(Client &client){
    int answer = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Selected Client Menu");
    std::cout<< "1 - View Client Details\n";
    std::cout<< "2 - View Packs Bought\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        client.show(std::cout);
        break;

      case 2:
        print_client_packs(client);
        break;

      default:
        break;
    }
  }
}

void print_client_selected(std::vector<Client> &client_vec){
  if(client_vec.size() > 1) std::cout<< "More than one client found!\nPlease select the client wanted by another parameter\n";
  else print_client_selected(client_vec.at(0));
}

void print_single_client(){
  int answer = 0;
  Client client;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Single Client View Menu");
    std::cout<< "1 - Search by NIF\n";
    std::cout<< "2 - Search by Name\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        switch (search_client_nif(client))
        {
          case 0:
            print_client_selected(client);
            break;

          case 1:
            std::cout<< "Could not find client!\n";
            break;

          default:
            break;
        }
        break;

      case 2:
        switch (search_client_name(client))
        {
          case 0:
            print_client_selected(client);
            break;
        
          case 1:
            std::cout<< "More than one client found with given name!\n";
            break;

          case -1:
            std::cout<< "Could not find client with specified name!\n";
            break;
            
          default:
            break;
        }
        break;

      default:
        break;
    }
  }
  
}

void print_all_clients(){
  std::vector<Client> vec = agency.getClientList();
  size_t client_counter = 0;

  for(size_t i = 0; i < vec.size(); i++, client_counter++){
    if(client_counter == 4){
      client_counter = 0; //reset counter
      print_wait_menu();
    }
    vec.at(i).show(std::cout);
    std::cout<< std::endl;
  }

  print_wait_menu();
}

void print_clients_all_travel_packs(){
  std::vector<Client> client_list = agency.getClientList();
  std::vector<unsigned int> client_packs_bought;
  std::vector<unsigned int> tour_packs_ids;
  TravelPack pack;
  bool already_exists = false;
  int pack_count = 0;

  for(size_t i = 0; i < client_list.size(); i++){ //For every client
    client_packs_bought = client_list.at(i).getTourPacksBought();
    for(size_t j = 0; j < client_packs_bought.size(); j++){ //Search each client
      for(size_t k = 0; k < tour_packs_ids.size(); k++){ //Verify for every id
        if(tour_packs_ids.at(k) == client_packs_bought.at(j)){ //Id is already in tour_packs_ids std::vector
          already_exists = true;
          break;
        }
      }
      if(already_exists == true) continue;
      else tour_packs_ids.push_back(client_packs_bought.at(j));
      already_exists = false;
    }
  }

  if(tour_packs_ids.size() == 0) std::cout<< "No packs were purchased by any client\n";
  else{
    for(size_t i = 0; i < tour_packs_ids.size(); i++, pack_count++){
      if(pack_count == 5) print_wait_menu();

      if(!agency.searchTravelPackId(tour_packs_ids.at(i), pack)) std::cout<< "Travel Pack with ID: " << tour_packs_ids.at(i) << " could not be found\n";
      else pack.show(std::cout);
      std::cout<< std::endl;             
    }
  }

  print_wait_menu();
}

void print_clients_menu(){
  int answer = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("View Clients Menu");
    std::cout<< "1 - All Clients\n";
    std::cout<< "2 - Single Client\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        print_all_clients();
        break;

      case 2:
        print_single_client();
        break;

      default:
        break;
    }
  }
}

void change_client_name(Client &client){
  std::string str_aux;
  std::cout<< "Name: "; 
  read_line(str_aux); 

  client.setName(str_aux);
}

void change_client_address(Client &client){
  std::string str_aux;
  std::cout<< "Address: "; read_line(str_aux);

  try {
    client.setAddress(str_aux);
  }

  catch(std::string) {
    std::cout<< "Invalid input!\nAddress must be typed in the following way: \n";
    print_address_struct();
    std::cout<< "Address: "; read_line(str_aux);
  }


}

void change_client_packs_bought(Client &client){
  std::string str_aux;

  std::cout<< "Tour packs bought: "; read_line(str_aux);

  while(1) {
      try {
        client.setTourPacks(str_aux, ';');
        break;
      }

      catch(std::string) {
        std::cout<< "Invalid intput!\nPlease type tour packs bought in the following order:\n";
        std::cout<< "(Tour Pack Id 1) ; (Tour Pack Id 2); ... ; (Tour Pack Id n) or - for no packs\n";
        std::cout<< "Tour packs bought: ";
        read_line(str_aux);
      }

  }

}

bool change_client_nif(Client &client){
  int nif = -1;
  std::string str_aux;
  Client search_aux;

  std::cout<< "NIF: "; read_line(str_aux);

  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "NIF: "; read_line(str_aux);
  }

  if(agency.searchClientNif((unsigned int)nif, search_aux) == true){
    std::cerr << "Invalid Input!\nClient with NIF: " << nif << " already exists!\n";
    return false;
  }

  client.setNif(nif);
  return true;
}

void change_client_family_num(Client &client){
  int family_num = -1;
  std::string str_aux;

  std::cout<< "Family Number: "; read_line(str_aux);
  while(string_to_int(str_aux, family_num) == false || family_num <= 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Family Number: "; read_line(str_aux);
  }

  client.setFamilyNum(family_num);
}

void add_client(){
  Client new_client;
  change_client_name(new_client);
  if(change_client_nif(new_client) == false){
    print_wait_menu();
    return;
  }
  change_client_address(new_client);
  change_client_packs_bought(new_client);
  change_client_family_num(new_client);


  try {
    agency.addClient(new_client.getName(), new_client.getAddress().getAddress(), new_client.getTourPacksBought(), new_client.getNif(), new_client.getNif());
  }

  catch(std::string) {
    std::cerr << "Failled to add client: some parameters were wrong\n";
  }

  modified_client = true;
  print_wait_menu();
}

void change_client_menu(Client &client){
  int answer = 0;
  int old_nif = client.getNif();

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Change Client Selected Menu");
    std::cout<< "1 - All\n";
    std::cout<< "2 - Name\n";
    std::cout<< "3 - NIF\n";
    std::cout<< "4 - Address\n";
    std::cout<< "5 - Tour Packs Bought\n";
    std::cout<< "6 - Family Number\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 6){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        change_client_name(client);
        if(change_client_nif(client) == false) break;
        change_client_address(client);
        change_client_packs_bought(client);
        change_client_family_num(client);

        try {
          agency.changeClient(client, old_nif);
          modified_client = true;
        }
        catch(std::string) {
          std::cerr << "Failled to modify client: some parameters were invalid!\n";
        }

        break;

      case 2:
        change_client_name(client);
       /* if(*/agency.changeClient(client, old_nif); //== true) modified_client = true;
        //else std::cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      case 3:
        if(change_client_nif(client) == false) break;
        /*if(*/agency.changeClient(client, old_nif);// == true) modified_client = true;
        //else std::cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      case 4:
        change_client_address(client);
        /*if(*/agency.changeClient(client, old_nif);// == true) modified_client = true;
        //else std::cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      case 5:
        change_client_packs_bought(client);
        /*if(*/agency.changeClient(client, old_nif);// == true) modified_client = true;
        //else std::cerr << "Failled to modify client: invalid packs entered!\n";
        break;

      case 6:
        change_client_family_num(client);
        /*if(*/agency.changeClient(client, old_nif);// == true) modified_client = true;
        //else std::cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      default:
        break;
    }
  }
}

void change_clients_menu(){
  int answer = 0;
  Client client;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Change Clients Menu");
    std::cout<< "1 - Search by NIF\n";
    std::cout<< "2 - Search by Name\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        switch (search_client_nif(client))
        {
          case 0:
            change_client_menu(client);
            break;

          case 1:
            std::cout<< "Could not find with given NIF client!\n";
            break;

          default:
            break;
        }
        break;

      case 2:
        switch (search_client_name(client))
        {
          case 0:
            change_client_menu(client);
            break;
        
          case 1:
            std::cout<< "More than one client found with given name!\n";
            break;

          case -1:
            std::cout<< "Could not find client with specified name!\n";
            break;
            
          default:
            break;
        }
        break;

      default:
        break;
    }
  }
}

bool purchase_pack(Client &client){
  int id = -1;
  std::string str_aux;
  TravelPack pack;
  std::vector <unsigned int> packs_bought;

  std::cout<< "Travel Pack ID: ";
  read_line(str_aux);
  while(string_to_int(str_aux, id) == false || id < 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Travel Pack ID: ";
    read_line(str_aux);
  }

  if(!agency.searchTravelPackId(id, pack)) std::cout<< "Travel Pack with ID: " << id << " not found!\n";
  else {
    packs_bought = client.getTourPacksBought();
    
    if(pack.getAvailability() == false) {
      std::cout<< "This pack is not available for purchase!\n";
      return false;
    }
    
    if( (pack.getPeopleLimit() - pack.getNumberSold()) <= 0 ) {
      std::cout<< "This pack has no more seats available for purchase!\n";
      return false;
    }

    /*if(*/client.addPack(id);/* == false){
      std::cerr << "This client has already purchased this pack!\n";
      return false;
    }*/
    pack.setNumberSold(pack.getNumberSold() + 1);
    agency.changeTravelPack(pack, pack.getPackId());
    /*if(*/agency.changeClient(client, client.getNif());/* == false) {
      std::cerr << "Failled to purchase the pack for the client!\n";
      return false;
    }*/
    return true;
  }
  return false;
}

void purchase_client_nif(){
  int nif = -1;
  std::string str_aux;
  Client client;

  std::cout<< "NIF: ";
  read_line(str_aux);
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "NIF: ";
    read_line(str_aux);
  }

  

  if(agency.searchClientNif((unsigned int)nif, client) == true){
    if(purchase_pack(client) == true){
      agency.changeClient(client, nif);
      modified_client = true;
    } 
    print_wait_menu();
  }
  else std::cout<< "Client with NIF: " << nif << " not found!\n";
}

void purchase_client_name(){
  std::vector<Client> vec;
  std::string name;

  std::cout<< "Name: "; read_line(name); 

  vec = agency.searchClientName(name);
  
  if(purchase_pack(vec.at(0)) == true){
    agency.changeClient(vec.at(0), vec.at(0).getNif());
    modified_client = true;
  } 
  else if(vec.size() > 1) std::cout<< "More than one client found with name: " << name << "\nPlease select another method of choosing a client\n";
  else if(vec.size() == 0) std::cout<< "Client with name:" << name << " not found!\n";
  
  print_wait_menu();
}

void purchase_client_menu(){
  int answer = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Purchase Travel Pack Menu");
    std::cout<< "1 - Search Client by NIF\n";
    std::cout<< "2 - Search Client by Name\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        purchase_client_nif();
        break;

      case 2:
        purchase_client_name();
        break;

      default:
        break;
    }
  }
}

void clients_menu(){
  int answer = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Clients Menu");
    std::cout<< "1 - View Clients\n";
    std::cout<< "2 - Add New Client\n";
    std::cout<< "3 - Change Clients\n";
    std::cout<< "4 - Purchase a Pack for a Client\n";   
    std::cout<< "5 - View All Travel Packs Purchased\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 5){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        print_clients_menu();
        break;

      case 2:
        add_client();
        break;

      case 3:
        change_clients_menu();
        break;

      case 4:
        purchase_client_menu();
        break;

      case 5:
        print_clients_all_travel_packs();
        break;

      default:
        break;
    }
  }
}

//End Clients
//Begin Travel Packs

bool search_travel_pack(int &id, TravelPack &pack){
  std::string str_aux;

  std::cout<< "Travel Pack ID: ";
  read_line(str_aux);
  while(string_to_int(str_aux, id) == false || id < 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Travel Pack ID: ";
    read_line(str_aux);
  }

  return agency.searchTravelPackId(id, pack);
}

void print_all_travel_pack(){
  std::vector<TravelPack> vec = agency.getTourPacks();
  int packs_counter = 0;
  
  for(size_t i = 0; i < vec.size(); i++, packs_counter++){
    if(packs_counter == 5){
      print_wait_menu();
      packs_counter = 0;
    }
    vec.at(i).show(std::cout);
    std::cout<< std::endl;
  }
  print_wait_menu();
}

void print_all_travel_pack_destination(){
  std::vector<TravelPack> vec;
  std::string destination;

  std::cout<< "Destination: "; read_line(destination); 
  std::cout<< std::endl;

  vec = agency.searchTravelPackDestination(destination);

  if(vec.size() == 0) std::cout<< "Travel Packs with destination:" << destination << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      vec.at(i).show(std::cout);
}

void print_all_travel_pack_dates(){
  std::vector<TravelPack> vec;
  Date init_date, final_date;
  std::string str_aux;

  do {
    std::cout<< "Initial Date: "; read_line(str_aux); 

    try {
      init_date.setDate(str_aux);
      break;
    }
    catch(std::string) {
      std::cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      std::cout<< "Initial Date: ";  read_line(str_aux);
    }
  }  while(1);

  init_date.setDate(str_aux);

  do {
    std::cout<< "Final Date: "; read_line(str_aux); 

    try {
      final_date.setDate(str_aux);
      break;
    }
    catch(std::string) {
      std::cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      std::cout<< "Final Date: "; read_line(str_aux);
    }
  }  while(1);

  final_date.setDate(str_aux);

  std::cout<< std::endl;

  vec = agency.searchTravelPackDates(init_date, final_date);

  if(vec.size() == 0) std::cout<< "Travel Packs with dates raging from " << init_date << " to " << final_date << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      vec.at(i).show(std::cout);

}

void print_all_travel_pack_destination_dates(){
  std::vector<TravelPack> vec;
  Date init_date, final_date;
  std::string str_aux;
  std::string destination;
  bool found = false;

  std::cout<< "Destination: "; read_line(destination); 

  do {
    std::cout<< "Initial Date: "; read_line(str_aux); 

    try {
      init_date.setDate(str_aux);
      break;
    }
    catch(std::string) {
      std::cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      std::cout<< "Initial Date: ";  read_line(str_aux);
    }
  }  while(1);

  do {
    std::cout<< "Final Date: "; read_line(str_aux); 

    try {
      final_date.setDate(str_aux);
      break;
    }
    catch(std::string) {
      std::cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      std::cout<< "Final Date: "; read_line(str_aux);
    }
  }  while(1);


  std::cout<< std::endl;

  vec = agency.searchTravelPackDates(init_date, final_date);

  if(vec.size() == 0) std::cout<< "Travel Packs with dates raging from " << init_date << " to " << final_date << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      if(vec.at(i).getDestination() == destination){
        vec.at(i).show(std::cout);
        found = true;
      }

  else if(found == false) std::cout<< "Travel Packs with destination:" << destination << " not found!\n";
}

void print_travel_pack_menu(){
  int answer = 0;
  TravelPack search_pack;
  int id = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("View Travel Packs Menu");
    std::cout<< "1 - All\n";
    std::cout<< "2 - All to Destination\n";
    std::cout<< "3 - All from date to date\n";
    std::cout<< "4 - All to Destination and from date to date\n";
    std::cout<< "5 - Single Travel Pack\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 5){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        print_all_travel_pack();
        break;

      case 2:
        print_all_travel_pack_destination();
        break;

      case 3:
        print_all_travel_pack_dates();
        break;

      case 4:
        print_all_travel_pack_destination_dates();
        break;

      case 5:
        if(!search_travel_pack(id, search_pack)) std::cout<< "Travel Pack with ID: " << id << " not found!\n";
        else {
          search_pack.show(std::cout);
          print_wait_menu();
        }

        break;

      default:
        break;
    }
  }
}

void change_travel_pack_init_date(TravelPack &travel_pack){
  std::string str_aux;

  do {
    std::cout<< "Initial Date: "; read_line(str_aux); 

    try {
      travel_pack.setInitDate(str_aux);
      break;
    }
    catch(std::string) {
      std::cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      std::cout<< "Initial Date: ";  read_line(str_aux);
    }
  }  while(1);

}

void change_travel_pack_final_date(TravelPack &travel_pack){
  std::string str_aux;
  Date date_aux;

  do {
    std::cout<< "Final Date: "; read_line(str_aux); 

    try {
      travel_pack.setFinalDate(str_aux);
      break;
    }
    catch(std::string) {
      std::cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      std::cout<< "Final Date: "; read_line(str_aux);
    }
  }  while(1);
}

void change_travel_pack_destination(TravelPack &travel_pack){
  std::string str_aux;
  std::cout<< "Destination: "; read_line(str_aux);

  travel_pack.setDestination(str_aux);
}

void change_travel_pack_cities(TravelPack &travel_pack){
  std::string str_aux;
  std::vector<std::string> cities;

  std::cout<< "Cities (Separated by , or - for none): "; read_line(str_aux);

  if(str_aux.compare("-") == 0) cities.resize(0);
  else decompose(str_aux, cities, ',');

  travel_pack.setCities(cities);
}

void change_travel_pack_price(TravelPack &travel_pack){
  int price = -1;
  std::string str_aux;
  std::cout<< "Price: "; read_line(str_aux);
  while(string_to_int(str_aux, price) == false || price < 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Price: "; read_line(str_aux);
  }

  travel_pack.setPrice(price);
}

void change_travel_pack_people_limit(TravelPack &travel_pack){
  int people_limit = -1;
  std::string str_aux;
  std::cout<< "Number of seats available: "; read_line(str_aux);
  while(string_to_int(str_aux, people_limit) == false || people_limit < 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Number of seats available: "; read_line(str_aux);
  }

  travel_pack.setPeopleLimit(people_limit);
}

void change_travel_pack_num_sold(TravelPack &travel_pack){
  int num_sold = -1;
  std::string str_aux;

  std::cout<< "Number of seats sold: "; read_line(str_aux);
  while(!string_to_int(str_aux, num_sold) || num_sold < 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Number of seats sold: "; read_line(str_aux);
  }

  travel_pack.setNumberSold(num_sold);
}

void change_travel_pack_available(TravelPack &travel_pack){
  std::string str_aux;
  std::cout<< "Available(Yes/No): "; read_line(str_aux); 
  while(str_aux.compare("Yes") != 0 && str_aux.compare("No") != 0){
    std::cout<< "Invalid Input\n";
    std::cout<< "Available(Yes/No): "; read_line(str_aux);
  }

  if(str_aux.compare("Yes") == 0) travel_pack.setAvailability(true);
  else if(str_aux.compare("No") == 0) travel_pack.setAvailability(false);
}

void add_travel_pack(){
  TravelPack new_pack;
  TravelPack search_pack;
  int id = -1;
  std::string str_aux;

  std::cout<< "Travel Pack ID: ";
  read_line(str_aux);
  while(string_to_int(str_aux, id) == false || id < 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Travel Pack ID: ";
    read_line(str_aux);
  }
  new_pack.setPackId(id);

  if(agency.searchTravelPackId(id, search_pack)){
    std::cerr << "Travel Pack with ID: " << id << " already exists!\n";
    print_wait_menu();
    return;
  }

  change_travel_pack_destination(new_pack);
  change_travel_pack_cities(new_pack);
  change_travel_pack_init_date(new_pack);
  change_travel_pack_final_date(new_pack);
  if(new_pack.getInitDate() > new_pack.getFinalDate()){
    std::cerr << "Invalid dates: initial date must be before final date!\n";
    print_wait_menu();
    return;
  }
  change_travel_pack_price(new_pack);
  change_travel_pack_people_limit(new_pack);
  change_travel_pack_num_sold(new_pack);
  if(new_pack.getNumberSold() > new_pack.getPeopleLimit()){
    std::cerr << "Invalid seats numbers: number of total seats available must higher or equal to number of seats sold!\n";
    print_wait_menu();
    return;
  }
  change_travel_pack_available(new_pack);

  /*if(*/agency.addTravelPack(new_pack.getInitDate().getDate(), new_pack.getFinalDate().getDate(), new_pack.getDestination(), new_pack.getCities(), new_pack.getAvailability(), new_pack.getPackId(), new_pack.getPrice(), new_pack.getPeopleLimit(), new_pack.getNumberSold());/* == false){
    std::cerr << "Failled to add travel pack: travel pack with ID: " << id << " already exists\n";
  }
  else modified_travel_pack = true;*/

  print_wait_menu();
}

void change_travel_pack_menu(TravelPack &travel_pack){
  int answer = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Change Travel Pack Menu");
    std::cout<< "1 - All\n";
    std::cout<< "2 - Destination\n";
    std::cout<< "3 - Cities\n";
    std::cout<< "4 - Initial Date\n";
    std::cout<< "5 - Final Date\n";
    std::cout<< "6 - Price\n";
    std::cout<< "7 - Seats Available\n";
    std::cout<< "8 - Seats Sold\n";
    std::cout<< "9 - Availability\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 9){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        change_travel_pack_destination(travel_pack);
        change_travel_pack_cities(travel_pack);
        change_travel_pack_init_date(travel_pack);
        change_travel_pack_final_date(travel_pack);
        change_travel_pack_price(travel_pack);
        change_travel_pack_people_limit(travel_pack);
        change_travel_pack_num_sold(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      case 2:
        change_travel_pack_destination(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: destination is invalid!\n";
        break;

      case 3:
        change_travel_pack_cities(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: no repeated cities allowed!\n";
        break;

      case 4:
        change_travel_pack_init_date(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      case 5:
        change_travel_pack_final_date(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      case 6:
        change_travel_pack_price(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      case 7:
        change_travel_pack_people_limit(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: total seats available must be higher than seats sold!\n";
        break;

      case 8:
        change_travel_pack_num_sold(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: total seats available must be higher than seats sold!\n";
        break;

      case 9:
        change_travel_pack_available(travel_pack);
        /*if(*/agency.changeTravelPack(travel_pack, travel_pack.getPackId());// == true) modified_travel_pack = true;
        //else std::cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      default:
        break;
    }
  }
}

void travel_packs_menu(){
  TravelPack search_pack;
  int answer = 0;
  int id = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Travel Packs Menu");
    std::cout<< "1 - View Travel Packs\n";
    std::cout<< "2 - Add New Travel Pack\n";
    std::cout<< "3 - Change Travel Pack\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 3){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        print_travel_pack_menu();
        break;

      case 2:
        add_travel_pack();
        break;

      case 3:
        if(!search_travel_pack(id, search_pack)) std::cout<< "Travel Pack with ID: " << id << " not found!\n";
        else {
          change_travel_pack_menu(search_pack);
          /*if(*/agency.changeTravelPack(search_pack, id) ;/*== true) modified_travel_pack = true;
          else std::cout<< "Failled to modify travel pack!\n";*/
        }
        break;

      default:
        break;
    }
  }
}

//End Travel Packs
//Begin Statistics

void print_most_visited_places(){
  std::multimap<unsigned int, std::string> mp = agency.mostVisitedPlaces();
  std::string str_aux;
  int number_places = -1;

  std::cout<< "Number of Places: "; read_line(str_aux);
  while(!string_to_int(str_aux, number_places) || number_places < 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Number of Places: "; read_line(str_aux);
  }

  auto it = mp.begin();
  for(int i = 0; i < number_places && it != mp.end(); i++, it++)
    std::cout<< "Most visited place number " << i+1 << ": " << (*it).second << " visited a total of " << (*it).first << " times\n";

  std::cout<< std::endl;
}

void print_most_visited_places_clients(){
  std::multimap<unsigned int, std::string> mp = agency.mostVisitedPlaces();
  std::string str_aux;
  int number_places = -1;
  std::vector <TravelPack> packs_with_city;
  std::vector <Client> clients = agency.getClientList();
  std::vector <unsigned int> packs_bought;
  std::vector <TravelPack> clients_pack(clients.size()); //pack for every client people_limit = 0 == none
  

  std::cout<< "Number of Places: "; read_line(str_aux);
  while(!string_to_int(str_aux, number_places) || number_places < 0){
    std::cerr << "Invalid intput!\n\n";
    std::cout<< "Number of Places: "; read_line(str_aux);
  }

  auto it = mp.begin();
  for(int i = 0; i < number_places && it != mp.end(); i++, it++){
    packs_with_city = agency.searchTravelPackCity((*it).second);

    for(size_t j = 0; j < clients.size(); j++){

      if(!(clients_pack.at(j).getPeopleLimit() != 0)) continue;
      packs_bought = clients.at(j).getTourPacksBought();

      for(size_t k = 0; k < packs_bought.size(); k++){
        if(!(clients_pack.at(j).getPeopleLimit != 0)) break;
        //find pack from all packs that have the city with same id as the pack bought by the client

        if( find(packs_with_city.begin(), packs_with_city.end(), packs_bought.at(k)) == packs_with_city.end() ){
        //could not find == client has not visited the city!
          if(packs_with_city.size() != 0){
            clients_pack.at(j) = packs_with_city.at(0);
            break;
          }
        }

      }

    }
    
  }

  for(size_t i = 0; i < clients.size(); i++){
    clients.at(i).show(std::cout);
    std::cout<< "Recommstd::endl pack: \n";
    if(clients_pack.at(i).getPeopleLimit() != 0)
      clients_pack.at(i).show(std::cout);
    else
      std::cout<< "None\n";

    std::cout<< std::endl;
  }


  std::cout<< std::endl;
}

void statistics_menu(){
  TravelPack search_pack;
  int answer = 0;
  int id = 0;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Statistics Menu");
    std::cout<< "1 - Most Visited Places\n";
    std::cout<< "2 - Clients Who Visited a Most Visited Place\n";
    std::cout<< "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        print_most_visited_places();
        break;

      case 2:
        print_most_visited_places_clients();
        break;

      default:
        break;
    }
  }
}

//End Statistics

void start_menu(){
  int answer;

  while(1){ //only std::endls when 0 is typed
    print_first_lines("Main Menu");
    std::cout<< "1 - Agency\n";
    std::cout<< "2 - Clients\n";
    std::cout<< "3 - Travel Packs\n";
    std::cout<< "4 - Statistics\n";
    std::cout<< "0 - Exit\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 4){
      std::cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer){
      case 0:
        return;

      case 1:
        agency_menu();
        break;

      case 2:
        clients_menu();
        break;

      case 3:
        travel_packs_menu();
        break;

      case 4:
        statistics_menu();
        break;
    }
  }
}
