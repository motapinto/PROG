#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include "client.h"
#include "StringFunctions.h"

using namespace std;

Client::Client() { this->nif = 0; this->family_num = 0; this->tour_packs_bought.resize(0); }

Client::Client(string name, string address, vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num) {
    this->client_name = name;
    this->client_address.setAddress(address);
    if(verifyPacksBought(tour_packs_bought)) this->tour_packs_bought = tour_packs_bought;
    else this->tour_packs_bought.resize(0);
    this->nif = nif;
    this->family_num = family_num;
}

Client::Client(string name, Address address, vector<unsigned int> tour_packs_bought, unsigned int nif, unsigned int family_num) {
  this->client_name = name;
  this->client_address = address;
  if(verifyPacksBought(tour_packs_bought)) this->tour_packs_bought = tour_packs_bought;
  else this->tour_packs_bought.resize(0);
  this->nif = nif;
  this->family_num = family_num;
}

bool Client::addPack(unsigned int pack_id){
  for(size_t i = 0; i < tour_packs_bought.size(); i++)
    if(tour_packs_bought.at(i) == pack_id)
      return false;

  this->tour_packs_bought.push_back(pack_id);
  return true;
}

void Client::setName (string new_name) { this->client_name = new_name; }
void Client::setAddress(Address address) { this->client_address = address; }
bool Client::setAddress(string address) { return this->client_address.setAddress(address); }
bool Client::setTourPacks(vector <unsigned int> packs) { 
  if(verifyPacksBought(packs) == false) return false;
  this->tour_packs_bought = packs; 
  return true;
}
bool Client::setTourPacks(string packs, char delim) { 
  vector<unsigned int> packs_bought;

  if(packs.compare("-") == 0){
    this->tour_packs_bought.resize(0); //eliminate previous values
    return true;
  } 

  if(decompose(packs, packs_bought, delim) == true){
    if(verifyPacksBought(packs_bought)){
      this->tour_packs_bought = packs_bought;
      return true; 
    }
  }

  return false;
}
void Client::setNif(unsigned int nif) { this->nif = nif; }
void Client::setFamilyNum(unsigned int family_num) {this->family_num = family_num;}

string Client::getName(void){ return this->client_name; }
Address Client::getAddress(void){ return this->client_address; }
vector <unsigned int> Client::getTourPacksBought(void) { return this->tour_packs_bought; }
unsigned int Client::getNif(void) { return this->nif; }
unsigned int Client::getFamilyNum(void){ return this->family_num; }
unsigned int Client::getNumOfBuys(void){ return this->tour_packs_bought.size(); }

bool Client::verifyPacksBought(vector<unsigned int> packs){
  for(size_t i = 0; i < packs.size(); i++){
    for(size_t j = 0; j < packs.size(); j++){
      if(i == j) continue;
      if(packs.at(i) == packs.at(j))
        return false;
    }
  }
  return true;
}