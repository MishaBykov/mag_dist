#include <utility>

//
// Created by misha on 11.10.18.
//

#include <memory>
#include <iostream>
#include <fstream>

#include <incidence_matrix.hpp>


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
    return std::stoi(row, nullptr, 2);
}

void IncidenceMatrix::setRow(int index, std::string value) {
    matrix[index] = stringToRow(std::move(value));
}

std::vector<IncidenceMatrix> IncidenceMatrix::readFromFile(const std::string& file_name) {
    std::vector<IncidenceMatrix> result;
    std::string buff; // буфер промежуточного хранения считываемого из файла текста
    std::ifstream file_in(file_name); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)

    if(!file_in.is_open()) {
        std::cout << "Файл не может быть открыт!" << std::endl; // сообщить об этом
        return result;
    }

    result.emplace_back();
    while(std::getline(file_in, buff)) {
        if(buff.empty())
        {
            result.emplace_back();
            continue;
        }
        try {
            result.back().appendRow(buff);
        }catch (...)
        {
            std::cout << "Некоректный файл" << std::endl;
            result.pop_back();
            break;
        }
    }

    file_in.close(); // закрываем файл

    return result;
}

// todo перейти на bitset
void IncidenceMatrix::printToFile(const std::string &file_name) {
    std::ofstream file_out(file_name); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)

    if(!file_out.is_open()) {
        std::cout << "Файл не может быть открыт!" << std::endl; // сообщить об этом
        return;
    }


    file_out.close();
}

void IncidenceMatrix::printToFile(std::vector<IncidenceMatrix> incidenceMatrix, const std::string &file_name) {

}
