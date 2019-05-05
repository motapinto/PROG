#pragma once

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