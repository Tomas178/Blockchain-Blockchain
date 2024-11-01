#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "funkcijos.h"

class Transaction {
    private:
        std::string TransactionID;
        std::string Sender;
        std::string Receiver;
        int Amount; 

    public:
        Transaction() : TransactionID(""), Sender(""), Receiver(""), Amount(0) {}

        Transaction(std::string Sender, std::string Receiver, int Amount){
            this->TransactionID = Maisos_funkcija(Sender + Receiver + std::to_string(Amount));
            this->Sender = Sender;
            this->Receiver = Receiver;
            this->Amount = Amount;
        }

        void SetTransactionID() {this->TransactionID = Maisos_funkcija(GetSender() + GetReceiver() + std::to_string(GetAmount()));};
        void SetSender(std::string Sender) {this->Sender = Sender;};
        void SetReceiver(std::string Receiver) {this->Receiver = Receiver;};
        void SetAmount(int Amount) {this->Amount = Amount;};
        
        std::string GetTransactionID() const {return TransactionID;};
        std::string GetSender() const {return Sender;};
        std::string GetReceiver() const {return Receiver;};
        int GetAmount() const {return Amount;};
};

#endif