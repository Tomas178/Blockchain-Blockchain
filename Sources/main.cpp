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
    std::list<Block> Blockchain;

    std::vector<User> users(UsersCount);
    std::vector<Transaction> transactions(TransactionsCount);
    std::vector<std::vector<Transaction>> Kandidatu_sarasas;

    std::cout << "Vyksta 1 uzduotis... Generuojama 1000 tinklo vartotoju" << std::endl;
    GenerateUsers(UsersCount, users);
    std::cout << "Vartotoju duomenys galima rasti Vartotojai.txt" << std::endl << std::endl;
    
    std::cout << "Vyksta 2 uzduotis... Generuojama 10000 tinklo transakciju" << std::endl;
    transactions = GenerateTransactions(TransactionsCount, users);

    std::cout << "Transakciju kiekis: " << transactions.size() << std::endl;
    std::ofstream RF("Transakcijos.txt");
    RF << std::left << std::setw(70) << "Transakcijos ID" << std::setw(70) << "Siuntejas" << std::setw(70) << "Gavejas" << std::setw(15) << "Suma" << std::endl;
    for(int i = 0; i < transactions.size(); i++){
        RF << std::left << std::setw(70) << transactions[i].GetTransactionID() << std::setw(70) << transactions[i].GetSender() <<
        std::setw(70) << transactions[i].GetReceiver() << std::setw(15) << transactions[i].GetAmount() << std::endl;
    }
    RF.close();
    std::cout << "Transakciju duomenys galima rasti Transakcijos.txt" << std::endl << std::endl;

    std::cout << "Generuojami kandidatai..." << std::endl;
    Kandidatu_sarasas = GenerateCandidates(transactions, BlockSize);
    std::cout << "Kandidatai sugeneruoti sekmingai." << std::endl << std::endl;

    std::cout << "Kasamas Genesis Blokas..." << std::endl;
    Blockchain_Head = new Block(MineBlock(WinnerID, GenesisPreviousHash, nullptr, Version, Difficulty, Kandidatu_sarasas));
    Blockchain.push_back(*Blockchain_Head);
    std::cout << "Genesis blokas iskastas sekmingai:)" << std::endl << std::endl;
    for(Transaction transaction : Blockchain_Head->GetTransactions()){
        transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
        [&transaction](const Transaction& t) { return t.GetTransactionID() == transaction.GetTransactionID(); }),
        transactions.end());
    }

    printBlockChain(Blockchain);

    std::cout << "Daromos transakcijos kasejams..." << std::endl;
    AtliktiTransakcijas(transactions, Blockchain_Head->GetTransactions(), users);
    std::cout << "Transakcijos atliktos sekmingai." << std::endl << std::endl;

    std::cout << "Isvedami vartotoju balansai po transakciju..." << std::endl;
    std::ofstream RF2("Vartotojai_Po_Pirmu_Transakciju.txt");
    RF2 << std::left << std::setw(20) << "Vartotojo vardas:" << std::setw(70) << "PublicKey:" << std::setw(15) << "Balansas:" << std::endl;
    for(int i = 0; i < users.size(); i++){
        RF2 << std::left << std::setw(20) << users[i].GetName() << std::setw(70) <<
        users[i].GetPublicKey() << std::setw(15) << users[i].GetBalansas() << std::endl;
    }
    RF2.close();
    std::cout << "Vartotoju balansai po transakciju galima rasti Vartotojai_Po_Pirmu_Transakciju.txt" << std::endl << std::endl;

    std::cout << "Genesis bloko informacija: " << std::endl;
    IsvestiBloka(WinnerID, BlockCount, Blockchain_Head);
    std::cout << "Genesis bloko informacija isvesta .txt faile!" << std::endl << std::endl;
    Kandidatu_sarasas.clear();
    BlockCount++;

    std::cout << "Likes transakciju kiekis: " << transactions.size() << std::endl;

    std::string atsakymas;
    std::cout << "Ar norite kasti nauja bloka? (y/n)" << std::endl; std::cin >> atsakymas;
    while(atsakymas == "y"){
        std::cout << "Generuojami kandidatai..." << std::endl;
        Kandidatu_sarasas = GenerateCandidates(transactions, BlockSize);
        std::cout << "Kandidatai sugeneruoti sekmingai." << std::endl << std::endl;
        Blockchain_Head = new Block(MineBlock(WinnerID, Blockchain_Head->GetMasterHash(), Blockchain_Head, Version, Difficulty, Kandidatu_sarasas));
        Blockchain.push_back(*Blockchain_Head);
        for(Transaction transaction : Blockchain_Head->GetTransactions()){
            transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
            [&transaction](const Transaction& t) { return t.GetTransactionID() == transaction.GetTransactionID(); }),
            transactions.end());
        }
        AtliktiTransakcijas(transactions, Blockchain_Head->GetTransactions(), users);
        IsvestiBloka(WinnerID, BlockCount, Blockchain_Head);
        Kandidatu_sarasas.clear();
        BlockCount++;
        std::cout << "Likes transakciju kiekis: " << transactions.size() << std::endl;
        std::cout << "Ar norite kasti nauja bloka? (y/n)" << std::endl; std::cin >> atsakymas;
    }

    std::cout << "Isvedami vartotoju balansai po transakciju..." << std::endl;
    std::ofstream RF3("Vartotojai_Po_Visu_Transakciju.txt");
    RF3 << std::left << std::setw(20) << "Vartotojo vardas:" << std::setw(70) << "PublicKey:" << std::setw(15) << "Balansas:" << std::endl;
    for(int i = 0; i < users.size(); i++){
        RF3 << std::left << std::setw(20) << users[i].GetName() << std::setw(70) <<
        users[i].GetPublicKey() << std::setw(15) << users[i].GetBalansas() << std::endl;
    }
    RF3.close();
    std::cout << "Vartotoju balansai po transakciju galima rasti Vartotojai_Po_Visu_Transakciju.txt" << std::endl << std::endl;

    //printBlockInChain(Blockchain, 2);
    //printBlockChain(Blockchain);

    return 0;
}