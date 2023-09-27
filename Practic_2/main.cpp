//
//  main.cpp
//  Practic_2
//
//  Created by Vlad V on 20.09.2023.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

// Структура записи
struct PatientRecord {
    int cardNumber;             // Номер карточки
    int chronicDiseaseCode;     // Код хронического заболевания
    string doctorLastName;      // Фамилия лечащего врача
    
    PatientRecord() {}
    PatientRecord(int card, int code, const string& lastName) : cardNumber(card), chronicDiseaseCode(code), doctorLastName(lastName) {}
};

// Функция для создания двоичного файла с записями
void createBinaryFile(const string& filename, int numRecords) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return;
    }
    
    srand(static_cast<unsigned>(time(nullptr)));
    vector<int> usedCardNumbers;
    
    for (int i = 0; i < numRecords; ++i) {
        int cardNumber;
        do {
            cardNumber = i; //rand() % 10000; // Генерация случайных номеров карточек
        } while (find(usedCardNumbers.begin(), usedCardNumbers.end(), cardNumber) != usedCardNumbers.end());
        
        usedCardNumbers.push_back(cardNumber);
        int chronicDiseaseCode = rand() % 100;
        string doctorLastName = "Doctor_" + to_string(i);
        
        PatientRecord record(cardNumber, chronicDiseaseCode, doctorLastName);
        
        file.write(reinterpret_cast<const char*>(&record), sizeof(record));
    }
    
    file.close();
}

// Функция для линейного поиска записи по ключу (номеру карточки)
bool linearSearchByKey(const string& filename, int key, PatientRecord& result) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return false;
    }
    
    PatientRecord record;
    while (file.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        if (record.cardNumber == key) {
            result = record;
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

// Функция для интерполяционного поиска записи по ключу (номеру карточки)
bool interpolationSearchByKey(const string& filename, int key, PatientRecord& result) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return false;
    }
    
    file.seekg(0, ios::end);
    long long int fileSize = file.tellg();
    file.seekg(0, ios::beg);
    
    int recordSize = sizeof(PatientRecord);
    long long int numRecords = fileSize / recordSize;
    
    if (key < 0 || key > 9999) {
        cerr << "Ключ находится за пределами диапазона." << endl;
        file.close();
        return false;
    }
    
    long long int left = 0;
    long long int right = numRecords - 1;
    
    while (left <= right) {
        if (key < 0 || key > 9999) {
            cerr << "Ключ находится за пределами диапазона." << endl;
            file.close();
            return false;
        }
        
        long long int mid = left + ((key - 0) * (right - left)) / (9999 - 0);
        
        if (mid < 0 || mid >= numRecords) {
            cerr << "Ключ находится за пределами диапазона записей." << endl;
            file.close();
            return false;
        }
        
        file.seekg(mid * recordSize, ios::beg);
        PatientRecord record;
        file.read(reinterpret_cast<char*>(&record), sizeof(record));
        
        if (record.cardNumber == key) {
            result = record;
            file.close();
            return true;
        } else if (record.cardNumber < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    file.close();
    cerr << "Запись не найдена." << endl;
    return false;
}

int main(int argc, const char * argv[]) {
    const string filename = "/Users/vladv/XCode Projects/SIAOD/Practic_2/patient_records.bin";
    
    // Создаем двоичный файл с записями (замените 100 на нужное количество записей)
    createBinaryFile(filename, 100);
    
    int key;
    cout << "Введите номер карточки для поиска: ";
    cin >> key;
    
    PatientRecord result;
    
    // Выполняем линейный поиск
    if (linearSearchByKey(filename, key, result)) {
        cout << "Запись найдена: " << result.cardNumber << " " << result.chronicDiseaseCode << " " << result.doctorLastName << endl;
    } else {
        cout << "Запись не найдена." << endl;
    }
    
    // Выполняем интерполяционный поиск
    if (interpolationSearchByKey(filename, key, result)) {
        cout << "Запись найдена: " << result.cardNumber << " " << result.chronicDiseaseCode << " " << result.doctorLastName << endl;
    } else {
        cout << "Запись не найдена." << endl;
    }
    
    return 0;
}
