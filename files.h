#include <fstream>
#include "agency.h"

#define BUFFER_SIZE 50

bool last_line(std::string line);

int read_agency(Agency &agency, std::string agency_file_name, std::string &clients_file_name, std::string &packs_file_name);

int read_clients(Agency &agency, std::string clients_file_name);

int read_packs(Agency &agency, std::string packs_file_name);

int read_files(Agency &agency, std::string agency_file_name, std::string &clients_file_name, std::string &packs_file_name);

void write_agency(Agency &agency, const std::string agency_file_name, const std::string clients_file_name, const std::string packs_file_name);

void write_clients(Agency &agency, const std::string clients_file_name);

void write_packs(Agency &agency, const std::string packs_file_name);
