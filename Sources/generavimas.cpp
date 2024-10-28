#include "../Headers/funkcijos.h"
#include "../Headers/Transaction.h"
#include "../Headers/User.h"
#include "../Headers/Block.h"

void GenerateUsers(int kiekis, std::vector<User>& users){
    std::ofstream RF("Vartotojai.txt");

    for(int i = 0; i < kiekis; i++){
        users[i] = User();
        users[i].SetName("Vardas" + std::to_string(i+1));
        users[i].SetPublicKey(Maisos_funkcija(RandomStringGeneravimas(64)));
        users[i].SetBalansas(std::round(RandomSkaicius(100.00, 1000000.00)*100.00)/100.00);
    }

    for(int i = 0; i < kiekis; i++){
        for(int j = 0; j < kiekis; j++){
            if(users[i].GetPublicKey() == users[j].GetPublicKey() && i != j){
                std::cout << "RASTA SUTAMPANCIU PUBLICKEY... VARTOTOJAI NEBEGENERUOJAMI" << std::endl;
                exit(1);
            }
        }
    }

    std::cout << "Viskas good! nera sutampanciu PublicKey" << std::endl;

    RF << std::left << std::setw(20) << "Vartotojo vardas:" << std::setw(70) << "PublicKey:" << std::setw(15) << "Balansas:" << std::endl;
    for(int i = 0; i < kiekis; i++){
        RF << std::left << std::setw(20) << users[i].GetName() << std::setw(70) <<
        users[i].GetPublicKey() << std::setw(15) << users[i].GetBalansas() << std::endl;
    }
}

std::string RandomStringGeneravimas(int ilgis) {
    std::string simboliu_seka = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string random_string;
    std::random_device rd; 
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, simboliu_seka.size() - 1);

    for(unsigned int i = 0; i < ilgis; i ++){
        random_string += simboliu_seka[distribution(generator)];
    }
    return random_string;
}

double RandomSkaicius(double low, double high){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(low, high);
    return distribution(generator);
}

void GenerateTransactions(int kiekis, std::vector<Transaction>& transactions){
    std::ofstream RF("Transakcijos.txt");

    for(int i = 0; i < kiekis; i++){ 
        transactions[i] = Transaction();
        transactions[i].SetSender(RandomStringGeneravimas(64));
        transactions[i].SetReceiver(RandomStringGeneravimas(64));
        transactions[i].SetAmount(RandomSkaicius(100.00,1000000.00));
        transactions[i].SetTransactionID();
        //transactions[i] = Transaction(RandomStringGeneravimas(64), RandomStringGeneravimas(64), RandomSkaicius());
    }

    /*for(int i = 0; i < kiekis; i++){
        for(int j = 0; j < kiekis; j++){
            if(transactions[i].GetTransactionID() == transactions[j].GetTransactionID() && i != j){
                std::cout << "RASTA SUTAMPANCIU TRANSACTIONID... TRANSAKCIJOS NEBEGENERUOJAMOS" << std::endl;
                exit(1);
            }
        }
    }

    std::cout << "Viskas good! Nera sutampanciu TransactionID" << std::endl;*/

    RF << std::left << std::setw(70) << "Transakcijos ID:" << std::setw(70) << "Siuntejas:" << std::setw(70) << "Gavejas:" << std::setw(15) << "Suma:" << std::endl;
    for(int i = 0; i < kiekis; i++){
        RF << std::left << std::setw(70) << transactions[i].GetTransactionID() << std::setw(70) << transactions[i].GetSender() <<
        std::setw(70) << transactions[i].GetReceiver() << std::setw(15) << transactions[i].GetAmount() << std::endl;
    }
}

std::vector<std::vector<Transaction>> GenerateCandidates(std::vector<Transaction>& transactions, int BlockSize){
    int kandidatu_kiekis = 5;
    int transakciju_kiekis = (transactions.size() <= BlockSize) ? transactions.size() : BlockSize;

    std::vector<std::vector<Transaction>> Kandidatu_sarasas;
    std::vector<Transaction> Kandidatu_saraso_kopija = transactions;

    for(int i = 0; i < kandidatu_kiekis; i++){
        std::vector<Transaction> Kandidatai;
        Kandidatai.reserve(transakciju_kiekis);

        for(int j = 0; j < transakciju_kiekis; j++){
            int kandidato_indeksas = RandomSkaicius(0, Kandidatu_saraso_kopija.size()-1);
            Kandidatai.push_back(Kandidatu_saraso_kopija[kandidato_indeksas]);
            Kandidatu_saraso_kopija.erase(Kandidatu_saraso_kopija.begin() + kandidato_indeksas);
        }
        Kandidatu_sarasas.push_back(Kandidatai);
    }
    return Kandidatu_sarasas;
}

Block MineBlock(int& WinnerID, std::string PreviousHash, Block* PreviousBlockPointer, std::string Version, int Difficulty, std::vector<std::vector<Transaction>> Kandidatu_sarasas){
    int Max_Bandymai = 10000;

    while(true){
        bool mined = false;

        for(int i = 0; i <= Kandidatu_sarasas.size(); i++){
            int Nonce = 0;
            std::string MasterString = "";
            std::string MasterHash = "";

            std::string Merkel_Root_Hash = create_merkle(Kandidatu_sarasas[i]);
            std::cout << Merkel_Root_Hash << std::endl;


            for(int j = 0; j < Max_Bandymai; j++){
                double randomskaicius = RandomSkaicius(0.0, 999999.0);
                Nonce = std::round(randomskaicius);
                MasterString = std::to_string(Nonce) + PreviousHash + Version + Merkel_Root_Hash + std::to_string(Difficulty);
                MasterHash = Maisos_funkcija(MasterString);
                //std::cout << "MasterString = "<< MasterString << std::endl;
                //std::cout << "MasterHash = "<< MasterHash << std::endl;

                for(int i = 0; i < Difficulty; i++){
                    if(MasterHash[i] != '0') break;
                    if(i == Difficulty - 1) mined = true;
                }

                if(mined){
                    WinnerID = i+1;
                    std::time_t TimeStamp = std::time(nullptr);

                    // Output the time in seconds since the epoch
                    std::cout << "Current time in seconds since epoch: " << TimeStamp << std::endl;

                    // Optionally, convert to a human-readable format
                    std::cout << "Human-readable time: " << std::ctime(&TimeStamp); // std::ctime converts time_t to a string

                    return Block(PreviousHash, PreviousBlockPointer, MasterHash, TimeStamp, Version, Difficulty, Nonce, Merkel_Root_Hash, Kandidatu_sarasas[i]);
                }
            }
        }   
        std::cout << "All candidates failed... decreasing the difficulty..." << std::endl;
        Difficulty--;
    }
}

std::string create_merkle(std::vector<Transaction> transactions)
{

    bc::hash_list merkle = {};

    for(int i = 0; i<transactions.size(); i++) {

        char char_array[65];
        strcpy(char_array, transactions[i].GetTransactionID().c_str());
        
        bc::hash_digest temp_hash = bc::hash_literal(char_array);
        merkle.push_back(temp_hash);
    }

    // Stop if hash list is empty or contains one element
    if (merkle.empty()) return bc::encode_base16(bc::null_hash);
    else if (merkle.size() == 1) return bc::encode_base16(merkle[0]);


    // While there is more than 1 hash in the list, keep looping...
    while (merkle.size() > 1) {

        // If number of hashes is odd, duplicate last hash in the list.
        if (merkle.size() % 2 != 0) merkle.push_back(merkle.back());

        // List size is now even.
        assert(merkle.size() % 2 == 0);

        // New hash list.
        bc::hash_list new_merkle;

        // Loop through hashes 2 at a time.
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            // Join both current hashes together (concatenate).
            bc::data_chunk concat_data(bc::hash_size * 2);
            auto concat = bc::serializer<decltype(concat_data.begin())>(concat_data.begin());

            concat.write_hash(*it);
            concat.write_hash(*(it + 1));

            // Hash both of the hashes.
            bc::hash_digest new_root = bc::bitcoin_hash(concat_data);

            // Add this to the new list.
            new_merkle.push_back(new_root);
        }

        // This is the new list.
        merkle = new_merkle;
    }
    // Finally we end up with a single item.
    return bc::encode_base16(merkle[0]);
}
