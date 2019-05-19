#include <iostream>
#include <cmath>
#include <iomanip>
#include "files.h"
#include "menu.h"

using namespace std;

Agency agency;
bool modified = false;

int main() {
  string agency_file;
  string client_file;
  string packs_file;

  cout << "Agency file to read: ";
  cin >> agency_file; 

  if ( read_files(agency, agency_file, client_file, packs_file) != 0 )
    return -1;

  start_menu();

  if(modified == true) {
    write_agency(agency, agency_file, client_file, packs_file);
    write_clients(agency, client_file);
    write_packs(agency, packs_file);
  }

  return 0;
}