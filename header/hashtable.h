#include <iostream>
#include <string>
#include <vector>
using namespace std;

class StockData {
public:
    StockData();
    StockData(string date, double open, double high, double low, double close, double adjClose, double volume); // Wenn Stock importiert wird
    string date;
    double open;
    double high;
    double low;
    double close;
    double adjClose;
    double volume;
};

class Stock {
public:
    Stock(string name, string wkn, string kuerzel, vector<StockData> stocks);
    Stock(string name, string wkn, string kuerzel);
    string name;
    string wkn;
    string kuerzel;
    vector<StockData> stocks;
};

class HashTable {
public:
    int HashFunction(string name);
    void insert(Stock stock);
    void search(HashTable& hashTable);
    void import(HashTable& hashTable);
    void remove(HashTable& hashTable);
    void plot(HashTable& hashTable);
    void add(HashTable& hashTable);
    void save(HashTable& hashTable);
    void load(HashTable& hashTable);
    Stock getStock(string name);
    Stock getStockIndex(int index);
    vector<Stock> Table[2003];
};