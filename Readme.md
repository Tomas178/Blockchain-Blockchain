# Decentralizuotas Blockchain'as



## Struktūra
    * User klasė – skirta saugoti duomenys apie vartotoją: vardą, unikalų PublicKey ir turima balansą.
    * Transaction klasė - skirta saugoti duomenys apie transakciją: unikalų TransactionID, Siuntejo PublicKey, gavėjo PublicKey ir siunčiamą sumą.
    * Block klasė - skirta saugoti duomenys apie bloką: prieš tai buvusio bloko hash'ą ``PreviousHash``, Rodyklę į prieš tai buvusį bloką ``PreviousBlockPointer``, pačio bloko hash'ą ``MasterHash``, laiko žymą kada buvo iškastas blokas ``TimeStamp``, Versiją ``Version``, Merkle hash'ą ``MerkleHash``, ``Nonce``, ``Difficulty`` ir visas bloko transakcijas ``Transactions``.
    * Hash.cpp – naudojamas hash'as iš 1 laboratorinio darbo
    * Generavimas.cpp – visos papildomos funkcijos, kurios naudojamos programoje, tokios kaip vartojojų generavimas, transakcijų generavimas, blokų kasimas ir t.t.
    * Programoje yra naudojamas gerosios OOP praktikos (enkapsuliavimas, konstruktoriai ir RAII idiomas).

## Funkcija **void GenerateUsers(int kiekis, std::vector<User>& users)**
    * Sugeneruoja tiek vartotojų kiek yra jai pateikiama su kintamuoju ``kiekis``. Pagal užduoties aprašymą yra generuojama 1000 tinklo vartotojų.

## Funkcija **std::vector<Transaction> GenerateTransactions(int kiekis, std::vector<User>& users)**
    * Sugeneruoja tiek transakcijų kiek yra jai pateikiama su kintamuoju ``kiekis``. Pagal užduoties aprašymą yra generuojama 10000 transakcijų tinkle.
    * Gražina ``kiekis`` dydžio vektorių sudarytą iš transakcijų.

## Funkcija **std::vector<std::vector<Transaction>> GenerateCandidates(std::vector<Transaction>& transactions, int BlockSize)**
    * Iš transakcijų vektoriaus kiekvienam generuojamam kandidatui yra priskiriama ``BlockSize`` transakcijų. Pagal užduoties aprašą yra priskiriama po 100 transakcijų.
    * Iš viso yra sukūriami 5 kandidatai bloko kasimams.
    * Gražina kandidatų vektorių, kuris yra sudarytas iš priskirtų transakcijų vektoriaus.

## Funkcija **Block MineBlock(int& WinnerID, std::string PreviousHash, Block* PreviousBlockPointer, std::string Version, int Difficulty, std::vector<std::vector<Transaction>> Kandidatu_sarasas)**
    * Priskiriamas Max_Bandymų kiekis = 100000. Jeigu visiems kandidatams nepavyksta atrasti tinkamo hash'o Max_Bandymai kiekis padvigubeja
    * Yra padarytas paralelinis kasimas su OpenMp API.
    * Funkcija grąžina informaciją apie iškastą bloką.

## Funkcija **std::string create_merkle(std::vector<Transaction> transactions)**
    * Paimta Libbitcoin bibliotekos create_merkle implementacija.

## Funkcija **void AtliktiTransakcijas(std::vector<Transaction>& transactions, std::vector<Transaction> BlockTransactions, std::vector<User>& users)**
    * Jeigu transakcijoje nurodyti gavėjo ir siuntėjo PublicKey nėra randami tarp visų tinklo vartotojų transakcija yra atmetama.
    * Jeigu transakcijoje nurodytas siuntėjo balansas yra mažesnis nei transakcijos suma, tai transakcija yra atmetama.
    * Jeigu transakcijos duomenų maišos reikšmė nesutampa su tranksacijos ``TransactionID``, tai transakcija yra atmetama.
    * Jeigu viskas okey, tai transakcija yra atliekama.
