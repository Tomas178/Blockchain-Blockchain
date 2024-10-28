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
#include <bitcoin/system.hpp>

class User;
class Transaction;
class Block;
class Data;

void PaddedInput(std::string& simboliu_seka);
void Salt(std::string& simboliu_seka);
std::string Maisos_funkcija(const std::string simboliu_seka);
void GenerateUsers(int kiekis, std::vector<User>& users);
void GenerateTransactions(int kiekis, std::vector<Transaction>& transactions);
std::string RandomStringGeneravimas(int ilgis);
double RandomSkaicius(double low, double high);
std::vector<std::vector<Transaction>> GenerateCandidates(std::vector<Transaction>& transactions, int BlockSize);
Block MineBlock(int& WinnerID, std::string PreviousHash, Block* PreviousBlockPointer, std::string Version, int Difficulty, std::vector<std::vector<Transaction>> Kandidatu_sarasas);
std::string create_merkle(std::vector<Transaction> transactions);

extern std::string simboliu_seka;

#endif