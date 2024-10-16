#include "../Headers/funkcijos.h"
#include "../Headers/Transaction.h"
#include "../Headers/User.h"
#include "../Headers/Block.h"
#include "../Headers/Data.h"

int main(){

    int UsersCount = 1000;
    int TransactionsCount = 10000;
    int BlockSize = 100;

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

    std::cout << "Kasamas Genesis blokas..." << std::endl;
    Kandidatu_sarasas = GenerateCandidates(transactions, BlockSize);
    std::cout << "Kandidatu saraso dydis: " << Kandidatu_sarasas.size() << std::endl;
    for(auto& sarasas : Kandidatu_sarasas){
        std::cout << "Kandidato bandymu kiekis: " << sarasas.size() << std::endl;
        for(auto& transakcija : sarasas){
            std::cout << transakcija.GetTransactionID() << std::endl;
        }
    }
    std::cout << "Genesis bloko duomenys galima rasti GenesisBlokas.txt" << std::endl << std::endl;
    return 0;
}