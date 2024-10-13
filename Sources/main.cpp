#include "../Headers/funkcijos.h"

int main(){
    std::string simboliu_seka;
    std::cout << "Iveskite simboliu seka: ";
    std::getline(std::cin, simboliu_seka);
    std::cout << "Simboliu seka: " << simboliu_seka << std::endl;
    std::cout << "Maisos funkcijos rezultatas: " << Maisos_funkcija(simboliu_seka) << std::endl;
    return 0;
}