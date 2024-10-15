#include "../Headers/funkcijos.h"
#include "../Headers/Transaction.h"
#include "../Headers/User.h"

void GenerateUsers(int kiekis) {
    std::ofstream RF("Vartotojai.txt");
    std::vector<User> users(kiekis);

    for(int i = 0; i < kiekis; i++){
        users[i].SetName("Vardas" + std::to_string(i+1));
        users[i].SetPublicKey(Maisos_funkcija(RandomStringGeneravimas(64)));
        users[i].SetBalansas(std::round(RandomBalansoGeneravimas()*100.00)/100.00);
    }

    for(int i = 0; i < kiekis; i++){
        RF << "Vartotojo vardas: "<< users[i].GetName() << std::endl;
        RF << "PublicKey: " << users[i].GetPublicKey() << std::endl;
        RF << "Balansas: " << users[i].GetBalansas() << std::endl;
        RF << std::endl;
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

double RandomBalansoGeneravimas(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(100.0, 1000000.0);
    return distribution(generator);
}

void GenerateTransactions(int kiekis){
    std::ofstream RF("Transakcijos.txt");
    std::vector<Transaction> transactions(kiekis);

    for(int i = 0; i < kiekis; i++){ 
        transactions[i].SetSender(RandomStringGeneravimas(64));
        transactions[i].SetReceiver(RandomStringGeneravimas(64));
        transactions[i].SetAmount(RandomBalansoGeneravimas());
        transactions[i].SetTransactionID();
        //transactions[i] = Transaction(RandomStringGeneravimas(64), RandomStringGeneravimas(64), RandomBalansoGeneravimas());
    }

    for(int i = 0; i < kiekis; i++){
        RF << "Transakcijos ID: " << transactions[i].GetTransactionID() << std::endl;
        RF << "Siuntejas: " << transactions[i].GetSender() << std::endl;
        RF << "Gavejas: " << transactions[i].GetReceiver() << std::endl;
        RF << "Suma: " << transactions[i].GetAmount() << std::endl;
        RF << std::endl;
    }
}