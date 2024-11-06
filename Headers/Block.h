#ifndef BLOCK_H
#define BLOCK_H

#include "funkcijos.h"
#include <ctime>
#include "Transaction.h"

class Block {
    private:
        //HashPointer<Block> PreviousBlock;
        std::string PreviousHash;
        Block* PreviousBlockPointer;
        std::string MasterHash;
        std::string TimeStamp;
        std::string Version;
        std::string MerkleHash;
        int Nonce = 0;
        int Difficulty = 0;
        std::vector<Transaction> Transactions;

    public:
        Block() {};
    
        Block(std::string PreviousHash, Block* PreviousBlockPointer, std::string MasterHash, std::time_t TimeStamp, std::string Version, int Difficulty, int Nonce, std::string MerkelHash, std::vector<Transaction> Transactions) :
            //PreviousBlock{PreviousHash, PreviousBlockPointer},
            PreviousHash{PreviousHash},
            PreviousBlockPointer{PreviousBlockPointer},
            MasterHash{MasterHash},
            TimeStamp{std::ctime(&TimeStamp)},
            Version{Version},
            MerkleHash{MerkelHash},
            Nonce{Nonce},
            Difficulty{Difficulty},
            Transactions{Transactions} {};
        
        void SetMasterHash(std::string MasterHash) {this->MasterHash = MasterHash;};
        void SetPreviousHash(std::string PreviousHash) {this->PreviousHash = PreviousHash;};
        void SetPreviousBlockPointer(Block* PreviousBlockPointer) {this->PreviousBlockPointer = PreviousBlockPointer;};
        void SetTimeStamp(std::time_t TimeStamp) {this->TimeStamp = std::ctime(&TimeStamp);};
        void SetVersion(std::string Version) {this->Version = Version;};
        void SetMerkleHash(std::string MerkleHash) {this->MerkleHash = MerkleHash;};
        void SetNonce(int Nonce) {this->Nonce = Nonce;};
        void SetDifficulty(int Difficulty) {this->Difficulty = Difficulty;};
        void SetTransactions(std::vector<Transaction> Transactions) {this->Transactions = Transactions;};

        std::string GetMasterHash() const {return MasterHash;};
        std::string GetPreviousHash() const {return PreviousHash;};
        Block* GetPreviousBlockPointer() const {return PreviousBlockPointer;}; 
        std::string GetTimeStamp() const {return TimeStamp;};
        std::string GetVersion() const {return Version;};
        std::string GetMerkleHash() const {return MerkleHash;};
        int GetNonce() const {return Nonce;};
        int GetDifficulty() const {return Difficulty;};
        std::vector<Transaction> GetTransactions() const {return Transactions;};

        void print(){
            std::cout << "BLOCK HASH: " << this->MasterHash << std::endl;
            std::cout << "PREVIOUS HASH: " << this->PreviousHash << std::endl;
            std::cout << "ISKASIMO LAIKAS: " << this->TimeStamp;
            std::cout << "TRANSAKCIJU KIEKIS: " << this->Transactions.size() << std::endl;
            std::cout << "DIFFICULTY: " << this->Difficulty << std::endl;
            std::cout << "MERKLE ROOT HASH: " << this->MerkleHash << std::endl;
            std::cout << "VERSION: " << this->Version << std::endl;
            std::cout << "NONCE: " << this->Nonce << std::endl;
            std::cout << "PASKUTINES TRANSAKCIJOS ID: " << this->Transactions.back().GetTransactionID() << std::endl << std::endl;
        }

        ~Block() {};
};

#endif