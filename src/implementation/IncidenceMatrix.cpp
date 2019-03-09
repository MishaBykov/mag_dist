#include <utility>

#include <utility>

#include <utility>

//
// Created by misha on 11.10.18.
//

#include <utility>
#include <memory>
#include <iostream>

#include <IncidenceMatrix.h>

void IncidenceMatrix::updateCountColumn(unsigned long new_row) {
    if(new_row >= max_row) {
        if (new_row > max_row) {
            max_row = new_row;
        } else {
            max_row = matrix[0];
            for (auto &i : matrix)
                max_row = std::max(max_row, i);
            new_row = max_row;
        }
        for (count_column = 0; new_row != 0; new_row >>= 1, count_column++);
    }
}

unsigned long IncidenceMatrix::stringToRow(std::string row) {
    return std::stoull(row, nullptr, 2);
}

std::vector<bool> IncidenceMatrix::stringToColumn(std::string row) {
    std::vector<bool> result(row.size());
    for (int i = 0; i < row.size(); ++i) {
        result[i] = row[i] - '0';
    }
    return result;
}

void IncidenceMatrix::appendRow(unsigned long new_row) {
    updateCountColumn(new_row);
    matrix.push_back(new_row);
}

void IncidenceMatrix::appendRow(std::string new_str_row) {
    unsigned long new_row = stringToRow(std::move(new_str_row));
    appendRow(new_row);
}

unsigned long IncidenceMatrix::getRow(unsigned int index) {
    if(matrix.size() > index)
        return matrix[index];
    return 0;
}

unsigned long IncidenceMatrix::getCountRow() {
    return matrix.size();
}

unsigned long IncidenceMatrix::getCountColumn() {
    return count_column;
}

void IncidenceMatrix::appendColumn(std::vector<bool> new_column) {
    count_column++;
    for(int i = 0; i < matrix.size(); ++i) {
        matrix[i] <<= 1;
        matrix[i] += new_column[i];
    }
}

void IncidenceMatrix::appendColumn(std::string new_str_column) {
    appendColumn(stringToColumn(std::move(new_str_column)));
}

void IncidenceMatrix::removeColumn(unsigned long index) {
    auto right = (1 << index) - 1, left = ((1 << count_column) - 1) - ((1 << (index + 1)) - 1);
    count_column--;
    for(auto &i : matrix){
        i = ((left & i) >> 1) + (right & i);
    }
}

void IncidenceMatrix::printToStream(std::ostream &ostream) {
    for (unsigned long row : matrix) {
        for (int j = 0; j < count_column; j++){
            ostream << (row & 1);
            row >>= 1;
        }
        ostream << std::endl;
    }
    ostream << std::endl;
}

std::vector<bool> IncidenceMatrix::getColumn(unsigned long index) {
    std::vector<bool> result;
    unsigned long bit = static_cast<unsigned long>(1) << index;
    result.reserve(matrix.size());
    for (unsigned long i : matrix) {
        result.push_back(bool(i & bit));
    }
    return result;
}

void IncidenceMatrix::removeRow(unsigned long index) {
    matrix.erase(matrix.begin() + index);
}

std::vector<unsigned long> IncidenceMatrix::sumRow() {
    std::vector<unsigned long> result(getCountRow());
    for (int i = 0; i <matrix.size(); ++i) {
        for (unsigned long m = matrix[i]; m != 0; m >>= 1) {
            if (m & 1)
                result[i]++;
        }
    }
    return result;
}

std::vector<unsigned long> IncidenceMatrix::sumColumn() {
    std::vector<unsigned long> result(getCountColumn());
    for (unsigned long m : matrix) {
        for (int i = 0; m != 0; i++, m >>= 1) {
            if (m & 1)
                result[i]++;
        }
    }
    return result;
}

void IncidenceMatrix::setColumn(unsigned long index, std::vector<bool> new_value) {
    unsigned long bit = 1;
    bit <<= index;
    for (int i = 0; i < matrix.size(); ++i) {
        if (new_value[i] != (bit && matrix[i])){
            if (bit && matrix[i]){
                matrix[i] -= bit;
            }
            if (new_value[i]){
                matrix[i] += bit;
            }
        }

    }
}

void IncidenceMatrix::setColumn(unsigned long index, std::string new_value) {
    setColumn(index, stringToColumn(std::move(new_value)));
}

void IncidenceMatrix::setRow(unsigned int index, unsigned long new_value) {
    matrix[index] = new_value;
}

void IncidenceMatrix::setRow(unsigned int index, std::string new_value) {
    matrix[index] = stringToRow(std::move(new_value));
}

void IncidenceMatrix::readFromFile(std::istream &istream) {
    std::string buff;

    while(getline(istream, buff)) {
        if(!buff.empty()) {
            try {
                appendRow(buff);
            }
            catch (const std::invalid_argument &e) {
                std::cout << "Некоректный файл" << std::endl
                          << "(" << e.what() << ") строка: " << buff << std::endl;
                break;
            }
        }
    }
}
