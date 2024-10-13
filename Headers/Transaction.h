#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "funkcijos.h"

class Transaction {
    private:
        std::string TransactionID;
        std::string Sender;
        std::string Receiver;
        double Amount; 

    public:
        Transaction(std::string Sender, std::string Receiver, double Amount){
            TransactionID = Maisos_funkcija(Sender + Receiver + std::to_string(Amount));
            this->Sender = Sender;
            this->Receiver = Receiver;
            this->Amount = Amount;
        }
};

#endif