#include <utility>

//
// Created by misha on 11.10.18.
//

#include <iostream>
#include <fstream>
#include "incidence_matrix.hpp"


void IncidenceMatrix::appendRow(int new_row) {
    matrix.push_back( new_row );
}

void IncidenceMatrix::appendRow(std::string new_row) {
    matrix.push_back( stringToRow(std::move(new_row)) );
}

int IncidenceMatrix::getRow(int index) {
    return matrix[index];
}

void IncidenceMatrix::setRow(int value, int index) {
    matrix[index] = value;
}

int IncidenceMatrix::stringToRow(std::string row) {
    int result = 0;
    for (unsigned long i = 0; i < row.size(); i++) {
        if (row[i] == '1') {
            int a = 1;
            a <<= row.size() - 1 - i;
            result += a;
        }
    }
    return result;
}

void IncidenceMatrix::setRow(int index, std::string value) {
    matrix[index] = stringToRow(std::move(value));
}

void IncidenceMatrix::readFromFile(std::string file_name) {
    std::string buff; // буфер промежуточного хранения считываемого из файла текста
    std::ifstream fin(file_name); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)

    if (!fin.is_open()) {
        std::cout << "Файл не может быть открыт!" << std::endl; // сообщить об этом
        return;
    }

    std::getline(fin, buff); // считали строку из файла
    fin.close(); // закрываем файл
    std::cout << buff << std::endl; // напечатали эту строку

}
