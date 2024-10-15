#ifndef DUOMENYS_H
#define DUOMENYS_H

#include "funkcijos.h"
#include "Transaction.h"
#include "User.h"

class Data {
    public:
        std::vector<User> Users;
        std::vector<Transaction> Transactions;
};

#endif