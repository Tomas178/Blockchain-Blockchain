#ifndef BLOCK_H
#define BLOCK_H

#include "funkcijos.h"
#include <ctime>
#include "Transaction.h"

class Block {
    private:
        std::string PreviousHash;
        std::time_t Timestamp;
        std::string Version;
        std::string MerkleHash;
        int Nonce = 0;
        int Difficulty = 0;
        std::vector<Transaction> Transactions;

    public:
        Block() {};

        Block(std::string PreviousHash, std::time_t TimeStamp, std::string Version, int Difficulty, std::string MerkelHash, std::vector<Transaction> Transactions){
            this->PreviousHash = PreviousHash;
            this->Timestamp = TimeStamp;
            this->Version = Version;
            this->Difficulty = Difficulty;
            this->Transactions = Transactions;
            this->MerkleHash = MerkelHash;
        }

        void SetPreviousHash(std::string PreviousHash) {this->PreviousHash = PreviousHash;};
        void SetTimestamp(std::time_t Timestamp) {this->Timestamp = Timestamp;};
        void SetVersion(std::string Version) {this->Version = Version;};
        void SetMerkleHash(std::string MerkleHash) {this->MerkleHash = MerkleHash;};
        void SetNonce(int Nonce) {this->Nonce = Nonce;};
        void SetDifficulty(int Difficulty) {this->Difficulty = Difficulty;};
        void SetTransactions(std::vector<Transaction> Transactions) {this->Transactions = Transactions;};

        std::string GetPreviousHash() const {return PreviousHash;};
        std::time_t GetTimestamp() const {return Timestamp;};
        std::string GetVersion() const {return Version;};
        std::string GetMerkleHash() const {return MerkleHash;};
        int GetNonce() const {return Nonce;};
        int GetDifficulty() const {return Difficulty;};
        std::vector<Transaction> GetTransactions() const {return Transactions;};

};

#endif