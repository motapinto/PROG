#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <exception>

void TrimLeft(std::string &str);

void TrimRight(std::string &str);

void Trim(std::string &str);

void decompose(std::string s, std::vector<std::string> &elements, char c);

bool decompose(std::string s, std::vector<unsigned int> &elements, char c);

bool string_to_int(std::string s, int &ret);

void read_string(std::string &str);

template <class T>
bool Try(void func(T &param), T &param);