#ifndef BLOCK_H
#define BLOCK_H

#include "funkcijos.h"
#include <ctime>
#include "Transaction.h"

class Block {
    private:
        std::string Hash;
        std::string PreviousHash;
        std::time_t Timestamp;
        std::string Version;
        std::string MerkleHash;
        int Nonce = 0;
        int Difficulty = 0;
        bool Mined = false;
        std::list<Transaction> Transactions;

    public:
        Block() {};

        Block(std::string PreviousHash, std::time_t TimeStamp, std::string Version, int Difficulty, std::list<Transaction> Transactions){
            this->PreviousHash = PreviousHash;
            this->Timestamp = TimeStamp;
            this->Version = Version;
            this->Difficulty = Difficulty;
            this->Transactions = Transactions;
        }

};

#endif