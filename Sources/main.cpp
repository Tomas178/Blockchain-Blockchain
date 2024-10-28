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
    int Difficulty = 5;
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
    GenerateTransactions(TransactionsCount, transactions, users);

    std::ofstream("Transakcijos.txt");
    for(int i = 0; i < transactions.size(); i++){
        std::ofstream RF("Transakcijos.txt");
        RF << std::left << std::setw(70) << transactions[i].GetTransactionID() << std::setw(70) << transactions[i].GetSender() <<
        std::setw(70) << transactions[i].GetReceiver() << std::setw(15) << transactions[i].GetAmount() << std::setw(15) << transactions[i].GetTransakcijosIndex() << std::endl;
    }
    std::cout << "Transakciju duomenys galima rasti Transakcijos.txt" << std::endl << std::endl;

    std::cout << "Generuojami kandidatai..." << std::endl;
    Kandidatu_sarasas = GenerateCandidates(transactions, BlockSize);
    std::cout << "Kandidatai sugeneruoti sekmingai." << std::endl << std::endl;

    std::cout << "Kasamas Genesis Blokas..." << std::endl;
    Blockchain_Head = new Block(MineBlock(WinnerID, GenesisPreviousHash, nullptr, Version, Difficulty, Kandidatu_sarasas));
    std::cout << "Genesis blokas iskastas sekmingai:)" << std::endl << std::endl;

    std::cout << "Daromos transakcijos kasejams..." << std::endl;
    AtliktiTransakcijas(transactions, Blockchain_Head->GetTransactions(), users);
    std::cout << "Transakcijos atliktos sekmingai." << std::endl << std::endl;

    std::cout << "Genesis bloko informacija: " << std::endl;
    IsvestiBloka(WinnerID, BlockCount, Blockchain_Head);
    std::cout << "Genesis bloko informacija isvesta .txt faile!" << std::endl << std::endl;

    BlockCount++;

    return 0;
}