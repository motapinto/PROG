#pragma once

#include <iostream>
#include <vector>
#include <string>

void TrimLeft(std::string &str);

void TrimRight(std::string &str);

void Trim(std::string &str);

void decompose(std::string s, std::vector<std::string> &elements, char c);

void decompose(std::string s, std::vector<std::string> &elements);

bool decompose(std::string s, std::vector<unsigned int> &elements, char c);

bool decompose(std::string s, std::vector<unsigned int> &elements);

bool string_to_int(std::string s, int &ret);

void read_string(std::string &str);

void read_uint(unsigned int &init_store);

void read_int(int &init_store);