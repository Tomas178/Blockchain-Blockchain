#ifndef HASHPOINTER_HPP
#define HASHPOINTER_HPP

#include "funkcijos.h"

template <class T>
class HashPointer {

    private:
        T* data_ptr;
        std::string hash;

    public:
        HashPointer(std::string hash, T* data_ptr = nullptr) : hash{hash}, data_ptr{data_ptr} {}
        
        std::string getHash() {
            return hash;
        }

        T* getPointer() {
            return data_ptr;
        }

        ~HashPointer() {
            delete data_ptr;
        }


};


#endif