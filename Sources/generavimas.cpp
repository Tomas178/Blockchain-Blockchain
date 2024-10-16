#include "../Headers/funkcijos.h"
#include "../Headers/Transaction.h"
#include "../Headers/User.h"
#include "../Headers/Block.h"

void GenerateUsers(int kiekis, std::vector<User>& users){
    std::ofstream RF("Vartotojai.txt");

    for(int i = 0; i < kiekis; i++){
        users[i].SetName("Vardas" + std::to_string(i+1));
        users[i].SetPublicKey(Maisos_funkcija(RandomStringGeneravimas(64)));
        users[i].SetBalansas(std::round(RandomSkaicius(100.00, 1000000.00)*100.00)/100.00);
    }

    for(int i = 0; i < kiekis; i++){
        for(int j = 0; j < kiekis; j++){
            if(users[i].GetPublicKey() == users[j].GetPublicKey() && i != j){
                std::cout << "RASTA SUTAMPANCIU PUBLICKEY... VARTOTOJAI NEBEGENERUOJAMI" << std::endl;
                exit(1);
            }
        }
    }

    std::cout << "Viskas good! nera sutampanciu PublicKey" << std::endl;

    RF << std::left << std::setw(20) << "Vartotojo vardas:" << std::setw(70) << "PublicKey:" << std::setw(15) << "Balansas:" << std::endl;
    for(int i = 0; i < kiekis; i++){
        RF << std::left << std::setw(20) << users[i].GetName() << std::setw(70) <<
        users[i].GetPublicKey() << std::setw(15) << users[i].GetBalansas() << std::endl;
    }
}

std::string RandomStringGeneravimas(int ilgis) {
    std::string simboliu_seka = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string random_string;
    std::random_device rd; 
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, simboliu_seka.size() - 1);

    for(unsigned int i = 0; i < ilgis; i ++){
        random_string += simboliu_seka[distribution(generator)];
    }
    return random_string;
}

double RandomSkaicius(double low, double high){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(low, high);
    return distribution(generator);
}

void GenerateTransactions(int kiekis, std::vector<Transaction>& transactions){
    std::ofstream RF("Transakcijos.txt");

    for(int i = 0; i < kiekis; i++){ 
        transactions[i].SetSender(RandomStringGeneravimas(64));
        transactions[i].SetReceiver(RandomStringGeneravimas(64));
        transactions[i].SetAmount(RandomSkaicius(100.00,1000000.00));
        transactions[i].SetTransactionID();
        //transactions[i] = Transaction(RandomStringGeneravimas(64), RandomStringGeneravimas(64), RandomSkaicius());
    }

    /*for(int i = 0; i < kiekis; i++){
        for(int j = 0; j < kiekis; j++){
            if(transactions[i].GetTransactionID() == transactions[j].GetTransactionID() && i != j){
                std::cout << "RASTA SUTAMPANCIU TRANSACTIONID... TRANSAKCIJOS NEBEGENERUOJAMOS" << std::endl;
                exit(1);
            }
        }
    }

    std::cout << "Viskas good! Nera sutampanciu TransactionID" << std::endl;*/

    RF << std::left << std::setw(70) << "Transakcijos ID:" << std::setw(70) << "Siuntejas:" << std::setw(70) << "Gavejas:" << std::setw(15) << "Suma:" << std::endl;
    for(int i = 0; i < kiekis; i++){
        RF << std::left << std::setw(70) << transactions[i].GetTransactionID() << std::setw(70) << transactions[i].GetSender() <<
        std::setw(70) << transactions[i].GetReceiver() << std::setw(15) << transactions[i].GetAmount() << std::endl;
    }
}

std::vector<std::vector<Transaction>> GenerateCandidates(std::vector<Transaction>& transactions, int BlockSize){
    int kandidatu_kiekis = 5;
    int transakciju_kiekis = (transactions.size() <= BlockSize) ? transactions.size() : BlockSize;

    std::vector<std::vector<Transaction>> Kandidatu_sarasas;
    std::vector<Transaction> Kandidatu_saraso_kopija = transactions;

    for(int i = 0; i < kandidatu_kiekis; i++){
        std::vector<Transaction> Kandidatai;

        for(int j = 0; j < transakciju_kiekis; j++){
            int kandidato_indeksas = RandomSkaicius(0, Kandidatu_saraso_kopija.size()-1);
            Kandidatai.push_back(Kandidatu_saraso_kopija[kandidato_indeksas]);
            Kandidatu_saraso_kopija.erase(Kandidatu_saraso_kopija.begin() + kandidato_indeksas);
        }
        
        Kandidatu_sarasas.push_back(Kandidatai);
    }
    return Kandidatu_sarasas;
}

/*void uzduotis3(int kiekis, std::vector<Block>& blokai, std::vector<Transaction>& transactions){
    for(int i = 0; i < kiekis; i++){
        blokai[].
    }
    
}*/

/*Block GenerateGenesisBlock(){
    std::vector<Transaction> transactions;
    std::vector<Block> blokai;
    transactions.push_back(Transaction("Genesis", "Genesis", RandomSkaicius()));
    Block genesis("0", std::time(0), "1.0", 0, transactions);

}*/