#include "UtilityFunctions.h"

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

bool string_to_int(std::string s, int &value){
  char *ptr;
  value = strtol(s.c_str(), &ptr, 10);

  //if no conversion is performed or there is a part of the string that contain char's
  if(*ptr != '\0' || errno == EINVAL) {
    return false;
  }

  return true;
}

void read_line(std::string &s){
  std::cin.clear();
  fflush(stdin);
  getline(std::cin, s);
  while(s.size() == 0)
    getline(std::cin, s);  
}

int scan_single_int(){
  int scan = 0;
  std::string str_aux;

  std::cout << "Please type in a number: ";
  read_line(str_aux);  
  while(string_to_int(str_aux, scan) == false || scan < 0 || scan > 9){
    std::cerr << "Invalid intput!\n\n";
    std::cout << "Please type in a number: ";
    read_line(str_aux);  
  }
  return scan;
}

//Generic function to test and catch exceptions
template <class T>
bool Try(void func(T &param), T &param){
  try{
    func(param);
    return true;
  }
  catch(std::string){
    return false;
  }

  return false;
}