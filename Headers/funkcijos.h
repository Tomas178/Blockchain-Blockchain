#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <string>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <bitset>
#include <sstream>
#include <list>

void PaddedInput(std::string& simboliu_seka);
void salt(std::string& simboliu_seka);
std::string Maisos_funkcija(const std::string simboliu_seka);

extern std::string simboliu_seka;

#endif