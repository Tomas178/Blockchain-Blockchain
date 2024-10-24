#include "../Headers/funkcijos.h"
#include "../Headers/Transaction.h"
#include "../Headers/User.h"
#include "../Headers/Block.h"
#include "../Headers/Data.h"

int main(){

    int UsersCount = 1000;
    int TransactionsCount = 10000;
    int BlockSize = 100;
    std::string GenesisPreviousHash = "Tomas";
    Block* Blockchain_Head;
    int Difficulty = 3;
    int WinnerID = 0;
    std::string Version = "1.0";
    int BlockCount = 0;

    std::vector<User> users(UsersCount);
    std::vector<Transaction> transactions(TransactionsCount);
    std::vector<std::vector<Transaction>> Kandidatu_sarasas;


    std::cout << "Vyksta 1 uzduotis... Generuojama 1000 tinklo vartotoju" << std::endl;
    GenerateUsers(UsersCount, users);
    std::cout << "Vartotoju duomenys galima rasti Vartotojai.txt" << std::endl << std::endl;
    
    std::cout << "Vyksta 2 uzduotis... Generuojama 10000 tinklo transakciju" << std::endl;
    GenerateTransactions(TransactionsCount, transactions);
    std::cout << "Transakciju duomenys galima rasti Transakcijos.txt" << std::endl << std::endl;

    /*std::cout << "Vyksta 3 uzduotis... Generuojama 100 random transakciju i bloka" << std::endl;
    uzduotis3(BlockSize, block, transactions);
    std::cout << "Bloko duomenys galima rasti Blokas.txt" << std::endl << std::endl;
    */

    Kandidatu_sarasas = GenerateCandidates(transactions, BlockSize);
    Blockchain_Head = new Block(MineBlock(WinnerID, GenesisPreviousHash, nullptr, Version, Difficulty, Kandidatu_sarasas));

    return 0;
}