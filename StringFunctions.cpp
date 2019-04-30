#include <iostream>
#include <string>
#include <vector>
#include "StringFunctions.h"

using namespace std;

void TrimLeft(string &str){
    str.erase(0, str.find_first_not_of(' '));
}

void TrimRight(string &str) {
    str.erase(str.find_last_not_of(' ') + 1);
}

void Trim(string &str) {
    TrimLeft(str); 
    TrimRight(str); 
}

void decompose(string s, vector<string> &elements, char c){
  elements.resize(0);

  Trim(s);
  if(s.size() == 0) return;

	size_t pos = s.find(c);
	while(pos != string::npos){ //ate final da string
		string elem = s.substr(0, pos);
		Trim(elem);
		elements.push_back(elem);
		s.erase(0, pos+1);
		pos = s.find(c);
	}
	Trim(s);
	elements.push_back(s);
}

void decompose(string s, vector<string> &elements){
  elements.resize(0);

  Trim(s);
  if(s.size() == 0) return;

  size_t pos = s.find('/');
	while(pos != string::npos){ //ate final da string
		string elem = s.substr(0, pos);
		Trim(elem);
		elements.push_back(elem);
		s.erase(0, pos + 1);
		pos = s.find('/');
	}
	Trim(s);
	elements.push_back(s);
}

bool decompose(string s, vector<unsigned int> &elements, char c){
  //used to verify if value was converted
  //all values are unsigned, if after converting value <= -1, convertion failled or value is not unsigned
  vector<string> string_elem;
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

bool decompose(string s, vector<unsigned int> &elements){
  //used to verify if value was converted
  //all values are unsigned, if after converting value <= -1, convertion failled or value is not unsigned
  vector<string> string_elem;
  elements.resize(0);
  int value = -1; 

  decompose(s, string_elem);


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

bool string_to_int(string s, int &ret){
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

void read_int(int &ret){
  string reading_str;

  while(1){
    getline(cin, reading_str);

    try{
      ret = stoi(reading_str);
      break;
    }
    catch(const invalid_argument &ia){
      cout << "Invalid Input\n";
    }
  }
}