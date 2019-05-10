#include "files.h"

#include "StringFunctions.h"
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

  string str_aux; //string used to read the file
  size_t total_line_count = 1; //total line counter
  size_t line_count = 0; //line counter
  int value_check = -1; //used to check if value read is unsigned or if it can be converted

  agency_file.open(agency_file_name);
  if(!agency_file.is_open())
      return -1;

  while(getline(agency_file, str_aux)){
    total_line_count++;
    if(str_aux.size() > 0){
      if(str_aux.at(str_aux.size() - 1) == '\r') str_aux.pop_back();
      if(str_aux.at(0) == '\r') str_aux.erase(0, 1);
    } 
    Trim(str_aux);
    switch (line_count) {
      case 0:
        agency.setName(str_aux);
        break;

      case 1:
        if(string_to_int(str_aux, value_check) == false){
          agency_file.close();
          return total_line_count;
        } 
        if(value_check <= -1){
          agency_file.close();
          return total_line_count;
        } 
        else value_check = -1;
        agency.setNif(stoi(str_aux));
        break;

      case 2:
        agency.setUrl(str_aux);
        break;

      case 3:
        if(!agency.setAddress(str_aux)) return total_line_count;
        break;

      case 4:
        clients_file_name = str_aux;
        break;

      case 5:
        packs_file_name = str_aux;
        break;

      default:
        break;
    }
    line_count++;
  }

  agency_file.close();

  if(line_count != 6) return total_line_count;

  return 0;
}

int read_clients(Agency &agency, string clients_file_name){
  ifstream client_file;

  string str_aux;
  size_t total_line_count = 0;
  size_t line_count = 0;
  int value_check = -1;
  Client new_client;

  //auxiliar variables to fill client class
  bool end_of_file = false;

  //read client file
  client_file.open(clients_file_name);
  if(!client_file.is_open())
    return -1;


  while(getline(client_file, str_aux) && end_of_file == false){
    total_line_count++;
    if(str_aux.size() > 0){
      if(str_aux.at(str_aux.size() - 1) == '\r') str_aux.pop_back();
      if(str_aux.at(0) == '\r') str_aux.erase(0, 1);
    } 
    Trim(str_aux);
    switch (line_count) {
      case 0:
        new_client.setName(str_aux);
        
        break;

      case 1:
        if(string_to_int(str_aux, value_check) == false){
          client_file.close();
          return total_line_count;
        } 
        if(value_check <= -1){
          client_file.close();
          return total_line_count;
        } 
        new_client.setNif(value_check);
        value_check = -1;        
        break;

      case 2:
        if(string_to_int(str_aux, value_check) == false){
          client_file.close();           
          return total_line_count;         
        } 
        if(value_check <= -1){ //verify value
          client_file.close();
          return total_line_count;
        } 
        new_client.setFamilyNum(value_check);        
        value_check = -1;
        break;

      case 3:
        if(new_client.setAddress(str_aux) == false){
          client_file.close();
          return total_line_count;
        }      

        break;

      case 4:
        if( new_client.setTourPacks(str_aux, ';') == false) { //couldn't convert all values, vector might be empty
          if( !(end_of_file = last_line(str_aux)) ){ //separator was read
            line_count = -1;
          }
          else if(!client_file.eof()){ //end of file was not reached, error in string read
            client_file.close();
            return total_line_count;
          }
        } 
        if(agency.addClient(new_client) == false){
          client_file.close();
          return total_line_count;
        }
        
        break;

      case 5:
        if(string_to_int(str_aux, value_check) == false){
          client_file.close();           
          return total_line_count;         
        } 
        if(value_check <= -1){ //verify value
          client_file.close();
          return total_line_count;
        } 
        new_client.setMoneySpent(value_check);        
        value_check = -1;
        break;

      case 6:
        end_of_file = last_line(str_aux);
        line_count = -1; //reset line_count, it will increment to 0 for next iteration
        
        break;

      default:
        break;
    }
    line_count++;
  }

  if(str_aux.size() == 0 && client_file.eof() && total_line_count == 0){
    client_file.close();
    return 0;
  }

  if(end_of_file == true) //client separator not found
    if(client_file.eof() != true){ //not end of file, invalid file struct
      client_file.close();
      return total_line_count;
    }

  if(line_count == 4 && str_aux.size() == 0){
    new_client.setTourPacks(str_aux, ';'); // str_aux will be empty so packs bought will be none
    if(agency.addClient(new_client) == false){
      client_file.close();
      return total_line_count;
    }
    client_file.close();
    return 0;
  } 

  if(line_count == 5){
    client_file.close();
    return 0; //filled every client
  } 

  client_file.close();


  return total_line_count;
}

int read_packs(Agency &agency, string packs_file_name){
  ifstream packs_file;

  string str_aux;
  size_t total_line_count = 1;
  size_t line_count = 0;
  int value_check = -1;
  int last_pack_id = 0;

  //auxiliar variables to fill packs class
  TravelPack pack;
  vector<string>cities;
  bool end_of_file = false;

  //read packs file
  packs_file.open(packs_file_name);
  if(!packs_file.is_open())
    return -1;

  getline(packs_file, str_aux);
  if(str_aux.size() > 0){
    if(str_aux.at(str_aux.size() - 1) == '\r') str_aux.pop_back();
    if(str_aux.at(0) == '\r') str_aux.erase(0, 1);
  } 
  Trim(str_aux);

  if(str_aux.size() == 0 && packs_file.eof() && total_line_count == 1){
    packs_file.close();
    return 0;
  }


  if(string_to_int(str_aux, last_pack_id) == false) {
    packs_file.close();
    return total_line_count;
  }

  while(getline(packs_file, str_aux) && end_of_file == false){
    total_line_count++;
    if(str_aux.size() > 0){
      if(str_aux.at(str_aux.size() - 1) == '\r') str_aux.pop_back();
      if(str_aux.at(0) == '\r') str_aux.erase(0, 1);
    } 
    Trim(str_aux);
    switch (line_count) {
      case 0:
        if(string_to_int(str_aux, value_check) == false) {
          packs_file.close();
          return total_line_count;
        }
        if(value_check < 0){
          pack.setAvailability(false);
          pack.setPackId(-value_check);
        }
        else {
          pack.setAvailability(true);
          pack.setPackId(value_check);
        }
        value_check = -1;
        break;

      case 1:
        //separate destination from cities
        decompose(str_aux, cities, '-'); 
        if(cities.size() == 0 || cities.size() > 2) return total_line_count;
        pack.setDestination(cities.at(0));

        //separate all cities if they exist
        if(cities.size() == 2) decompose(cities.at(1), cities, ',');
        else cities.resize(0); //eliminate all elements of cities
        pack.setCities(cities);
        break;

      case 2:
        if(pack.setInitDate(str_aux) != 0){
          packs_file.close();
          return total_line_count;
        }
        break;

      case 3:
        if(pack.setFinalDate(str_aux) != 0){
          packs_file.close();
          return total_line_count;
        }
        break;

      case 4:
        if(string_to_int(str_aux, value_check) == false){
          packs_file.close();
          return 1;
        } 
        if(value_check <= -1){
          packs_file.close();
          return 1;
        }
        pack.setPrice(value_check);
        value_check = -1;
        break;
      
      case 5:
        if(string_to_int(str_aux, value_check) == false){
          packs_file.close();
          return total_line_count;
        } 
        if(value_check <= -1){
          packs_file.close();
          return total_line_count;
        }
        pack.setPeopleLimit(value_check);
        value_check = -1;
        break;
      
      case 6:
        if(string_to_int(str_aux, value_check) == false){
          packs_file.close();
          return total_line_count;
        } 
        if(value_check <= -1){
          packs_file.close();
          return total_line_count;
        }
        pack.setNumberSold(value_check);
        value_check = -1;

        if (agency.addTravelPack(pack) == false ) return total_line_count;
        cities.resize(0); //eliminate all elements for next iteration
        break;
    
      case 7: // packs separtor ::::::::::
        end_of_file = last_line(str_aux);
        line_count = -1; //reset line_count, it will increment to 0 for next iteration
        break;

      default:
        break;
    }
    line_count++;
  }

  if (last_pack_id < 0){
    if(pack.getPackId() != (unsigned int)(-last_pack_id)) return total_line_count;
  } 
  else if(pack.getPackId() != (unsigned int)last_pack_id) return total_line_count;

  if(end_of_file == true) //client separator not found
    if(packs_file.eof() != true){ //not end of file, invalid file struct
      packs_file.close();
      return total_line_count;
    }

  if(line_count == 7) return 0; //filled every pack

  return total_line_count;
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
