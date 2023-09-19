//
//  main.cpp
//  Practic_1
//
//  Created by Vlad V on 07.09.2023.
//

#include <iostream>
#include <fstream>

using namespace std;

void set1And15And17BitTo1() {
    int hexValue = 0x3A4;
    
    cout << "Исходное значение: 0x" << hex << hexValue << endl;
    cout << "Исходное значение в двоичной системе: " << bitset<32>(hexValue) << endl;
    
    int bit17 = 1 << 17;
    int bit15 = 1 << 15;
    int bit1 = 1 << 1;
    
    hexValue |= bit17;
    hexValue |= bit15;
    hexValue |= bit1;
    
    cout << "Результат: 0x" << hex << hexValue << endl;
    cout << "Результат в двоичной системе: " << bitset<32>(hexValue) << endl;
}

void set3BitFrom5To0() {
    int inputValue;
    
    cout << "Введите целое число: ";
    cin >> inputValue;
    
    cout << "Исходное значение: " << bitset<32>(inputValue) << endl;
    
    int mask = ~(7 << 2);
    
    int resultValue = inputValue & mask;
    
    cout << "Результат: " << bitset<32>(resultValue) << endl;
    cout << "Результат: " << resultValue << endl;
}

void multiplyBy64() {
    int variable;
    
    cout << "Введите значение переменной: ";
    cin >> variable;
    
    variable = variable << 6;
    
    cout << "Результат умножения: " << variable << endl;
}

void devideBy64() {
    int variable;
    
    cout << "Введите значение переменной: ";
    cin >> variable;
    
    variable = variable >> 6;
    
    cout << "Результат умножения: " << variable << endl;
}

void nBitTo0() {
    int variable;
    
    cout << "Введите значение переменной: ";
    cin >> variable;
    
    cout << "Исходное значение в двоичной системе: " << bitset<32>(variable) << endl;
    
    int n;
    cout << "Введите номер бита для обнуления: ";
    cin >> n;
    
    int mask = ~(1 << n);
    
    variable = variable & mask;
    
    cout << "Результат обнуления " << n << "-го бита: " << variable << endl;
    cout << "Результат в двоичной системе: " << bitset<32>(variable) << endl;
}

void bitSort(vector<int>& nums) {
    const int maxNum = 7;
    vector<unsigned char> bitArray(maxNum + 1, 0);

    for (int num : nums) {
        bitArray[num] = 1;
    }

    nums.clear();
    for (int i = 0; i <= maxNum; ++i) {
        if (bitArray[i] == 1) {
            nums.push_back(i);
        }
    }
}

void bitSortFile(const string& inputFile, const string& outputFile) {
    const int maxNum = 10000000;
    vector<unsigned char> bitArray(maxNum + 1, 0);
    
    ifstream input(inputFile);
    if (!input.is_open()) {
        cerr << "Ошибка открытия входного файла." << endl;
        return;
    }
    
    int num;
    while (input >> num) {
        bitArray[num] = 1;
    }
    input.close();
    
    ofstream output(outputFile);
    if (!output.is_open()) {
        cerr << "Ошибка открытия выходного файла." << endl;
        return;
    }
    
    for (int i = 0; i <= maxNum; ++i) {
        if (bitArray[i] == 1) {
            output << i << " ";
        }
    }
    output.close();
}

int main(int argc, const char * argv[]) {
    int choice;
    do {
        cout << endl;
        cout << "Выберите задачу:" << endl;
        cout << "1. Первая задача" << endl;
        cout << "2. Вторая задача" << endl;
        cout << "3. Третья задача" << endl;
        cout << "4. Четвертая задача" << endl;
        cout << "5. Пятая задача" << endl;
        cout << "6. Сортировка битовым массивом" << endl;
        cout << "7. Сортировка файла битовым массивом" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер задачи (0-7): ";
        cin >> choice;

        switch (choice) {
            case 1:
                set1And15And17BitTo1();
                break;
            case 2:
                set3BitFrom5To0();
                break;
            case 3:
                multiplyBy64();
                break;
            case 4:
                devideBy64();
                break;
            case 5:
                nBitTo0();
                break;
            case 6: {
                vector<int> nums = {1, 0, 5, 7, 2, 4};
                bitSort(nums);
                cout << "Отсортированная последовательность: ";
                for (int num : nums) {
                    cout << num << " ";
                }
                cout << endl;
                break;
            }
            case 7: {
                string inputFile = "/Users/vladv/XCode Projects/SIAOD/Practic_1/input.txt";
                string outputFile = "/Users/vladv/XCode Projects/SIAOD/Practic_1/output.txt";
                bitSortFile(inputFile, outputFile);
                cout << "Сортировка завершена. Результат записан в " << outputFile << endl;
                break;
            }
            case 0:
                cout << "Программа завершена." << endl;
                break;
            default:
                cout << "Некорректный выбор. Попробуйте снова." << endl;
                break;
        }
        
    } while (choice != 0);

    return 0;
}
