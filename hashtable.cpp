#include <iostream>
#include <string> // Strings
#include <vector> // Vektoren
#include <fstream> // File-Input
#include <sstream> // File-Input
#include <cmath> // pow
#include <algorithm> // für Speicherfreigabe
#include <limits>   // Berechnung der Grafik
#include <iomanip> // 2 Nachkomma Stellen
#include "header/hashtable.h"
using namespace std;

StockData::StockData() {
    date = "";
    open = 0.0;
    high = 0.0;
    low = 0.0;
    close = 0.0;
    volume = 0.0;
    adjClose = 0.0;
}

StockData::StockData(string date, double open, double high, double low, double close, double adjClose, double volume) {
    this->date = date;
    this->open = open;
    this->high = high;
    this->low = low;
    this->close = close;
    this->volume = volume;
    this->adjClose = adjClose;
};

Stock::Stock(string name, string wkn, string kuerzel, vector<StockData> stocks) {
    this->name = name;
    this->wkn = wkn;
    this->kuerzel = kuerzel;
    this->stocks = stocks;
};

Stock::Stock(string name, string wkn, string kuerzel) {
    this->name = name;
    this->wkn = wkn;
    this->kuerzel = kuerzel;
};

void HashTable::insert(Stock stock) {

    int index = HashFunction(stock.name);
    Table[index].push_back(stock);
}

Stock HashTable::getStock(string name) {
    int index = HashFunction(name);
    for(int i = 0; i < Table[index].size(); i++) {
        if (Table[index][i].name == name) {
            return Table[index][i];
        }
    }
    return Stock("", "", "", {});
}

Stock HashTable::getStockIndex(int index) {
    for(int i = 0; i < Table[index].size(); i++) {
        string name = Table[index][i].name;
        if (Table[index][i].name == name) {
            return Table[index][i];
        }
    }
    return Stock("", "", "", {});
}

int HashTable::HashFunction(string name) {
    int temp = 0;
    for (int i = 0; i < name.length(); i++) {
        temp = (int)name[i] * pow(31, i - 1);
    }
    return temp % 2003;
}

void HashTable::add(HashTable& hashTable) {
    string fileName = "";
    string stockName = "";
    string shortName = "";
    string wkn = "";
    cout << "\nGebe den Namen der Aktie ein: ";
    cin >> stockName;
    cout << "\nGebe das Kürzel der Aktie ein: ";
    cin >> shortName;
    cout << "\nGebe das WKN der Aktie ein: ";
    cin >> wkn;

    Stock stock(stockName, shortName, wkn);
    hashTable.insert(stock);

    Stock result = hashTable.getStock(stockName);
    cout << result.name << " ";
    cout << result.wkn << " ";
    cout << result.kuerzel << " ";
}

void HashTable::remove(HashTable& hashTable) {
    string stockName = "";

    cout << "Welche Aktie willst du löschen? (Name) ";
    cin >> stockName;
    int del = HashFunction(stockName);
    for (int i = 0; i < Table[del].size();) {
        Table[del].erase(Table[del].begin() + i);
        cout << "Aktie " << stockName << " wurde gelöscht." << endl;
        return;
    }
    cout << "Aktie " << stockName << " nicht gefunden." << endl;
}

void HashTable::load(HashTable& hashTable) {
    string fileName = "";

    cout << "\nGeben Sie bitte den Namen der Datei ein: ";
    cin >> fileName;

    //ifstream file("/Users/leitner/Library/CloudStorage/OneDrive-FHTechnikumWien/SS2023/Algorithmen und Datenstruktur Labor/2-ALGOS-Aktien/stocks/" + shortName + ".csv");
    ifstream file("/Users/sinisapanic/Desktop/Aktien Beispiel - Leitner, Panic/cmake-build-debug/" + fileName + ".csv");
    if (!file.is_open()) {
        cout << "Fehler beim Dateiöffnen." << endl;
        return;
    }

    string line = "";
    string token = "";
    getline(file, line);

    while (getline(file, line)) {
        vector<StockData> stock_data;
        StockData data;
        stringstream ss(line);

        // Erster durchlauf um Vektor zu initialisieren
        getline(ss, token, ',');
        data.date = token;
        getline(ss, token, ',');
        data.open = stod(token);
        getline(ss, token, ',');
        data.high = stod(token);
        getline(ss, token, ',');
        data.low = stod(token);
        getline(ss, token, ',');
        data.close = stod(token);
        getline(ss, token, ',');
        data.adjClose = stod(token);
        getline(ss, token, ',');
        data.volume = stoi(token);
        stock_data.push_back(data);

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, token, ',');
            data.date = token;
            getline(ss, token, ',');
            data.open = stod(token);
            getline(ss, token, ',');
            data.high = stod(token);
            getline(ss, token, ',');
            data.low = stod(token);
            getline(ss, token, ',');
            data.close = stod(token);
            getline(ss, token, ',');
            data.adjClose = stod(token);
            getline(ss, token, ',');
            data.volume = stoi(token);
            stock_data.push_back(data);
        }

        int bestätigung = 0;
        cout << "\nDer Vorgang löscht Ihre derzeit gespeicherte Aktien. Trotzdem fortfahren? Ja [1] / Nein [0]: ";
        cin >> bestätigung;

        if(bestätigung == 1){
            string stockName = "";
            string shortName = "";
            string wkn = "";
            cout << "\nGebe den Namen der Aktie ein: ";
            cin >> stockName;
            cout << "\nGebe das Kürzel der Aktie ein: ";
            cin >> shortName;
            cout << "\nGebe das WKN der Aktie ein: ";
            cin >> wkn;

            int del = HashFunction(stockName);
            for (int i = 0; i < Table[del].size();) {
                Table[del].erase(Table[del].begin() + i);
            }

            Stock stock(stockName, shortName, wkn, stock_data);
            hashTable.insert(stock);

            Stock result = hashTable.getStock(stockName);
            cout << result.name << " ";
            cout << result.wkn << " ";
            cout << result.kuerzel << endl;
            cout << "Date " << "Open " << "High " << "Low " << "AdjClose " << "Volume" << endl;
            for (int i = 0; i < 30; i++) {
                cout << result.stocks[i].date << " ";
                cout << result.stocks[i].open << " ";
                cout << result.stocks[i].high << " ";
                cout << result.stocks[i].low << " ";
                cout << result.stocks[i].close << " ";
                cout << result.stocks[i].adjClose << " ";
                cout << fixed << setprecision(2) << result.stocks[i].volume << endl;
            }
            cout << "--------------------------------";
            cout << "Datei erfolgreich importiert.";
            cout << "--------------------------------" << endl;
        }
        else{
            cout << "--------------------------------";
            cout << "Vorgang abgebrochen.";
            cout << "--------------------------------" << endl;
        }
    }
}

void HashTable::save(HashTable& hashTable) {
    string fileName;

    cout << "Speichern als: ";
    cin >> fileName;

    ofstream outFile; //using ofstream to write into Files
    outFile.open(fileName + ".csv");

    if(!outFile.is_open()){
        cout << "Fehler beim Öffnen der Datai: " << fileName + ".csv" << endl;
    }

    for(int i = 0; i < 2003; i++){
        if( Table[i].size() != 0 ){
            Stock result = hashTable.getStockIndex(i);

            outFile << "Date" << ",";
            outFile << "Open" << ",";
            outFile << "High" << ",";
            outFile << "Low" << ",";
            outFile << "Close" << ",";
            outFile << "Adj Close" << ",";
            outFile << "Volume" << endl;

            for(int j = 0; j < 30; j++)
            {
                outFile << result.stocks[j].date << ",";
                outFile << result.stocks[j].open << ",";
                outFile << result.stocks[j].high << ",";
                outFile << result.stocks[j].low << ",";
                outFile << result.stocks[j].close << ",";
                outFile << result.stocks[j].adjClose << ",";
                outFile << fixed << setprecision(2) << result.stocks[j].volume << endl;

                cout << result.stocks[j].date << " ";
                cout << result.stocks[j].open << " ";
                cout << result.stocks[j].high << " ";
                cout << result.stocks[j].low << " ";
                cout << result.stocks[j].close << " ";
                cout << result.stocks[j].adjClose << " ";
                cout << fixed << setprecision(2) << result.stocks[j].volume << endl;
            }
        }
    }

    cout << "--------------------------------";
    cout << "Datei erfolgreich gespeichert!";
    cout << "--------------------------------" << endl;

    outFile.close();
}

void HashTable::import(HashTable& hashTable) {
    string fileName = "";
    string stockName = "";
    string shortName = "";
    string wkn = "";
    cout << "\nGebe den Namen der Aktie ein: ";
    cin >> stockName;
    cout << "\nGebe das Kürzel der Aktie ein: ";
    cin >> shortName;
    cout << "\nGebe das WKN der Aktie ein: ";
    cin >> wkn;

    //ifstream file("/Users/leitner/Library/CloudStorage/OneDrive-FHTechnikumWien/SS2023/Algorithmen und Datenstruktur Labor/2-ALGOS-Aktien/stocks/" + shortName + ".csv");
    ifstream file("/Users/sinisapanic/Desktop/Aktien Beispiel - Leitner, Panic/stocks/" + shortName + ".csv");
    if (!file.is_open()) {
        cout << "Fehler beim Dateiöffnen." << endl;
        return;
    }

    string line = "";
    string token = "";
    getline(file, line);

    while (getline(file, line)) {
        vector<StockData> stock_data;
        StockData data;
        stringstream ss(line);

        // Erster durchlauf um Vektor zu initialisieren
        getline(ss, token, ',');
        data.date = token;
        getline(ss, token, ',');
        data.open = stod(token);
        getline(ss, token, ',');
        data.high = stod(token);
        getline(ss, token, ',');
        data.low = stod(token);
        getline(ss, token, ',');
        data.close = stod(token);
        getline(ss, token, ',');
        data.adjClose = stod(token);
        getline(ss, token, ',');
        data.volume = stoi(token);
        stock_data.push_back(data);

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, token, ',');
            data.date = token;
            getline(ss, token, ',');
            data.open = stod(token);
            getline(ss, token, ',');
            data.high = stod(token);
            getline(ss, token, ',');
            data.low = stod(token);
            getline(ss, token, ',');
            data.close = stod(token);
            getline(ss, token, ',');
            data.adjClose = stod(token);
            getline(ss, token, ',');
            data.volume = stoi(token);
            stock_data.push_back(data);
        }

        int del = HashFunction(stockName);
        for (int i = 0; i < Table[del].size();) {
            Table[del].erase(Table[del].begin() + i);
        }

        Stock stock(stockName, shortName, wkn, stock_data);
        hashTable.insert(stock);

        Stock result = hashTable.getStock(stockName);
        cout << result.name << " ";
        cout << result.wkn << " ";
        cout << result.kuerzel << endl;
        cout << "Date " << "Open " << "High " << "Low " << "AdjClose " << "Volume" << endl;
        for (int i = 0; i < 30; i++) {
            cout << result.stocks[i].date << " ";
            cout << result.stocks[i].open << " ";
            cout << result.stocks[i].high << " ";
            cout << result.stocks[i].low << " ";
            cout << result.stocks[i].close << " ";
            cout << result.stocks[i].adjClose << " ";
            cout << fixed << setprecision(2) << result.stocks[i].volume << endl;
        }
    }
    cout << "--------------------------------";
    cout << "Aktie erfolgreich importiert.";
    cout << "--------------------------------" << endl;
}

//Set the char which has to be used in our chart. 
char getChar(int index, int currentPosition, int nextPosition = 0){
    int actualGraphPos = 10 - index;
    if(currentPosition == actualGraphPos){          //is it the same row?
        if(nextPosition > currentPosition)
            return '/';
        else if(nextPosition < currentPosition)
            return '\\';
        else if(nextPosition == currentPosition)
            return '-';
    }
    else if(currentPosition > actualGraphPos)
        return '.';
    else if(currentPosition <actualGraphPos)
        return ' ';

    return ' ';
}

//First we compute the difference from lowest to highest as we want to get only the relevant date for the chart.
//Than we iterate through all spots of the chart and set it with the char from the function getChar.
vector<vector<char>> ASCII(Stock& result){
    vector<vector<char>> asc;
    vector<int> position;

    float highest = numeric_limits<float>::min();
    float lowest = numeric_limits<float>::max();
    float dif;

    for(int i = 0; i < 10; i++){
        asc.push_back({'|'});
    }
    for(int i = 0; i < 30; i++){
        float current = result.stocks[i].close;
        highest = current > highest ? current : highest;
        lowest = current < lowest ? current : lowest;
    }
    dif = highest - lowest;
    for(int i = 29; i >=0; i--){
        position.push_back((int)((result.stocks[i].close - lowest) / dif * 10));
    }
    position.push_back(lowest);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 30; j++){
            asc.at(i).push_back(getChar(i, position.at(j), position.at(j + 1)));
        }
    }
    return asc;
}

//All Stock from the last 30 days in a chart.
void HashTable::plot(HashTable& hashTable) {
    string stockName = "";

    cout << "Für welche Aktie soll der Plot ausgegeben werden? (Name) ";
    cin >> stockName;
    Stock result = hashTable.getStock(stockName);

    if(result.name == ""){
        cout << "Aktie nicht gefunden" << endl;
    } else {
        cout << "\nDate\t\tOpen\tHigh\tLow\tClose\tAdjClose\tVolume\n";
        for (int i = 0; i < 30; i++) {
            cout << result.stocks[i].date << " ";
            cout << result.stocks[i].open << " ";
            cout << result.stocks[i].high << " ";
            cout << result.stocks[i].low << " ";
            cout << result.stocks[i].close << " ";
            cout << result.stocks[i].adjClose << " ";
            cout << fixed << setprecision(2) << result.stocks[i].volume << endl;
        }
        vector<vector<char>> asc = ASCII(result);

        for(int i = 0; i < 10; i++){
            cout << " ";
            for(int j = 0; j < 30; j++){
                cout << asc.at(i).at(j) << " ";
            }
            cout << "\n";
        }
        cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    }
}

void HashTable::search(HashTable& hashTable) {
    int i = 29;
    string stockName = "";

    cout << "Welche Aktie willst du suchen? (Name) ";
    cin >> stockName;
    Stock result = hashTable.getStock(stockName);

    if(result.name == "") {
        cout << "Aktie nicht gefunden" << endl;
    } else {
        cout << result.name << " ";
        cout << result.wkn << " ";
        cout << result.kuerzel << endl;
        cout << result.stocks[i].date << " ";
        cout << result.stocks[i].open << " ";
        cout << result.stocks[i].high << " ";
        cout << result.stocks[i].low << " ";
        cout << result.stocks[i].close << " ";
        cout << result.stocks[i].adjClose << " ";
        cout << fixed << setprecision(2) << result.stocks[i].volume << endl;
    }
}

int main() {
    HashTable hashTable;
    int input = 0;
    while(input != 8) {
        cout << "\n1. ADD: Aktie hinzufügen";
        cout << "\n2. DEL: Aktie löschen";
        cout << "\n3. IMPORT: Aktie importieren";
        cout << "\n4. SEARCH: Aktie suchen";
        cout << "\n5. PLOT: Grafik anzeigen";
        cout << "\n6. SAVE: Programm speichert die Hashtabelle in eine Datei ab";
        cout << "\n7. LOAD: Programm lädt die Hashtabelle aus einer Datei";
        cout << "\n8. QUIT: Programm beenden" << endl;

        cout << "\nGeben Sie die gewünschte Nummer ein: ";

        cin >> input;
        if(input == 1) {
            hashTable.add(hashTable);
        }
        else if(input == 2) {
            hashTable.remove(hashTable);
        }
        else if(input == 3) {
            hashTable.import(hashTable);
        }
        else if(input == 4) {
            hashTable.search(hashTable);
        }
        else if(input == 5){
            hashTable.plot(hashTable);
        }
        else if(input == 6){
            hashTable.save(hashTable);
        }
        else if(input == 7){
            hashTable.load(hashTable);
        }
        else if(input == 8) {
            return 0;
        }
        else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Keine gültige Eingabe!" << endl;
        }
    }
}