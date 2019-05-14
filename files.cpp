#include "files.h"

#include "UtilityFunctions.h"
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

//returns true when line != :::::::::
bool last_line(string line){
  const static string s = "::::::::::";
  return line != s;
}

int read_agency(Agency &agency, string agency_file_name, string &clients_file_name, string &packs_file_name){
  ifstream agency_file;

  agency_file.open(agency_file_name);
  if(!agency_file.is_open())
      return -1;

  try{
    agency_file >> agency;
  }
  catch (string){
    return 1;
  }

  if(!agency_file.eof()){
    getline(agency_file, clients_file_name);
    if(clients_file_name.size() > 0){
      if(clients_file_name.at(clients_file_name.size() - 1) == '\r') clients_file_name.pop_back();
      if(clients_file_name.at(0) == '\r') clients_file_name.erase(0, 1);
    } 
    Trim(clients_file_name);
    if(clients_file_name.size() == 0) return 2;
  }

  if(!agency_file.eof()){
    getline(agency_file, packs_file_name);
    if(packs_file_name.size() > 0){
      if(packs_file_name.at(packs_file_name.size() - 1) == '\r') packs_file_name.pop_back();
      if(packs_file_name.at(0) == '\r') packs_file_name.erase(0, 1);
    } 
    Trim(packs_file_name);
    if(packs_file_name.size() == 0) return 3;
  }

  agency_file.close();


  return 0;
}

int read_clients(Agency &agency, string clients_file_name){
  ifstream client_file;

  string str_aux = "::::::::::";
  Client new_client;
  vector <Client> client_list;

  //read client file
  client_file.open(clients_file_name);

  if(!client_file.is_open())
    return -1;

  if(client_file.peek() == ifstream::traits_type::eof()){
    return 0;
  }

  do{
    //Clear unwanted information
    if(str_aux.size() > 0){
      if(str_aux.at(str_aux.size() - 1) == '\r') str_aux.pop_back();
      if(str_aux.at(0) == '\r') str_aux.erase(0, 1);
    } 
    Trim(str_aux);
    if(last_line(str_aux))
      break;
    
    try{
      client_file >> new_client;
    }
    catch(string){
      client_file.close();
      return client_list.size();
    }
    client_list.push_back(new_client);

  } while(getline(client_file, str_aux));

  agency.setClientList(client_list);

  client_file.close();

  return 0;
}

int read_packs(Agency &agency, string packs_file_name){
  ifstream packs_file;

  string str_aux = "::::::::::";
  TravelPack new_pack;
  vector <TravelPack> packs;

  //read client file
  packs_file.open(packs_file_name);

  if(!packs_file.is_open())
    return -1;

  if(packs_file.peek() == ifstream::traits_type::eof()){
    return 0;
  }

  do{   
    //Clear unwanted information
    if(str_aux.size() > 0){
      if(str_aux.at(str_aux.size() - 1) == '\r') str_aux.pop_back();
      if(str_aux.at(0) == '\r') str_aux.erase(0, 1);
    } 
    Trim(str_aux);

    if(last_line(str_aux))
      break;
    
    try{
      packs_file >> new_pack;
    }
    catch(string){
      packs_file.close();
      return packs.size();
    }
    packs.push_back(new_pack);

  } while(getline(packs_file, str_aux));

  agency.setTourPack(packs);

  packs_file.close();

  return 0;
}

int read_files(Agency &agency, string agency_file_name, string &clients_file_name, string &packs_file_name){ //reads agency file and fills agency class
  
  ifstream agency_file, client_file, packs_file; //input file from where to read
  int line;
  
  switch (line = read_agency(agency, agency_file_name, clients_file_name, packs_file_name))
  {
    case -1:
      cerr << "Error: failled to open " << agency_file_name << "!\n";
      return -1;
      break;
    case 0:
      break;
    default:
      cerr << "Error: invalid struct of data in "<< agency_file_name << " on line: " << line << "!\n";      
      return 1;
  }

  switch (line = read_packs(agency, packs_file_name))
  {
    case -1:
      cerr << "Error: failled to open " << packs_file_name << "!\n";
      return -3;
      break;
    case 0:
      break;
    default:
      cerr << "Error: invalid struct of data in "<< packs_file_name << " on line: " << line << "!\n";      
      return 3;
  }

  switch (line = read_clients(agency, clients_file_name))
  {
    case -1:
      cerr << "Error: failled to open " << clients_file_name << "!\n";
      return -2;
      break;
    case 0:
      break;
    default:
      cerr << "Error: invalid struct of data in "<< clients_file_name << " on line: " << line << "!\n";      
      return 2;
  }

  return 0;
}

void write_agency(Agency &agency, const string agency_file_name, const string clients_file_name, const string packs_file_name){
  char temp_file_name[BUFFER_SIZE] = "temp.txt";
  const char *agency_file_name_array = agency_file_name.c_str();

  ofstream temp_file;

  temp_file.open(temp_file_name);
  
  temp_file << agency.getName() << "\n";
  temp_file << agency.getNif() << "\n";
  temp_file << agency.getUrl() << "\n";
  temp_file << agency.getAddress().getAddress() << "\n";
  temp_file << clients_file_name << "\n";
  temp_file << packs_file_name << "\n";

  temp_file.close();

  remove(agency_file_name_array);
  rename(temp_file_name, agency_file_name_array);

  return;
}

void write_clients(Agency &agency, const string clients_file_name){
  char temp_file_name[BUFFER_SIZE] = "temp.txt";
  const char *clients_file_name_array = clients_file_name.c_str();

  vector<Client> clients = agency.getClientList();
  vector<unsigned int> packs_bought;

  ofstream temp_file;

  temp_file.open(temp_file_name);

  if(clients.size() == 0){
    temp_file.close();
    return;
  }
  
  temp_file << clients.at(0).getName() << "\n";
  temp_file << clients.at(0).getNif() << "\n";
  temp_file << clients.at(0).getFamilyNum() << "\n";
  temp_file << clients.at(0).getAddress().getAddress() << "\n";
  packs_bought = clients.at(0).getTourPacksBought();
  if(packs_bought.size() != 0) {
    temp_file << packs_bought.at(0);
    for(size_t i = 1; i < packs_bought.size(); i++)
      temp_file << " ; " << packs_bought.at(i);
    
    temp_file << "\n";
  }
  temp_file << clients.at(0).getMoneySpent() << "\n";

  for(size_t i = 1; i < clients.size(); i++){
    temp_file << "::::::::::\n";
    temp_file << clients.at(i).getName() << "\n";
    temp_file << clients.at(i).getNif() << "\n";
    temp_file << clients.at(i).getFamilyNum() << "\n";
    temp_file << clients.at(i).getAddress().getAddress() << "\n";
    packs_bought = clients.at(i).getTourPacksBought();
    if(packs_bought.size() != 0) {
      temp_file << packs_bought.at(0);
      for(size_t j = 1; j < packs_bought.size(); j++)
        temp_file << " ; " << packs_bought.at(j);
      
      temp_file << "\n";
    }
    temp_file << clients.at(i).getMoneySpent() << "\n";
  }

  temp_file.close();

  remove(clients_file_name_array);
  rename(temp_file_name, clients_file_name_array);

  return;
}

void write_packs(Agency &agency, const string packs_file_name){
  char temp_file_name[BUFFER_SIZE] = "temp.txt";
  const char *packs_file_name_array = packs_file_name.c_str();

  vector<TravelPack> packs = agency.getTourPacks();
  vector<string> cities;

  ofstream temp_file;

  temp_file.open(temp_file_name);

  if(packs.size() == 0){
    temp_file.close();
    return;
  }

  temp_file << packs.at(packs.size() - 1).getPackId() << "\n";
  
  if(packs.at(0).getAvailability() == true ) temp_file << packs.at(0).getPackId() << "\n";
  else temp_file << -packs.at(0).getPackId() << "\n";
  temp_file << packs.at(0).getDestination();
  cities = packs.at(0).getCities();
  if(cities.size() != 0){
    temp_file << " - ";
    if(cities.size() > 0){
      temp_file << cities.at(0);
      for(size_t i = 1; i < cities.size(); i++)
        temp_file << ", " << cities.at(i);
    }
  }
  temp_file << "\n";
  temp_file << packs.at(0).getInitDate() << "\n";
  temp_file << packs.at(0).getFinalDate() << "\n";
  temp_file << packs.at(0).getPrice() << "\n";
  temp_file << packs.at(0).getPeopleLimit() << "\n";
  temp_file << packs.at(0).getNumberSold() << "\n";

  for(size_t i = 1; i < packs.size(); i++){
    temp_file << "::::::::::\n";
    if(packs.at(i).getAvailability() == true ) temp_file << packs.at(i).getPackId() << "\n";
    else temp_file << -(int)packs.at(i).getPackId() << "\n";
    temp_file << packs.at(i).getDestination();
    cities = packs.at(i).getCities();
    if(cities.size() != 0){
      temp_file << " - ";
      if(cities.size() > 0){
        temp_file << cities.at(0);
        for(size_t j = 1; j < cities.size(); j++)
          temp_file << ", " << cities.at(j);
      }
    }
    temp_file << "\n";
    temp_file << packs.at(i).getInitDate() << "\n";
    temp_file << packs.at(i).getFinalDate() << "\n";
    temp_file << packs.at(i).getPrice() << "\n";
    temp_file << packs.at(i).getPeopleLimit() << "\n";
    temp_file << packs.at(i).getNumberSold() << "\n";
  }

  temp_file.close();

  remove(packs_file_name_array);
  rename(temp_file_name, packs_file_name_array);

  return;
}
