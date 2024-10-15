#include "../Headers/funkcijos.h"

void PaddedInput(std::string& simboliu_seka){
    simboliu_seka += "11111";
}

void Salt(std::string& simboliu_seka){
    std::string salt = "AZ!@#()&,v;em.gT";
    simboliu_seka += salt;
}


std::string Maisos_funkcija(const std::string simboliu_seka){

    std::string nauja_simboliu_seka = simboliu_seka;
    Salt(nauja_simboliu_seka);
    const unsigned int size = nauja_simboliu_seka.length();
    std::bitset<8> bit_map(size);
    const unsigned int hash_parts = 4;

    unsigned long long hashes[hash_parts] = {
        0x6a09e667f3bcc908,
        0x9b05688c2b3e6c1f,
        0x1f83d9abfb41bd6b,
        0x5be0cd19137e2179
    };

    PaddedInput(nauja_simboliu_seka);

    for(char c : nauja_simboliu_seka){
        bit_map = std::bitset<8>(c);
        bit_map.flip();
        for(int i = 0; i < hash_parts; i++){
            hashes[i] ^= bit_map.to_ulong() * 0x9e3779b97f4a7c15;
            hashes[i] = (hashes[i] << 5) | (hashes[i] >> 59);
        }
    }

    std::ostringstream oss;
    for(int i = 0; i < hash_parts; i++){
        oss << std::hex << std::setw(16) << std::setfill('0') << hashes[i];
    }
    return oss.str();
}