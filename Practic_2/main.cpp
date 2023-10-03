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
#include <string>
#include <map>

using namespace std;

const char fileName[] = "medical_records.dat";

struct MedicalRecord {
    int cardNumber;
    int chronicDiseaseCode;
    string treatingDoctorLastName;
};

MedicalRecord generateRecord() {
    MedicalRecord record;
    record.cardNumber = rand() % 1000000; // Генерируем шестизначный номер карточки
    record.chronicDiseaseCode = rand() % 100; // Генерируем код хронического заболевания (пусть будет от 0 до 99)
    record.treatingDoctorLastName = "Doctor" + to_string(rand() % 10); // Генерируем фамилию лечащего врача
    return record;
}

void createBinaryFile(const char* fileName, int numRecords) {
    ofstream file(fileName, ios::binary | ios::out);
    if (!file) {
        cerr << "Ошибка при создании файла." << endl;
        return;
    }

    srand(time(nullptr));

    for (int i = 0; i < numRecords; i++) {
        MedicalRecord record = generateRecord();
        record.cardNumber = i;
        file.write(reinterpret_cast<const char*>(&record), sizeof(MedicalRecord));
    }

    file.close();
}

bool searchBinaryFile(const char* fileName, int key, MedicalRecord& foundRecord) {
    ifstream file(fileName, ios::binary | ios::in);
    if (!file) {
        cerr << "Ошибка при открытии файла." << endl;
        return false;
    }

    while (file.read(reinterpret_cast<char*>(&foundRecord), sizeof(MedicalRecord))) {
        if (foundRecord.cardNumber == key) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool interpolationSearchByKey(const string& filename, int key, MedicalRecord& result) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return false;
    }
    
    file.seekg(0, ios::end);
    long long int fileSize = file.tellg();
    file.seekg(0, ios::beg);
    
    int recordSize = sizeof(MedicalRecord);
    long long int numRecords = fileSize / recordSize;
    
    long long int left = 0;
    long long int right = numRecords - 1;
    
    while (left <= right) {
        long long int mid = left + ((key - 0) * (right - left)) / (9999 - 0);
        
        if (mid < 0 || mid >= numRecords) {
            cerr << "Ключ находится за пределами диапазона записей." << endl;
            file.close();
            return false;
        }
        
        file.seekg(mid * recordSize, ios::beg);
        MedicalRecord record;
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

int main() {
    createBinaryFile(fileName, 1000);
    cout << "Запись в файл прошла успешно!" << endl;

    MedicalRecord result;
    int searchKey = 998;
  
    clock_t linearStart = clock();
    bool resBinaryFile = searchBinaryFile(fileName, searchKey, result);
    clock_t linearEnd = clock();

    if (resBinaryFile) {
        cout << "Найдена запись по номеру карточки " << searchKey << ": " << result.treatingDoctorLastName << endl;
    }
    else {
        cout << "Запись с номером карточки " << searchKey << " не найдена при линейном поиске." << endl;
    }

    cout << "Время выполнения линейного поиска: " << double(linearEnd - linearStart) / CLOCKS_PER_SEC << " секунд." << endl;

  
    clock_t interpolationStart = clock();
    bool resInterpolationFile = interpolationSearchByKey(fileName, searchKey, result);
    clock_t interpolationEnd = clock();

    if (resInterpolationFile) {
        cout << "Найдена запись по номеру карточки " << searchKey << ": " << result.treatingDoctorLastName << endl;
    }
    else {
        cout << "Запись с номером карточки " << searchKey << " не найдена при интерполяционном поиске." << endl;
    }

    cout << "Время выполнения интерполяционного поиска: " << double(interpolationEnd - interpolationStart) / CLOCKS_PER_SEC << " секунд." << endl;

    return 0;
}
