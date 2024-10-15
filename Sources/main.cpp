#include "../Headers/funkcijos.h"

int main(){
    std::cout << "Vyksta 1 uzduotis... Generuojama 1000 tinklo vartotoju" << std::endl;
    GenerateUsers(1000);
    std::cout << "Vartotoju duomenys galima rasti Vartotojai.txt" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Vyksta 2 uzduotis... Generuojama 10000 tinklo transakciju" << std::endl;
    GenerateTransactions(10000);
    std::cout << "Transakciju duomenys galima rasti Transakcijos.txt" << std::endl;
    return 0;
}