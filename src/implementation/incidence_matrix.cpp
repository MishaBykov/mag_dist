#include <utility>

//
// Created by misha on 11.10.18.
//
#include <utility>
#include <memory>
#include <iostream>
#include <fstream>

#include <incidence_matrix.hpp>



IncidenceMatrix::IncidenceMatrix(int dimension) {
    this->dimension = dimension;
}

void IncidenceMatrix::appendRow(unsigned long int &&new_row) {
    updateCountVertex(new_row);
    matrix.push_back(new_row);
}

void IncidenceMatrix::appendRow(std::string new_str_row) {
    unsigned long int new_row = stringToRow(std::move(new_str_row));
    updateCountVertex(new_row);
    matrix.push_back(new_row);
}

unsigned long IncidenceMatrix::getRow(unsigned int index) {
    if(matrix.size() > index)
        return matrix[index];
    return 0;
}

void IncidenceMatrix::setRow(unsigned long index, unsigned long int new_row) {
    updateCountVertex(new_row);
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
        std::cout << "Файл(" << file_name << ") не может быть открыт!" << std::endl; // сообщить об этом
        return;
    }

    int max_bit = 0;
//    for(auto max_row = matrix[ind_row_max]; max_row != 0; max_row <<= 1, max_bit++);

    

    file_out.close();
}

void IncidenceMatrix::printToFile(std::vector<IncidenceMatrix> incidenceMatrix, const std::string &file_name) {

}

void IncidenceMatrix::updateCountVertex(unsigned long int new_row) {
    auto copy_row = new_row;
    unsigned int count_vertex = 0;
    for(; copy_row != 0; copy_row >>= 1, count_vertex++);
    if( this->count_vertex < count_vertex)
        this->count_vertex = count_vertex;
}
