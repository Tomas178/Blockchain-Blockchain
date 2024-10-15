#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <string>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <bitset>
#include <sstream>
#include <vector>
#include <random>
#include <fstream>

void PaddedInput(std::string& simboliu_seka);
void salt(std::string& simboliu_seka);
std::string Maisos_funkcija(const std::string simboliu_seka);
void GenerateUsers(int kiekis);
void GenerateTransactions(int kiekis);
std::string RandomStringGeneravimas(int ilgis);
double RandomBalansoGeneravimas();

extern std::string simboliu_seka;

#endif