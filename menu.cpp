#include <iostream>
#include <iomanip>
#include "menu.h"
#include "agency.h"
#include "StringFunctions.h"

#define MAX_NIF 999999999
#define INT_MAX 2147483647

extern Agency agency;

using namespace std;

extern bool modified_agency, modified_client, modified_travel_pack;

//General Functions

void read_line(string &s){
  cin.clear();
  fflush(stdin);
  getline(cin, s);
  while(s.size() == 0)
    getline(cin, s);  
}

void print_first_lines(const char *array){
  cout << "\n==============================\n";
  cout << "\t" << array;
  cout << "\n==============================\n";
}

void print_last_line(){
  cout << "==============================\n\n";
}

void print_wait_menu(){
  string str_aux;
  cin.clear();
  fflush(stdin);
  cout << "\nPress enter to continue... ";
  getline(cin, str_aux);
  cout << endl;
}

int scan_single_int(){
  int scan = 0;
  string str_aux;

  cout << "Please type in a number: ";
  read_line(str_aux);  
  while(string_to_int(str_aux, scan) == false || scan < 0 || scan > 9){
    cerr << "Invalid intput!\n\n";
    cout << "Please type in a number: ";
    read_line(str_aux);  
  }
  return scan;
}

void print_agency(){
  cout << "Name: " << agency.getName() << endl;
  cout << "URL: " << agency.getUrl() << endl;
  cout << "Address: " << agency.getAddress().getAddressString() << endl;
  cout << "NIF: " << agency.getNif() << endl;

  print_wait_menu();
}

void print_client(Client &client){
  cout << "Name: " << client.getName() << endl;
  cout << "Address: " << client.getAddress().getAddressString() << endl;
  cout << "Tour Packs Bought: ";
  if(client.getTourPacksBought().size() == 0) cout << "None";
  else for(size_t i = 0; i < client.getTourPacksBought().size(); i++){
    cout << client.getTourPacksBought().at(i) << " ";
  }
  cout << endl;
  cout << "NIF: " << client.getNif() << endl;
  cout << "Family Number: " << client.getFamilyNum() << endl;
}

void print_travel_pack(TravelPack &travel_pack){
  
  cout << "ID: " << travel_pack.getPackId() << endl;
  cout << "Destination: " << travel_pack.getDestination() << endl;
  cout << "Route: ";
  if(travel_pack.getCities().size() > 0){
      cout  << travel_pack.getCities().at(0);
    for(size_t i = 1; i < travel_pack.getCities().size(); i++)
      cout  << ", " << travel_pack.getCities().at(i);
  }
  cout << endl;
  cout << "Initial Date: " << travel_pack.getInitDate() << endl;
  cout << "Final Date: " << travel_pack.getFinalDate() << endl;
  cout << "Price: " << travel_pack.getPrice() << endl;
  cout << "Number of seats total: " << travel_pack.getPeopleLimit() << endl;
  cout << "Number of seats sold: " << travel_pack.getNumberSold() << endl;
  cout << "Available: ";
  if(travel_pack.getAvailability() == true) cout << "Yes\n";
  else cout << "No\n";
}

//Begin Agency

void print_address_struct(){
  cout << "(Street Name) / (Door Number) / (Floor) / (Zip Code) / (City)\n";
}

void change_agency_name(){
  string str_aux;
  cout << "Name: "; read_line(str_aux); 
  agency.setName(str_aux);
  modified_agency = true;
}

void change_agency_nif(){
  int nif = -1;
  string str_aux;

  cout << "NIF: "; read_line(str_aux);
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    cerr << "Invalid intput!\n\n";
    cout << "NIF: "; read_line(str_aux);
  }

  agency.setNif(nif);
  modified_agency = true;
}

void change_agency_address(){
  string str_aux;
  cout << "Address: "; read_line(str_aux);
  while(agency.setAddress(str_aux) == false){
    cout << "Invalid input!\nAddress must be typed in the following way: \n";
    print_address_struct();
    cout << "Address: "; read_line(str_aux);
  }
  modified_agency = true;
}

void change_agency_url(){
  string str_aux;

  cout << "URL: "; read_line(str_aux);

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

  while(1){ //only ends when 0 is typed
    print_first_lines("Change Agency Menu");
    cout << "1 - All\n";
    cout << "2 - Name\n";
    cout << "3 - NIF\n";
    cout << "4 - Address\n";
    cout << "5 - URL\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 5){
      cerr << "Invalid intput!\n\n";
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
  vector<TravelPack> packs = agency.getTourPacks();
  long gains = 0, num_sold = 0;
  
  for(size_t i = 0; i < packs.size(); i++){
    num_sold += packs.at(i).getNumberSold();
    gains += packs.at(i).getNumberSold() * packs.at(i).getPrice();
  }

  cout << endl << "Number of packs sold: " << num_sold << endl;
  cout << "Total amount of gains: " << gains << endl << endl;
  print_wait_menu();
}

void agency_menu(){
  int answer = 0;

  while(1){ //only ends when 0 is typed
    print_first_lines("Agency Menu");
    cout << "1 - View\n";
    cout << "2 - Change\n";
    cout << "3 - Calculate Gains\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 3){
      cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        print_agency();
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
  vector<Client> vec;
  string name;

  cout << "Name: "; read_line(name); 

  vec = agency.searchClientName(name);
  
  if(vec.size() == 1) client = vec.at(0);
  else if(vec.size() > 1) return 1;
  else return -1;

  return 0;
}

int search_client_nif(Client &client){
  int nif = 0;
  string str_aux;

  cout << "NIF: ";
  read_line(str_aux);
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    cerr << "Invalid intput!\n\n";
    cout << "NIF: ";
    read_line(str_aux);
  }



  if(!agency.searchClientNif(nif, client)) return -1;

  return 0;
}

void print_client_packs(Client &client){
  vector<unsigned int>tour_packs_ids = client.getTourPacksBought();
  TravelPack pack;

  if(tour_packs_ids.size() == 0) cout << "This client does not have any purchased packs\n";
  else{
    for(size_t i = 0; i < tour_packs_ids.size(); i++){
      if(agency.searchTravelPackId(tour_packs_ids.at(i), pack) == false) cout << "Travel Pack with ID: " << tour_packs_ids.at(i) << " could not be found\n";
      else print_travel_pack(pack);
    }
  }
}

void print_client_selected(Client &client){
    int answer = 0;

  while(1){ //only ends when 0 is typed
    print_first_lines("Selected Client Menu");
    cout << "1 - View Client Details\n";
    cout << "2 - View Packs Bought\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      cerr << "Invalid intput!\n\n";
      answer = scan_single_int();
    }
    
    switch (answer)
    {
      case 0:
        return;

      case 1:
        print_client(client);
        break;

      case 2:
        print_client_packs(client);
        break;

      default:
        break;
    }
  }
}

void print_client_selected(vector<Client> &client_vec){
  if(client_vec.size() > 1) cout << "More than one client found!\nPlease select the client wanted by another parameter\n";
  else print_client_selected(client_vec.at(0));
}

void print_single_client(){
  int answer = 0;
  Client client;

  while(1){ //only ends when 0 is typed
    print_first_lines("Single Client View Menu");
    cout << "1 - Search by NIF\n";
    cout << "2 - Search by Name\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      cerr << "Invalid intput!\n\n";
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
            cout << "Could not find client!\n";
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
            cout << "More than one client found with given name!\n";
            break;

          case -1:
            cout << "Could not find client with specified name!\n";
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
  vector<Client> vec = agency.getClientList();
  size_t client_counter = 0;

  for(size_t i = 0; i < vec.size(); i++, client_counter++){
    if(client_counter == 4){
      client_counter = 0; //reset counter
      print_wait_menu();
    }
    print_client(vec.at(i));
    cout << endl;
  }

  print_wait_menu();
}

void print_clients_all_travel_packs(){
  vector<Client> client_list = agency.getClientList();
  vector<unsigned int> client_packs_bought;
  vector<unsigned int> tour_packs_ids;
  TravelPack pack;
  bool already_exists = false;
  int pack_count = 0;

  for(size_t i = 0; i < client_list.size(); i++){ //For every client
    client_packs_bought = client_list.at(i).getTourPacksBought();
    for(size_t j = 0; j < client_packs_bought.size(); j++){ //Search each client
      for(size_t k = 0; k < tour_packs_ids.size(); k++){ //Verify for every id
        if(tour_packs_ids.at(k) == client_packs_bought.at(j)){ //Id is already in tour_packs_ids vector
          already_exists = true;
          break;
        }
      }
      if(already_exists == true) continue;
      else tour_packs_ids.push_back(client_packs_bought.at(j));
      already_exists = false;
    }
  }

  if(tour_packs_ids.size() == 0) cout << "No packs were purchased by any client\n";
  else{
    for(size_t i = 0; i < tour_packs_ids.size(); i++, pack_count++){
      if(pack_count == 5) print_wait_menu();

      if(!agency.searchTravelPackId(tour_packs_ids.at(i), pack)) cout << "Travel Pack with ID: " << tour_packs_ids.at(i) << " could not be found\n";
      else print_travel_pack(pack); 
      cout << endl;             
    }
  }

  print_wait_menu();
}

void print_clients_menu(){
  int answer = 0;

  while(1){ //only ends when 0 is typed
    print_first_lines("View Clients Menu");
    cout << "1 - All Clients\n";
    cout << "2 - Single Client\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      cerr << "Invalid intput!\n\n";
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
  string str_aux;
  cout << "Name: "; 
  read_line(str_aux); 

  client.setName(str_aux);
}

void change_client_address(Client &client){
  string str_aux;
  cout << "Address: "; read_line(str_aux);
  while(client.setAddress(str_aux) == false){
    cout << "Invalid input!\nAddress must be typed in the following way: \n";
    print_address_struct();
    cout << "Address: "; read_line(str_aux);
  }
}

void change_client_packs_bought(Client &client){
  string str_aux;

  cout << "Tour packs bought: "; read_line(str_aux);
  while(client.setTourPacks(str_aux, ';') == false){
    cout << "Invalid intput!\nPlease type tour packs bought in the following order:\n";
    cout << "(Tour Pack Id 1) ; (Tour Pack Id 2); ... ; (Tour Pack Id n) or - for no packs\n";
    cout << "Tour packs bought: ";
    read_line(str_aux);
  }
}

bool change_client_nif(Client &client){
  int nif = -1;
  string str_aux;
  Client search_aux;

  cout << "NIF: "; read_line(str_aux);

  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    cerr << "Invalid intput!\n\n";
    cout << "NIF: "; read_line(str_aux);
  }

  if(agency.searchClientNif((unsigned int)nif, search_aux) == true){
    cerr << "Invalid Input!\nClient with NIF: " << nif << " already exists!\n";
    return false;
  }

  client.setNif(nif);
  return true;
}

void change_client_family_num(Client &client){
  int family_num = -1;
  string str_aux;

  cout << "Family Number: "; read_line(str_aux);
  while(string_to_int(str_aux, family_num) == false || family_num <= 0){
    cerr << "Invalid intput!\n\n";
    cout << "Family Number: "; read_line(str_aux);
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

  if(agency.addClient(new_client) == false){
    cerr << "Failled to add client: some parameters were wrong\n";
  }
  modified_client = true;

  print_wait_menu();
}

void change_client_menu(Client &client){
  int answer = 0;
  int old_nif = client.getNif();

  while(1){ //only ends when 0 is typed
    print_first_lines("Change Client Selected Menu");
    cout << "1 - All\n";
    cout << "2 - Name\n";
    cout << "3 - NIF\n";
    cout << "4 - Address\n";
    cout << "5 - Tour Packs Bought\n";
    cout << "6 - Family Number\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 6){
      cerr << "Invalid intput!\n\n";
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
        if(agency.changeClient(client, old_nif) == true) modified_client = true;
        else cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      case 2:
        change_client_name(client);
        if(agency.changeClient(client, old_nif) == true) modified_client = true;
        else cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      case 3:
        if(change_client_nif(client) == false) break;
        if(agency.changeClient(client, old_nif) == true) modified_client = true;
        else cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      case 4:
        change_client_address(client);
        if(agency.changeClient(client, old_nif) == true) modified_client = true;
        else cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      case 5:
        change_client_packs_bought(client);
        if(agency.changeClient(client, old_nif) == true) modified_client = true;
        else cerr << "Failled to modify client: invalid packs entered!\n";
        break;

      case 6:
        change_client_family_num(client);
        if(agency.changeClient(client, old_nif) == true) modified_client = true;
        else cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      default:
        break;
    }
  }
}

void change_clients_menu(){
  int answer = 0;
  Client client;

  while(1){ //only ends when 0 is typed
    print_first_lines("Change Clients Menu");
    cout << "1 - Search by NIF\n";
    cout << "2 - Search by Name\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      cerr << "Invalid intput!\n\n";
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
            cout << "Could not find with given NIF client!\n";
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
            cout << "More than one client found with given name!\n";
            break;

          case -1:
            cout << "Could not find client with specified name!\n";
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
  string str_aux;
  TravelPack pack;
  vector <unsigned int> packs_bought;

  cout << "Travel Pack ID: ";
  read_line(str_aux);
  while(string_to_int(str_aux, id) == false || id < 0){
    cerr << "Invalid intput!\n\n";
    cout << "Travel Pack ID: ";
    read_line(str_aux);
  }

  if(!agency.searchTravelPackId(id, pack)) cout << "Travel Pack with ID: " << id << " not found!\n";
  else {
    packs_bought = client.getTourPacksBought();
    
    if(pack.getAvailability() == false) {
      cout << "This pack is not available for purchase!\n";
      return false;
    }
    
    if( (pack.getPeopleLimit() - pack.getNumberSold()) <= 0 ) {
      cout << "This pack has no more seats available for purchase!\n";
      return false;
    }

    if(client.addPack(id) == false){
      cerr << "This client has already purchased this pack!\n";
      return false;
    }
    pack.setNumberSold(pack.getNumberSold() + 1);
    agency.changeTravelPack(pack, pack.getPackId());
    if(agency.changeClient(client, client.getNif()) == false) {
      cerr << "Failled to purchase the pack for the client!\n";
      return false;
    }
    return true;
  }
  return false;
}

void purchase_client_nif(){
  int nif = -1;
  string str_aux;
  Client client;

  cout << "NIF: ";
  read_line(str_aux);
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    cerr << "Invalid intput!\n\n";
    cout << "NIF: ";
    read_line(str_aux);
  }

  

  if(agency.searchClientNif((unsigned int)nif, client) == true){
    if(purchase_pack(client) == true){
      agency.changeClient(client, nif);
      modified_client = true;
    } 
    print_wait_menu();
  }
  else cout << "Client with NIF: " << nif << " not found!\n";
}

void purchase_client_name(){
  vector<Client> vec;
  string name;

  cout << "Name: "; read_line(name); 

  vec = agency.searchClientName(name);
  
  if(purchase_pack(vec.at(0)) == true){
    agency.changeClient(vec.at(0), vec.at(0).getNif());
    modified_client = true;
  } 
  else if(vec.size() > 1) cout << "More than one client found with name: " << name << "\nPlease select another method of choosing a client\n";
  else if(vec.size() == 0) cout << "Client with name:" << name << " not found!\n";
  
  print_wait_menu();
}

void purchase_client_menu(){
  int answer = 0;

  while(1){ //only ends when 0 is typed
    print_first_lines("Purchase Travel Pack Menu");
    cout << "1 - Search Client by NIF\n";
    cout << "2 - Search Client by Name\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 2){
      cerr << "Invalid intput!\n\n";
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

  while(1){ //only ends when 0 is typed
    print_first_lines("Clients Menu");
    cout << "1 - View Clients\n";
    cout << "2 - Add New Client\n";
    cout << "3 - Change Clients\n";
    cout << "4 - Purchase a Pack for a Client\n";   
    cout << "5 - View All Travel Packs Purchased\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 5){
      cerr << "Invalid intput!\n\n";
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
  string str_aux;

  cout << "Travel Pack ID: ";
  read_line(str_aux);
  while(string_to_int(str_aux, id) == false || id < 0){
    cerr << "Invalid intput!\n\n";
    cout << "Travel Pack ID: ";
    read_line(str_aux);
  }

  return agency.searchTravelPackId(id, pack);
}

void print_all_travel_pack(){
  vector<TravelPack> vec = agency.getTourPacks();
  int packs_counter = 0;
  
  for(size_t i = 0; i < vec.size(); i++, packs_counter++){
    if(packs_counter == 5){
      print_wait_menu();
      packs_counter = 0;
    }
    print_travel_pack(vec.at(i));
    cout << endl;
  }
  print_wait_menu();
}

void print_all_travel_pack_destination(){
  vector<TravelPack> vec;
  string destination;

  cout << "Destination: "; read_line(destination); 
  cout << endl;

  vec = agency.searchTravelPackDestination(destination);

  if(vec.size() == 0) cout << "Travel Packs with destination:" << destination << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      print_travel_pack(vec.at(i));
}

void print_all_travel_pack_dates(){
  vector<TravelPack> vec;
  Date init_date, final_date;
  string str_aux;
  bool valid = false;

  do {
    cout << "Initial Date: "; read_line(str_aux); 
    while(!init_date.validSet(str_aux)){
      cout << "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout << "Initial Date: ";  read_line(str_aux);
    }
    init_date.setDate(str_aux);

    cout << "Final Date: "; read_line(str_aux); 
    while(!final_date.validSet(str_aux)){
      cout << "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout << "Final Date: "; read_line(str_aux);
    }
    final_date.setDate(str_aux);

    if(init_date > final_date){
      cout << "Invalid dates entered!\n";
      valid = false;
    }
  } while(!valid);


  cout << endl;

  vec = agency.searchTravelPackDates(init_date, final_date);

  if(vec.size() == 0) cout << "Travel Packs with dates raging from " << init_date << " to " << final_date << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      print_travel_pack(vec.at(i));

}

void print_all_travel_pack_destination_dates(){
  vector<TravelPack> vec;
  Date init_date, final_date;
  string str_aux;
  string destination;
  bool found = false;
  bool valid = false;

  cout << "Destination: "; read_line(destination); 

  do {
    cout << "Initial Date: "; read_line(str_aux); 
    while(!init_date.validSet(str_aux)){
      cout << "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout << "Initial Date: ";  read_line(str_aux);
    }
    init_date.setDate(str_aux);

    cout << "Final Date: "; read_line(str_aux); 
    while(!final_date.validSet(str_aux)){
      cout << "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout << "Final Date: "; read_line(str_aux);
    }
    final_date.setDate(str_aux);

    if(init_date > final_date){
      cout << "Invalid dates entered!\n";
      valid = false;
    }
  } while(!valid);

  cout << endl;

  vec = agency.searchTravelPackDates(init_date, final_date);

  if(vec.size() == 0) cout << "Travel Packs with dates raging from " << init_date << " to " << final_date << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      if(vec.at(i).getDestination() == destination){
        print_travel_pack(vec.at(i));
        found = true;
      }

  else if(found == false) cout << "Travel Packs with destination:" << destination << " not found!\n";
}

void print_travel_pack_menu(){
  int answer = 0;
  TravelPack search_pack;
  int id = 0;

  while(1){ //only ends when 0 is typed
    print_first_lines("View Travel Packs Menu");
    cout << "1 - All\n";
    cout << "2 - All to Destination\n";
    cout << "3 - All from date to date\n";
    cout << "4 - All to Destination and from date to date\n";
    cout << "5 - Single Travel Pack\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 5){
      cerr << "Invalid intput!\n\n";
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
        if(!search_travel_pack(id, search_pack)) cout << "Travel Pack with ID: " << id << " not found!\n";
        else {
          print_travel_pack(search_pack);
          print_wait_menu();
        }

        break;

      default:
        break;
    }
  }
}

void change_travel_pack_init_date(TravelPack &travel_pack){
  string str_aux;
  Date date_aux;

  cout << "Initial Date: "; read_line(str_aux);
  while(!date_aux.validSet(str_aux)){
    cout << "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
    cout << "Initial Date: ";  read_line(str_aux);
  }
  date_aux.setDate(str_aux);

  travel_pack.setInitDate(date_aux);
}

void change_travel_pack_final_date(TravelPack &travel_pack){
  string str_aux;
  Date date_aux;

  cout << "Final Date: "; read_line(str_aux); 
  while(!date_aux.validSet(str_aux)){
    cout << "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
    cout << "Final Date: "; read_line(str_aux);
  }
  date_aux.setDate(str_aux);

  travel_pack.setFinalDate(date_aux);
}

void change_travel_pack_destination(TravelPack &travel_pack){
  string str_aux;
  cout << "Destination: "; read_line(str_aux);

  travel_pack.setDestination(str_aux);
}

void change_travel_pack_cities(TravelPack &travel_pack){
  string str_aux;
  vector<string> cities;

  cout << "Cities (Separated by , or - for none): "; read_line(str_aux);

  if(str_aux.compare("-") == 0) cities.resize(0);
  else decompose(str_aux, cities, ',');

  travel_pack.setCities(cities);
}

void change_travel_pack_price(TravelPack &travel_pack){
  int price = -1;
  string str_aux;
  cout << "Price: "; read_line(str_aux);
  while(string_to_int(str_aux, price) == false || price < 0){
    cerr << "Invalid intput!\n\n";
    cout << "Price: "; read_line(str_aux);
  }

  travel_pack.setPrice(price);
}

void change_travel_pack_people_limit(TravelPack &travel_pack){
  int people_limit = -1;
  string str_aux;
  cout << "Number of seats available: "; read_line(str_aux);
  while(string_to_int(str_aux, people_limit) == false || people_limit < 0){
    cerr << "Invalid intput!\n\n";
    cout << "Number of seats available: "; read_line(str_aux);
  }

  travel_pack.setPeopleLimit(people_limit);
}

void change_travel_pack_num_sold(TravelPack &travel_pack){
  int num_sold = -1;
  string str_aux;

  cout << "Number of seats sold: "; read_line(str_aux);
  while(!string_to_int(str_aux, num_sold) || num_sold < 0){
    cerr << "Invalid intput!\n\n";
    cout << "Number of seats sold: "; read_line(str_aux);
  }

  travel_pack.setNumberSold(num_sold);
}

void change_travel_pack_available(TravelPack &travel_pack){
  string str_aux;
  cout << "Available(Yes/No): "; read_line(str_aux); 
  while(str_aux.compare("Yes") != 0 && str_aux.compare("No") != 0){
    cout << "Invalid Input\n";
    cout << "Available(Yes/No): "; read_line(str_aux);
  }

  if(str_aux.compare("Yes") == 0) travel_pack.setAvailability(true);
  else if(str_aux.compare("No") == 0) travel_pack.setAvailability(false);
}

void add_travel_pack(){
  TravelPack new_pack;
  TravelPack search_pack;
  int id = -1;
  string str_aux;

  cout << "Travel Pack ID: ";
  read_line(str_aux);
  while(string_to_int(str_aux, id) == false || id < 0){
    cerr << "Invalid intput!\n\n";
    cout << "Travel Pack ID: ";
    read_line(str_aux);
  }
  new_pack.setPackId(id);

  if(agency.searchTravelPackId(id, search_pack)){
    cerr << "Travel Pack with ID: " << id << " already exists!\n";
    print_wait_menu();
    return;
  }

  change_travel_pack_destination(new_pack);
  change_travel_pack_cities(new_pack);
  change_travel_pack_init_date(new_pack);
  change_travel_pack_final_date(new_pack);
  if(new_pack.getInitDate() > new_pack.getFinalDate()){
    cerr << "Invalid dates: initial date must be before final date!\n";
    print_wait_menu();
    return;
  }
  change_travel_pack_price(new_pack);
  change_travel_pack_people_limit(new_pack);
  change_travel_pack_num_sold(new_pack);
  if(new_pack.getNumberSold() > new_pack.getPeopleLimit()){
    cerr << "Invalid seats numbers: number of total seats available must higher or equal to number of seats sold!\n";
    print_wait_menu();
    return;
  }
  change_travel_pack_available(new_pack);

  if(agency.addTravelPack(new_pack) == false){
    cerr << "Failled to add travel pack: travel pack with ID: " << id << " already exists\n";
  }
  else modified_travel_pack = true;

  print_wait_menu();
}

void change_travel_pack_menu(TravelPack &travel_pack){
  int answer = 0;

  while(1){ //only ends when 0 is typed
    print_first_lines("Change Travel Pack Menu");
    cout << "1 - All\n";
    cout << "2 - Destination\n";
    cout << "3 - Cities\n";
    cout << "4 - Initial Date\n";
    cout << "5 - Final Date\n";
    cout << "6 - Price\n";
    cout << "7 - Seats Available\n";
    cout << "8 - Seats Sold\n";
    cout << "9 - Availability\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 9){
      cerr << "Invalid intput!\n\n";
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
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      case 2:
        change_travel_pack_destination(travel_pack);
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: destination is invalid!\n";
        break;

      case 3:
        change_travel_pack_cities(travel_pack);
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: no repeated cities allowed!\n";
        break;

      case 4:
        change_travel_pack_init_date(travel_pack);
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      case 5:
        change_travel_pack_final_date(travel_pack);
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      case 6:
        change_travel_pack_price(travel_pack);
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: some parameters were invalid!\n";
        break;

      case 7:
        change_travel_pack_people_limit(travel_pack);
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: total seats available must be higher than seats sold!\n";
        break;

      case 8:
        change_travel_pack_num_sold(travel_pack);
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: total seats available must be higher than seats sold!\n";
        break;

      case 9:
        change_travel_pack_available(travel_pack);
        if(agency.changeTravelPack(travel_pack, travel_pack.getPackId()) == true) modified_travel_pack = true;
        else cerr << "Failled to modify travel pack: some parameters were invalid!\n";
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

  while(1){ //only ends when 0 is typed
    print_first_lines("Travel Packs Menu");
    cout << "1 - View Travel Packs\n";
    cout << "2 - Add New Travel Pack\n";
    cout << "3 - Change Travel Pack\n";
    cout << "0 - Back\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 3){
      cerr << "Invalid intput!\n\n";
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
        if(!search_travel_pack(id, search_pack)) cout << "Travel Pack with ID: " << id << " not found!\n";
        else {
          change_travel_pack_menu(search_pack);
          if(agency.changeTravelPack(search_pack, id) == true) modified_travel_pack = true;
          else cout << "Failled to modify travel pack!\n";
        }
        break;

      default:
        break;
    }
  }
}

//End Travel Packs

void start_menu(){
  int answer;

  while(1){ //only ends when 0 is typed
    print_first_lines("Main Menu");
    cout << "1 - Agency\n";
    cout << "2 - Clients\n";
    cout << "3 - Travel Packs\n";
    cout << "0 - Exit\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 3){
      cerr << "Invalid intput!\n\n";
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
    }
  }

}