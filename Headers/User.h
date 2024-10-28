#ifndef USER_H
#define USER_H

#include "funkcijos.h"
#include <cmath>

class User {
    private:
        std::string Name;
        std::string PublicKey;
        int Balance;

    public:
        User() : Name(""), PublicKey(""), Balance(0) {}

        User(std::string Name, std::string PublicKey, int Balance){
            this->Name = Name;
            this->PublicKey = PublicKey;
            this->Balance = Balance;
        }

        std::string GetName() const {return Name;};
        std::string GetPublicKey() const {return PublicKey;};
        int GetBalansas() const {return Balance;};

        void SetName(const std::string Name) {this->Name = Name;};
        void SetPublicKey(const std::string PublicKey) {this->PublicKey = PublicKey;};
        void SetBalansas(const int Balance) {this->Balance = Balance;};
};

#endif