#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include "date.h"
#include "StringFunctions.h"

using namespace std;

int setDate(Date &date, string s){
  vector<unsigned int> elements;
  
  if(decompose(s, elements) == false) return -1;

  if(elements.size() != 3) return -1;


  date.day = elements.at(2);
  date.month = elements.at(1);
  date.year = elements.at(0);

  if(date.day == 0 || date.day > 31) return 1;
  if(date.month == 0 || date.month > 12) return 1;

  return 0;
}

string getDate(Date date){
  string s;

  if(date.year < 1000)
    s.push_back('0');
  if(date.year < 100)
    s.push_back('0');
  if(date.year < 10)
    s.push_back('0');
  s.append(to_string(date.year));

  s.append("/");
  if(date.month < 10)
    s.push_back('0');
  s.append(to_string(date.month));
  
  s.append("/");
  if(date.day < 10)
    s.push_back('0');
  s.append(to_string(date.day));

  return s;
}

int getIntDate(Date date){
  return date.day + date.month*30 + date.year * 365;
}