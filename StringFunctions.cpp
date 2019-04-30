#include "StringFunctions.h"

void TrimLeft(std::string &str){
    str.erase(0, str.find_first_not_of(' '));
}

void TrimRight(std::string &str) {
    str.erase(str.find_last_not_of(' ') + 1);
}

void Trim(std::string &str) {
    TrimLeft(str); 
    TrimRight(str); 
}

void decompose(std::string s, std::vector <std::string> &elements, char c){
  elements.resize(0);

  Trim(s);
  if(s.size() == 0) return;

	size_t pos = s.find(c);
	while(pos != std::string::npos){ //ate final da string
		std::string elem = s.substr(0, pos);
		Trim(elem);
		elements.push_back(elem);
		s.erase(0, pos+1);
		pos = s.find(c);
	}
	Trim(s);
	elements.push_back(s);
}

void decompose(std::string s, std::vector <std::string> &elements){
  elements.resize(0);

  Trim(s);
  if(s.size() == 0) return;

  size_t pos = s.find('/');
	while(pos != std::string::npos){ //ate final da string
		std::string elem = s.substr(0, pos);
		Trim(elem);
		elements.push_back(elem);
		s.erase(0, pos + 1);
		pos = s.find('/');
	}
	Trim(s);
	elements.push_back(s);
}

bool decompose(std::string s, std::vector <unsigned int> &elements, char c='/'){
  //used to verify if value was converted
  //all values are unsigned, if after converting value <= -1, convertion failled or value is not unsigned
  std::vector <std::string> string_elem;
  elements.resize(0);
  int value = -1; 

  decompose(s, string_elem, c);

  for(size_t i = 0; i < string_elem.size(); i++){
    if(string_to_int(string_elem.at(i), value) == false){  //convertion failled
      elements.resize(0);
      return false; 
    } 
    if(value <= -1){ //negative number
      elements.resize(0);
      return false; 
    }
    elements.push_back(value);
  }

  return true;
}

bool string_to_int(std::string s, int &ret){
  Trim(s);
  ret = 0;

  if(s.size() == 0) return false;

  if(s.at(0) == '-'){
    for(size_t i = 1; i < s.size(); i++){
      switch (s.at(i))
      {
        case '0':
          ret = ret*10;
          break;
      
        case '1':
          ret = ret*10 + 1;
          break;
      
        case '2':
          ret = ret*10 + 2;
          break;
      
        case '3':
          ret = ret*10 + 3;
          break;
      
        case '4':
          ret = ret*10 + 4;
          break;
      
        case '5':
          ret = ret*10 + 5;
          break;
      
        case '6':
          ret = ret*10 + 6;
          break;
      
        case '7':
          ret = ret*10 + 7;
          break;
      
        case '8':
          ret = ret*10 + 8;
          break;
      
        case '9':
          ret = ret*10 + 9;
          break;
      
        default:
          return false;
      }
    }
    ret = -ret;
    return true;
  }
  else{
    for(size_t i = 0; i < s.size(); i++){
      switch (s.at(i))
      {
        case '0':
          ret = ret*10;
          break;
      
        case '1':
          ret = ret*10 + 1;
          break;
      
        case '2':
          ret = ret*10 + 2;
          break;
      
        case '3':
          ret = ret*10 + 3;
          break;
      
        case '4':
          ret = ret*10 + 4;
          break;
      
        case '5':
          ret = ret*10 + 5;
          break;
      
        case '6':
          ret = ret*10 + 6;
          break;
      
        case '7':
          ret = ret*10 + 7;
          break;
      
        case '8':
          ret = ret*10 + 8;
          break;
      
        case '9':
          ret = ret*10 + 9;
          break;
      
        default:
          return false;
      }
    }
    return true;
  }


  return false;
}

//Generic function to read integers
void read_int(int &init_store) 
{ 
    std::string str;

    while(true) {
        getline(std::cin, str);

        try {
            init_store = stoi(str);
            break;

        }
        catch(const invalid_argument& ia) {
            std::cout << "Input value is not valid\n";
            std::cout << "Try again: ";
        }
    }
}

//Generic function to read unsigned integers
void read_uint(unsigned int &init_store) 
{ 
    std::cin >> init_store;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cin >> init_store;
    }
    std::cin.ignore();
}

//Generic function to read strings
void read_string(std::string &str) 
{ 
    while(!getline(std::cin, str, '\n')){
        std::cin.clear();
        std::cin.ignore();
    }
}