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
        users[i].SetBalansas(RandomSkaicius(100, 1000000));
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

std::vector<Transaction> GenerateTransactions(int kiekis, std::vector<User>& users){
    std::vector<Transaction> transactions = {};
    transactions.reserve(kiekis);
    for(int i = 0; i < kiekis; i++){ 
        User Sender, Receiver;
        do{
            Sender = users.at(RandomSkaicius(0, users.size()-1));
            Receiver = users.at(RandomSkaicius(0, users.size()-1));
        } while(Sender.GetPublicKey() == Receiver.GetPublicKey());
        int amount = RandomSkaicius(1, Sender.GetBalansas());
        if(!Sender.GetPublicKey().empty() && !Receiver.GetPublicKey().empty() && amount > 0){
            transactions.push_back(Transaction(Sender.GetPublicKey(), Receiver.GetPublicKey(), amount));
        }
    }
    std::cout << "Transakcijos sugeneruotos sekmingai" << std::endl;
    return transactions;
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

int RandomSkaicius(int low, int high){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(low, high);
    return distribution(generator);
}

std::vector<std::vector<Transaction>> GenerateCandidates(std::vector<Transaction>& transactions, int BlockSize){
    int kandidatu_kiekis = 5;
    int transakciju_kiekis = (transactions.size() <= BlockSize) ? transactions.size() : BlockSize;

    std::vector<std::vector<Transaction>> Kandidatu_sarasas = {};

    for(int i = 0; i < kandidatu_kiekis; i++){
        std::vector<Transaction> Kandidatu_saraso_kopija = transactions;
        std::vector<Transaction> Kandidatai = {};

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
    int Max_Bandymai = 100000;

    while(true){
        bool mined = false;

        for(int i = 0; i < Kandidatu_sarasas.size(); i++){
            int Nonce = 0;
            std::string MasterString = "";
            std::string MasterHash = "";

            std::string Merkel_Root_Hash = create_merkle(Kandidatu_sarasas[i]);
            std::cout << "Merkel Root Hash: "<< Merkel_Root_Hash << std::endl;


            for(int j = 0; j < Max_Bandymai; j++){
                double randomskaicius = RandomSkaicius(0, 999999);
                Nonce = std::round(randomskaicius);
                MasterString = std::to_string(Nonce) + PreviousHash + Version + Merkel_Root_Hash + std::to_string(Difficulty);
                MasterHash = Maisos_funkcija(MasterString);
                //std::cout << "MasterString = "<< MasterString << std::endl;
                //std::cout << "MasterHash = "<< MasterHash << std::endl;

                for(int z = 0; z < Difficulty; z++){
                    if(MasterHash[z] != '0') break;
                    if(z == Difficulty - 1) mined = true;
                }

                if(mined){
                    WinnerID = i+1;
                    std::time_t TimeStamp = std::time(nullptr);

                    std::cout << "MasterString: " << MasterString << std::endl;
                    std::cout << "MasterHash: " << MasterHash << std::endl;
                    std::cout << "Nonce: " << Nonce << std::endl;
                    std::cout << "WinnerID: " << WinnerID << std::endl;


                    // Output the time in seconds since the epoch
                    std::cout << "Current time in seconds since epoch: " << TimeStamp << std::endl;

                    // Optionally, convert to a human-readable format
                    std::cout << "Human-readable time: " << std::ctime(&TimeStamp); // std::ctime converts time_t to a string

                    return Block(PreviousHash, PreviousBlockPointer, MasterHash, TimeStamp, Version, Difficulty, Nonce, Merkel_Root_Hash, Kandidatu_sarasas[i]);
                }
            }
        }   
        std::cout << "VISIEMS KANDIDATAMS NEPAVYKO... MAZINAMAS DIFFICULTY..." << std::endl;
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

void AtliktiTransakcijas(std::vector<Transaction>& transactions, std::vector<Transaction> BlockTransactions, std::vector<User>& users){

    for(Transaction transaction : BlockTransactions){
        std::string SenderPubKey = transaction.GetSender();
        std::string ReceiverPubKey = transaction.GetReceiver();
        int SenderIndex = -1;
        int ReceiverIndex = -1;

        for(int i = 0; i < users.size(); i++){
            if(SenderPubKey == users[i].GetPublicKey()) SenderIndex = i;
            else if (ReceiverPubKey == users[i].GetPublicKey()) ReceiverIndex = i;
        }
        if(SenderIndex == -1 || ReceiverIndex == -1){
            std::cout << "NERASTAS VARTOTOJAS... TRANSAKCIJA NEATLIKTA" << std::endl;
            break;
        }

        if(users[SenderIndex].GetBalansas() >= transaction.GetAmount()){
            users[SenderIndex].SetBalansas(users[SenderIndex].GetBalansas() - transaction.GetAmount());
            users[ReceiverIndex].SetBalansas(users[ReceiverIndex].GetBalansas() + transaction.GetAmount());
        }
        else{
            std::cout << "NEPAKANKAMAS BALANSAS... TRANSAKCIJA NEATLIKTA" << std::endl;
            break;
        }

        for(int i = 0; i < transactions.size(); i++){
            if(transactions[i].GetTransactionID() == transaction.GetTransactionID()){
                transactions.erase(transactions.begin() + i);
                break;
            }
        }
    }
}

void IsvestiBloka(int WinnerID, int BlockCount, Block* Block){

    std::vector<Transaction> BlockTransactions = Block->GetTransactions();

    std::string failo_pavadinimas = "Isvedimai/Blokas-" + std::to_string(BlockCount) + ".txt";

    std::cout << "Failo pavadinimas: " << failo_pavadinimas << std::endl;
    std::ofstream RF(failo_pavadinimas);
    if (!RF.is_open()) {
    std::cerr << "Failed to open file: " << failo_pavadinimas << std::endl;
    return; // Or handle the error appropriately
}

    RF << "BLOCK: " << BlockCount << std::endl;
    RF << "WinnerID: " << WinnerID << std::endl;
    RF << std::string(50, '-') << std::endl;

    RF << "BLOCK HASH: " << Block->GetMasterHash() << std::endl;
    RF << "PREVIOUS HASH: " << Block->GetPreviousHash() << std::endl;
    RF << "ISKASIMO LAIKAS: " << Block->GetTimeStamp();
    RF << "TRANSAKCIJU KIEKIS: " << BlockTransactions.size() << std::endl;
    RF << "DIFFICULTY: " << Block->GetDifficulty() << std::endl;
    RF << "MERKLE ROOT HASH: " << Block->GetMerkleHash() << std::endl;
    RF << "VERSION: " << Block->GetVersion() << std::endl;
    RF << "NONCE: " << Block->GetNonce() << std::endl;

    RF << std::string(50, '-') << std::endl;
    RF << "BLOKO TRANSAKCIJOS: " << std::endl << std::endl;

    for(Transaction transaction : BlockTransactions){
        RF << "ID: " << transaction.GetTransactionID() << std::endl;
        RF << "Siuntejas: " << transaction.GetSender() << std::endl;
        RF << "Gavejas: " << transaction.GetReceiver() << std::endl;
        RF << "Suma: " << transaction.GetAmount() << std::endl;
        RF << std::endl;
    }
}
