#include <utility>

//
// Created by misha on 11.10.18.
//
#include <utility>
#include <memory>
#include <iostream>
#include <fstream>

#include <incidence_matrix.hpp>


void IncidenceMatrix::appendRow(unsigned long int &&new_row) {
    updateCountColumn(new_row);
    matrix.push_back(new_row);
}

void IncidenceMatrix::appendRow(std::string new_str_row) {
    unsigned long int new_row = stringToRow(std::move(new_str_row));
    updateCountColumn(new_row);
    matrix.push_back(new_row);
}

unsigned long IncidenceMatrix::getRow(unsigned int index) {
    if(matrix.size() > index)
        return matrix[index];
    return 0;
}

void IncidenceMatrix::setRow(unsigned long index, unsigned long int new_row) {
    updateCountColumn(new_row);
    if(matrix.size() > index) {
        matrix[index] = new_row;
    }
}

unsigned long IncidenceMatrix::stringToRow(std::string row) {
    return std::stoull(row, nullptr, 2);
}

void IncidenceMatrix::setRow(unsigned long index, std::string new_str_row) {
    unsigned long new_row = stringToRow(std::move(new_str_row));
    setRow(index, new_row);
}

std::vector<IncidenceMatrix> IncidenceMatrix::readFromFile(const std::string& file_name) {
    std::vector<IncidenceMatrix> result;
    std::string buff; // буфер промежуточного хранения считываемого из файла текста
    std::ifstream file_in(file_name);

    if(!file_in.is_open()) {
        std::cout << "Файл не может быть открыт!" << std::endl;
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

void IncidenceMatrix::printToFile(std::ofstream& file_out) {
    for (unsigned long row : matrix) {
        for (int j = 0; j < count_column; j++){
            file_out << (row & 1);
            row >>= 1;
        }
        file_out << std::endl;
    }
    file_out << std::endl;
}

void IncidenceMatrix::printToFile(std::vector<IncidenceMatrix> vecrtorIncidenceMatrix, const std::string &file_name) {
    std::ofstream file_out(file_name);

    if(!file_out.is_open()) {
        std::cout << "Файл(" << file_name << ") не может быть открыт!" << std::endl;
        return;
    }

    for (auto &i : vecrtorIncidenceMatrix) {
        i.printToFile(file_out);
    }

    file_out.close();
}

void IncidenceMatrix::updateCountColumn(unsigned long int new_row) {
    auto copy_row = new_row;
    unsigned int count_vertex = 0;
    for(; copy_row != 0; copy_row >>= 1, count_vertex++);
    if( this->count_column < count_vertex)
        this->count_column = count_vertex;
}

unsigned long IncidenceMatrix::getCountRow() {
    return matrix.size();
}

unsigned int IncidenceMatrix::getCountColumn() {
    return count_column;
}
