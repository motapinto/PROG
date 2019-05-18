#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include "menu.h"
#include "agency.h"
#include "UtilityFunctions.h"

#define MAX_NIF 999999999
#define INT_MAX 2147483647

using namespace std;

extern Agency agency;
extern bool modified_agency, modified_client, modified_travel_pack;

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
  cout<< endl;
}

//Begin Agency

void print_address_struct(){
  cout<< "(Street Name) / (Door Number) / (Floor) / (Zip Code) / (City)\n";
}

void change_agency_name(){
  string str_aux;
  cout<< "Name: "; read_line(str_aux); if(str_aux.size() == 0) return; 
  agency.setName(str_aux);
  modified_agency = true;
}

void change_agency_nif(){
  int nif = -1;
  string str_aux;

  cout<< "NIF: "; read_line(str_aux); if(str_aux.size() == 0) return;
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    cerr << "Invalid intput!\n\n";
    cout<< "NIF: "; read_line(str_aux); if(str_aux.size() == 0) return;
  }

  agency.setNif(nif);
  modified_agency = true;
}

void change_agency_address(){
  string str_aux;
  cout<< "Address: "; read_line(str_aux); if(str_aux.size() == 0) return;

  while(1) {

    try {
      agency.setAddress(str_aux);
      modified_agency = true;
    }

    catch(string) {
      cout<< "Invalid input!\nAddress must be typed in the following way: \n";
      print_address_struct();
      cout<< "Address: "; read_line(str_aux); if(str_aux.size() == 0) return;
    }

    catch(std::logic_error) {
      cout<< "Invalid input!\nAddress must be typed in the following way: \n";
      print_address_struct();
      cout<< "Address: "; read_line(str_aux); if(str_aux.size() == 0) return;
    }
  }
}

void change_agency_url(){
  string str_aux;

  cout<< "URL: "; read_line(str_aux); if(str_aux.size() == 0) return;

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

  while(1){ //only endls when 0 is typed
    print_first_lines("Change Agency Menu");
    cout<< "1 - All\n";
    cout<< "2 - Name\n";
    cout<< "3 - NIF\n";
    cout<< "4 - Address\n";
    cout<< "5 - URL\n";
    cout<< "0 - Back\n";
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

  cout<< endl << "Number of packs sold: " << num_sold << endl;
  cout<< "Total amount of gains: " << gains << endl << endl;
  print_wait_menu();
}

void agency_menu(){
  int answer = 0;

  while(1){ //only endls when 0 is typed
    print_first_lines("Agency Menu");
    cout<< "1 - View\n";
    cout<< "2 - Change\n";
    cout<< "3 - Calculate Gains\n";
    cout<< "0 - Back\n";
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
        cout << agency << endl;
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
  vector<Client> vec;
  string name;

  cout<< "Name: "; read_line(name);

  vec = agency.searchClientName(name);
  
  if(vec.size() == 1) client = vec.at(0);
  else if(vec.size() > 1) return 1;
  else return -1;

  return 0;
}

int search_client_nif(Client &client){
  int nif = 0;
  string str_aux;

  cout<< "NIF: ";
  read_line(str_aux);
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    cerr << "Invalid intput!\n\n";
    cout<< "NIF: ";
    read_line(str_aux); 
  }



  if(!agency.searchClientNif(nif, client)) return -1;

  return 0;
}

void print_client_packs(Client &client){
  vector<unsigned int>tour_packs_ids = client.getTourPacksBought();
  TravelPack pack;

  if(tour_packs_ids.size() == 0) cout<< "This client does not have any purchased packs\n";
  else{
    for(size_t i = 0; i < tour_packs_ids.size(); i++){
      if(agency.searchTravelPackId(tour_packs_ids.at(i), pack) == false) cout<< "Travel Pack with ID: " << tour_packs_ids.at(i) << " could not be found\n";
      else cout << pack << endl;
    }
  }
}

void print_client_selected(Client &client){
    int answer = 0;

  while(1){ //only endls when 0 is typed
    print_first_lines("Selected Client Menu");
    cout<< "1 - View Client Details\n";
    cout<< "2 - View Packs Bought\n";
    cout<< "0 - Back\n";
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
        cout << client << endl;
        print_wait_menu();
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
  if(client_vec.size() > 1) cout<< "More than one client found!\nPlease select the client wanted by another parameter\n";
  else print_client_selected(client_vec.at(0));
}

void print_single_client(){
  int answer = 0;
  Client client;

  while(1){ //only endls when 0 is typed
    print_first_lines("Single Client View Menu");
    cout<< "1 - Search by NIF\n";
    cout<< "2 - Search by Name\n";
    cout<< "0 - Back\n";
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
            cout<< "Could not find client!\n";
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
            cout<< "More than one client found with given name!\n";
            break;

          case -1:
            cout<< "Could not find client with specified name!\n";
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
    cout << vec.at(i) << endl;
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

  if(tour_packs_ids.size() == 0) cout<< "No packs were purchased by any client\n";
  else{
    for(size_t i = 0; i < tour_packs_ids.size(); i++, pack_count++){
      if(pack_count == 5) print_wait_menu();

      if(!agency.searchTravelPackId(tour_packs_ids.at(i), pack)) cout<< "Travel Pack with ID: " << tour_packs_ids.at(i) << " could not be found\n";
      else cout << pack << endl;
      cout<< endl;             
    }
  }

  print_wait_menu();
}

void print_clients_menu(){
  int answer = 0;

  while(1){ //only endls when 0 is typed
    print_first_lines("View Clients Menu");
    cout<< "1 - All Clients\n";
    cout<< "2 - Single Client\n";
    cout<< "0 - Back\n";
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

int change_client_name(Client &client){
  string str_aux;
  cout<< "Name: "; 
  read_line(str_aux); if(str_aux.size() == 0) return 1; 

  client.setName(str_aux);
  return 0;
}

int change_client_address(Client &client){
  string str_aux;
  cout<< "Address: "; read_line(str_aux); if(str_aux.size() == 0) return 1;

  while(1){

    try {
      client.setAddress(str_aux);
      break;
    }

    catch(string) {
      cout<< "Invalid input!\nAddress must be typed in the following way: \n";
      print_address_struct();
      cout<< "Address: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
    }

    catch(std::logic_error) {
      cout<< "Invalid input!\nAddress must be typed in the following way: \n";
      print_address_struct();
      cout<< "Address: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
    }
  }

  return 0;
}

int change_client_packs_bought(Client &client){
  string str_aux;

  cout<< "Tour packs bought: "; read_line(str_aux); if(str_aux.size() == 0) return 1;

  while(1) {
      try {
        client.setTourPacks(str_aux, ';');
        break;
      }

      catch(string) {
        cout<< "Invalid intput!\nPlease type tour packs bought in the following order:\n";
        cout<< "(Tour Pack Id 1) ; (Tour Pack Id 2); ... ; (Tour Pack Id n) or - for no packs\n";
        cout<< "Tour packs bought: ";
        read_line(str_aux); if(str_aux.size() == 0) return 1;
      }

      catch(std::logic_error) {
        cout<< "Invalid intput!\nPlease type tour packs bought in the following order:\n";
        cout<< "(Tour Pack Id 1) ; (Tour Pack Id 2); ... ; (Tour Pack Id n) or - for no packs\n";
        cout<< "Tour packs bought: ";
        read_line(str_aux); if(str_aux.size() == 0) return 1;
    }

  }
  return 0;
}

int change_client_nif(Client &client){
  int nif = -1;
  string str_aux;
  Client search_aux;

  cout<< "NIF: "; read_line(str_aux); if(str_aux.size() == 0) return 1;

  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    cerr << "Invalid intput!\n\n";
    cout<< "NIF: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  }

  client.setNif(nif);
  return 0;
}

int change_client_family_num(Client &client){
  int family_num = -1;
  string str_aux;

  cout<< "Family Number: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  while(string_to_int(str_aux, family_num) == false || family_num <= 0){
    cerr << "Invalid intput!\n\n";
    cout<< "Family Number: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  }

  client.setFamilyNum(family_num);
  return 0;
}

void add_client(){
  Client new_client;
  if(change_client_name(new_client)) return;
  if(change_client_nif(new_client)) return;
  if(change_client_address(new_client)) return;
  if(change_client_packs_bought(new_client)) return;
  if(change_client_family_num(new_client)) return;


  if(!agency.addClient(new_client)){
    cerr << "Failled to add client: some parameters were wrong\n";
    print_wait_menu();
  }

  modified_client = true;
  print_wait_menu();
}

void change_client_menu(Client &client){
  int answer = 0;
  int old_nif = client.getNif();

  while(1){ //only endls when 0 is typed
    print_first_lines("Change Client Selected Menu");
    cout<< "1 - All\n";
    cout<< "2 - Name\n";
    cout<< "3 - NIF\n";
    cout<< "4 - Address\n";
    cout<< "5 - Tour Packs Bought\n";
    cout<< "6 - Family Number\n";
    cout<< "0 - Back\n";
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
        if(change_client_name(client)) break;
        if(change_client_nif(client)) break;
        if(change_client_address(client)) break;
        if(change_client_packs_bought(client)) break;
        if(change_client_family_num(client)) break;
        if(agency.changeClient(client, old_nif))
          modified_client = true;
        else
          cerr << "Failled to modify client: some parameters were invalid!\n";
        break;

      case 2:
        if(change_client_name(client)) break;
        if(agency.changeClient(client, old_nif))
          modified_client = true;
        else
          cerr << "Failled to modify client: name is invalid!\n";
        break;

      case 3:
        if(change_client_nif(client)) break;
        if(agency.changeClient(client, old_nif))
          modified_client = true;
        else
          cerr << "Failled to modify client: NIF is invalid!\n";
        break;

      case 4:
        if(change_client_address(client)) break;
        if(agency.changeClient(client, old_nif))
          modified_client = true;
        else
          cerr << "Failled to modify client: address is invalid!\n";
        break;

      case 5:
        if(change_client_packs_bought(client)) break;
        if(agency.changeClient(client, old_nif))
          modified_client = true;
        else
          cerr << "Failled to modify client: packs are invalid!\n";
        break;

      case 6:
        if(change_client_family_num(client)) break;
        if(agency.changeClient(client, old_nif))
          modified_client = true;
        else
          cerr << "Failled to modify client: family number invalid!\n";
        break;

      default:
        break;
      
    }
  }
}

void change_clients_menu(){
  int answer = 0;
  Client client;

  while(1){ //only endls when 0 is typed
    print_first_lines("Change Clients Menu");
    cout<< "1 - Search by NIF\n";
    cout<< "2 - Search by Name\n";
    cout<< "0 - Back\n";
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
            cout<< "Could not find with given NIF client!\n";
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
            cout<< "More than one client found with given name!\n";
            break;

          case -1:
            cout<< "Could not find client with specified name!\n";
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

  cout<< "Travel Pack ID: ";
  read_line(str_aux);
  while(string_to_int(str_aux, id) == false || id < 0){
    cerr << "Invalid intput!\n\n";
    cout<< "Travel Pack ID: ";
    read_line(str_aux);
  }

  if(!agency.searchTravelPackId(id, pack)) cout<< "Travel Pack with ID: " << id << " not found!\n";
  else {
    packs_bought = client.getTourPacksBought();
    if(!pack.getAvailability()) {
      cout<< "This pack is not available for purchase!\n";
      return false;
    }
    
    if( (pack.getPeopleLimit() - (pack.getNumberSold() + client.getFamilyNum())) <= 0 ) {
      cout<< "This pack has no more seats available for purchase!\n";
      return false;
    }

    if(!agency.purchasePack(client.getNif(), pack.getPackId())){
      cout << "Failled to purchase pack!\n";
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

  cout<< "NIF: ";
  read_line(str_aux); if(str_aux.size() == 0) return;
  while(!string_to_int(str_aux, nif) || nif < 0 || nif > MAX_NIF){
    cerr << "Invalid intput!\n\n";
    cout<< "NIF: ";
    read_line(str_aux); if(str_aux.size() == 0) return;
  }

  

  if(agency.searchClientNif((unsigned int)nif, client) == true){
    if(purchase_pack(client) == true){
      agency.changeClient(client, nif);
      modified_client = true;
    } 
    print_wait_menu();
  }
  else cout<< "Client with NIF: " << nif << " not found!\n";
}

void purchase_client_name(){
  vector<Client> vec;
  string name;

  cout<< "Name: "; read_line(name); if(name.size() == 0) return;

  vec = agency.searchClientName(name);
  
  if(vec.size() > 1) cout<< "More than one client found with name: " << name << "\nPlease select another method of choosing a client\n";
  else if(vec.size() == 0) cout<< "Client with name:" << name << " not found!\n";
  else if(purchase_pack(vec.at(0)) == true){
    agency.changeClient(vec.at(0), vec.at(0).getNif());
    modified_client = true;
  } 
  
  print_wait_menu();
}

void purchase_client_menu(){
  int answer = 0;

  while(1){ //only endls when 0 is typed
    print_first_lines("Purchase Travel Pack Menu");
    cout<< "1 - Search Client by NIF\n";
    cout<< "2 - Search Client by Name\n";
    cout<< "0 - Back\n";
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

  while(1){ //only endls when 0 is typed
    print_first_lines("Clients Menu");
    cout<< "1 - View Clients\n";
    cout<< "2 - Add New Client\n";
    cout<< "3 - Change Clients\n";
    cout<< "4 - Purchase a Pack for a Client\n";   
    cout<< "5 - View All Travel Packs Purchased\n";
    cout<< "0 - Back\n";
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

int search_travel_pack(int &id, TravelPack &pack){
  string str_aux;

  cout<< "Travel Pack ID: ";
  read_line(str_aux); if(str_aux.size() == 0) return 2; 
  while(string_to_int(str_aux, id) == false || id < 0){
    cerr << "Invalid intput!\n\n";
    cout<< "Travel Pack ID: ";
    read_line(str_aux); if(str_aux.size() == 0) return 2; 
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
    cout << vec.at(i) << endl;
  }
  print_wait_menu();
}

void print_all_travel_pack_destination(){
  vector<TravelPack> vec;
  string destination;

  cout<< "Destination: "; read_line(destination); if(destination.size() == 0) return;
  cout<< endl;

  vec = agency.searchTravelPackDestination(destination);

  if(vec.size() == 0) cout<< "Travel Packs with destination:" << destination << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      cout << vec.at(i) << endl;
}

void print_all_travel_pack_dates(){
  vector<TravelPack> vec;
  Date init_date, final_date;
  string str_aux;

  do {
    cout<< "Initial Date: "; read_line(str_aux); if(str_aux.size() == 0) return; 

    try {
      init_date.setDate(str_aux);
      break;
    }
    catch(string) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Initial Date: ";  read_line(str_aux); if(str_aux.size() == 0) return;
    }
    catch(logic_error) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Initial Date: ";  read_line(str_aux); if(str_aux.size() == 0) return;
    }
  }  while(1);

  init_date.setDate(str_aux);

  do {
    cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return; 

    try {
      final_date.setDate(str_aux);
      break;
    }
    catch(string) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return;
    }
    catch(logic_error) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return;
    }
  }  while(1);

  final_date.setDate(str_aux);

  cout<< endl;

  vec = agency.searchTravelPackDates(init_date, final_date);

  if(vec.size() == 0) cout<< "Travel Packs with dates raging from " << init_date << " to " << final_date << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      cout << vec.at(i) << endl;

}

void print_all_travel_pack_destination_dates(){
  vector<TravelPack> vec;
  Date init_date, final_date;
  string str_aux;
  string destination;
  bool found = false;

  cout<< "Destination: "; read_line(destination); if(destination.size() == 0) return; 

  do {
    cout<< "Initial Date: "; read_line(str_aux); if(str_aux.size() == 0) return; 

    try {
      init_date.setDate(str_aux);
      break;
    }
    catch(string) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Initial Date: ";  read_line(str_aux); if(str_aux.size() == 0) return;
    }
    catch(logic_error) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Initial Date: ";  read_line(str_aux); if(str_aux.size() == 0) return;
    }
  }  while(1);

  do {
    cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return; 

    try {
      final_date.setDate(str_aux);
      break;
    }
    catch(string) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return;
    }
    catch(logic_error) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return;
    }
  }  while(1);


  cout<< endl;

  vec = agency.searchTravelPackDates(init_date, final_date);

  if(vec.size() == 0) cout<< "Travel Packs with dates raging from " << init_date << " to " << final_date << " not found!\n";
  else
    for(size_t i = 0; i < vec.size(); i++)
      if(vec.at(i).getDestination() == destination){
        cout << vec.at(i) << endl;
        found = true;
      }

  else if(found == false) cout<< "Travel Packs with destination:" << destination << " not found!\n";
}

void print_travel_pack_menu(){
  int answer = 0;
  TravelPack search_pack;
  int id = 0;

  while(1){ //only endls when 0 is typed
    print_first_lines("View Travel Packs Menu");
    cout<< "1 - All\n";
    cout<< "2 - All to Destination\n";
    cout<< "3 - All from date to date\n";
    cout<< "4 - All to Destination and from date to date\n";
    cout<< "5 - Single Travel Pack\n";
    cout<< "0 - Back\n";
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
        switch (search_travel_pack(id, search_pack)){
          case 0:
            cerr<< "Travel Pack with ID: " << id << " not found!\n";
            break;
          
          case 1:
            cout << search_pack << endl;
            print_wait_menu();
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

int change_travel_pack_dates(TravelPack &travel_pack){
  string str_aux;
  bool not_valid;
  Date init_date, final_date;

  do{
    do {
      cout<< "Initial Date: "; read_line(str_aux); if(str_aux.size() == 0) return 1; 

      try {
        init_date.setDate(str_aux);
      }
      catch(string) {
        cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
        cout<< "Initial Date: ";  read_line(str_aux); if(str_aux.size() == 0) return 1;
      }
      catch(logic_error) {
        cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
        cout<< "Initial Date: ";  read_line(str_aux); if(str_aux.size() == 0) return 1;
      }
    }  while(1);

    do {
      cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return 1; 

      try {
        final_date.setDate(str_aux);
      }
      catch(string) {
        cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
        cout<< "Final Date: ";  read_line(str_aux); if(str_aux.size() == 0) return 1;
      }
      catch(logic_error) {
        cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
        cout<< "Final Date: ";  read_line(str_aux); if(str_aux.size() == 0) return 1;
      }
    }  while(1);
    if((not_valid = init_date > final_date))
      cerr << "Invalid Dates: Final Date must after or the same as Initial Date\n";

  }while(not_valid);

  if(travel_pack.getInitDate() > init_date){
    travel_pack.setInitDate(init_date.getDate(), true);
    travel_pack.setFinalDate(final_date.getDate(), true);
  }
  else{
    travel_pack.setFinalDate(final_date.getDate(), true);
    travel_pack.setInitDate(init_date.getDate(), true);
  }
  return 0;
}

int change_travel_pack_init_date(TravelPack &travel_pack){
  string str_aux;
  Date date_aux;

  do {
    cout<< "Initial Date: "; read_line(str_aux); if(str_aux.size() == 0) return 1; 

    try {
      travel_pack.setInitDate(str_aux, true);
      break;
    }
    catch(string) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Initial Date: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
    }
    catch(logic_error) {
        cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
        cout<< "Initial Date: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
      }
  }  while(1);
  return 0;
}

int change_travel_pack_final_date(TravelPack &travel_pack){
  string str_aux;
  Date date_aux;

  do {
    cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return 1; 

    try {
      travel_pack.setFinalDate(str_aux, true);
      break;
    }
    catch(string) {
      cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
      cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
    }
    catch(logic_error) {
        cout<< "Invalid intput!\nDate must follow format: (Year)/(Month)/(Day)\n";
        cout<< "Final Date: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
      }
  }  while(1);
  return 0;
}

int change_travel_pack_destination(TravelPack &travel_pack){
  string str_aux;
  cout<< "Destination: "; read_line(str_aux); if(str_aux.size() == 0) return 1;

  travel_pack.setDestination(str_aux);
  return 0;
}

int change_travel_pack_cities(TravelPack &travel_pack){
  string str_aux;
  vector<string> cities;

  cout<< "Cities (Separated by , or - for none): "; read_line(str_aux); if(str_aux.size() == 0) return 1;

  if(str_aux.compare("-") == 0) cities.resize(0);
  else decompose(str_aux, cities, ',');

  travel_pack.setCities(cities, true);
  return 0;
}

int change_travel_pack_price(TravelPack &travel_pack){
  int price = -1;
  string str_aux;
  cout<< "Price: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  while(string_to_int(str_aux, price) == false || price < 0){
    cerr << "Invalid intput!\n\n";
    cout<< "Price: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  }

  travel_pack.setPrice(price);
  return 0;
}

int change_travel_pack_people_limit(TravelPack &travel_pack){
  int people_limit = -1;
  string str_aux;
  cout<< "Number of seats available: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  while(string_to_int(str_aux, people_limit) == false || people_limit < 0){
    cerr << "Invalid intput!\n\n";
    cout<< "Number of seats available: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  }

  travel_pack.setPeopleLimit(people_limit, true);
  return 0;
}

int change_travel_pack_num_sold(TravelPack &travel_pack){
  int num_sold = -1;
  string str_aux;

  cout<< "Number of seats sold: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  while(!string_to_int(str_aux, num_sold) || num_sold < 0){
    cerr << "Invalid intput!\n\n";
    cout<< "Number of seats sold: "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  }

  travel_pack.setNumberSold(num_sold, true);
  return 0;
}

int change_travel_pack_available(TravelPack &travel_pack){
  string str_aux;
  cout<< "Available(Yes/No): "; read_line(str_aux); if(str_aux.size() == 0) return 1; 
  while(str_aux.compare("Yes") != 0 && str_aux.compare("No") != 0){
    cout<< "Invalid Input\n";
    cout<< "Available(Yes/No): "; read_line(str_aux); if(str_aux.size() == 0) return 1;
  }

  if(str_aux.compare("Yes") == 0) travel_pack.setAvailability(true);
  else if(str_aux.compare("No") == 0) travel_pack.setAvailability(false);
  return 0;
}

void add_travel_pack(){
  TravelPack new_pack;
  TravelPack search_pack;
  int id = -1;
  string str_aux;

  cout<< "Travel Pack ID: ";
  read_line(str_aux); if(str_aux.size() == 0) return;
  while(string_to_int(str_aux, id) == false || id < 0){
    cerr << "Invalid intput!\n\n";
    cout<< "Travel Pack ID: ";
    read_line(str_aux); if(str_aux.size() == 0) return;
  }
  new_pack.setPackId(id);

  if(agency.searchTravelPackId(id, search_pack)){
    cerr << "Travel Pack with ID: " << id << " already exists!\n";
    print_wait_menu();
    return;
  }

  if(change_travel_pack_destination(new_pack)) return;
  if(change_travel_pack_cities(new_pack)) return;
  if(change_travel_pack_dates(new_pack)) return;
  if(change_travel_pack_price(new_pack)) return;
  if(change_travel_pack_people_limit(new_pack)) return;
  if(change_travel_pack_num_sold(new_pack)) return;
  if(new_pack.getNumberSold() > new_pack.getPeopleLimit()){
    cerr << "Invalid seats numbers: number of total seats available must higher or equal to number of seats sold!\n";
    print_wait_menu();
    return;
  }
  change_travel_pack_available(new_pack);

  if(agency.addTravelPack(new_pack) == false){
    cerr << "Failled to add travel pack\n";
  }
  else modified_travel_pack = true;

  print_wait_menu();
}

void change_travel_pack_menu(TravelPack &travel_pack){
  int answer = 0;

  while(1){ //only endls when 0 is typed
    print_first_lines("Change Travel Pack Menu");
    cout<< "1 - All\n";
    cout<< "2 - Destination\n";
    cout<< "3 - Cities\n";
    cout<< "4 - Initial Date\n";
    cout<< "5 - Final Date\n";
    cout<< "6 - Price\n";
    cout<< "7 - Seats Available\n";
    cout<< "8 - Seats Sold\n";
    cout<< "9 - Availability\n";
    cout<< "0 - Back\n";
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
        if(change_travel_pack_destination(travel_pack)) break;
        if(change_travel_pack_cities(travel_pack)) break;
        if(change_travel_pack_dates(travel_pack)) break;
        if(change_travel_pack_price(travel_pack)) break;
        if(change_travel_pack_people_limit(travel_pack)) break;
        if(change_travel_pack_num_sold(travel_pack)) break;
        break;

      case 2:
        if(change_travel_pack_destination(travel_pack)) break;
        break;

      case 3:
        if(change_travel_pack_cities(travel_pack)) break;
        break;

      case 4:
        if(change_travel_pack_init_date(travel_pack)) break;
        break;

      case 5:
        if(change_travel_pack_final_date(travel_pack)) break;
        break;

      case 6:
        if(change_travel_pack_price(travel_pack)) break;
        break;

      case 7:
        if(change_travel_pack_people_limit(travel_pack)) break;
        break;

      case 8:
        if(change_travel_pack_num_sold(travel_pack)) break;
        break;

      case 9:
        if(change_travel_pack_available(travel_pack)) break;
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

  while(1){ //only endls when 0 is typed
    print_first_lines("Travel Packs Menu");
    cout<< "1 - View Travel Packs\n";
    cout<< "2 - Add New Travel Pack\n";
    cout<< "3 - Change Travel Pack\n";
    cout<< "0 - Back\n";
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
        switch (search_travel_pack(id, search_pack)){
          case 0:
            cerr<< "Travel Pack with ID: " << id << " not found!\n";
            break;
          
          case 1:
            change_travel_pack_menu(search_pack);
            if(agency.changeTravelPack(search_pack, id)) modified_travel_pack = true;
            else cout<< "Failled to modify travel pack!\n";
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

//End Travel Packs
//Begin Statistics

void print_most_visited_places(){
  multimap<unsigned int, string> mp = agency.mostVisitedPlaces();
  string str_aux;
  int number_places = -1;

  cout<< "Number of Places: "; read_line(str_aux); if(str_aux.size() == 0) return;
  while(!string_to_int(str_aux, number_places) || number_places <= 0){
    cerr << "Invalid intput!\n\n";
    cout<< "Number of Places: "; read_line(str_aux); if(str_aux.size() == 0) return;
  }

  auto it = mp.rbegin();
  for(int i = 0; i < number_places && it != mp.rend(); i++, it++)
    cout<< "Most visited place number " << i+1 << ": " << (*it).second << " visited a total of " << (*it).first << " times\n";

  cout<< endl;

  print_wait_menu();
}

void print_most_visited_places_clients(){
  multimap<unsigned int, string> mp = agency.mostVisitedPlaces();
  string str_aux;
  int number_places = -1;
  vector <TravelPack> packs_with_city;
  vector <Client> clients = agency.getClientList();
  vector <unsigned int> packs_bought;
  

  cout << "Number of Places: "; read_line(str_aux); if(str_aux.size() == 0) return;
  while(!string_to_int(str_aux, number_places) || number_places <= 0){
    cerr << "Invalid intput!\n\n";
    cout << "Number of Places: "; read_line(str_aux); if(str_aux.size() == 0) return;
  }

  for(size_t client_count = 0; client_count < clients.size(); client_count++){
    bool found = false;
    cout << clients.at(client_count) << endl;
    cout << "Recommended pack: \n";
    packs_bought = clients.at(client_count).getTourPacksBought();

    auto it = mp.rbegin();
    for(int i = 0; i < number_places && it != mp.rend() && !found; i++, it++){
      packs_with_city = agency.searchTravelPackCity((*it).second);

        for(size_t k = 0; k < packs_bought.size() && !found; k++){
          //find pack from all packs that have the city with same id as the pack bought by the client
          if( find(packs_with_city.begin(), packs_with_city.end(), packs_bought.at(k)) == packs_with_city.end() ){
          //could not find == client has not visited the city!
            for(size_t j = 0; j < packs_with_city.size() && !found; j++)
              if(packs_with_city.at(j).getNumberSold() < packs_with_city.at(j).getPeopleLimit() && packs_with_city.at(j).getAvailability()){
                found = true;
                cout << packs_with_city.at(j) << endl;
                print_wait_menu();
              }
            
          }
        }
      
    }

    if(!found){
      cout << "None\n";
      print_wait_menu();
    } 
  }

  cout << endl;
}

void statistics_menu(){
  TravelPack search_pack;
  int answer = 0;

  while(1){ //only endls when 0 is typed
    print_first_lines("Statistics Menu");
    cout<< "1 - Most Visited Places\n";
    cout<< "2 - Clients Who Visited a Most Visited Place\n";
    cout<< "0 - Back\n";
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

  while(1){ //only endls when 0 is typed
    print_first_lines("Main Menu");
    cout<< "1 - Agency\n";
    cout<< "2 - Clients\n";
    cout<< "3 - Travel Packs\n";
    cout<< "4 - Statistics\n";
    cout<< "0 - Exit\n";
    print_last_line();

    answer = scan_single_int();
    while( answer < 0 || answer > 4){
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

      case 4:
        statistics_menu();
        break;
    }
  }
}