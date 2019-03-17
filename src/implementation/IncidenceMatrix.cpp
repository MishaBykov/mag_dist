//
// Created by misha on 11.10.18.
//

#include <IncidenceMatrix.h>

#include <algorithm>
#include <iostream>

void IncidenceMatrix::updateCountColumn() {
    if (matrix.empty()){
        return;
    }
    unsigned long max_row = *std::max_element(matrix.begin(), matrix.end());
    for (count_column = 0; max_row != 0; max_row >>= 1, count_column++);
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
    matrix.push_back(new_row);
    updateCountColumn();
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
    if (getCountRow() < new_column.size()) {
        matrix.resize(new_column.size());
    }
    count_column++;
    for(int i = 0; i < matrix.size(); ++i) {
        matrix[i] <<= 1;
        matrix[i] += new_column[i];
    }
    updateCountColumn();
}

void IncidenceMatrix::appendColumn(std::string new_str_column) {
    appendColumn(stringToColumn(std::move(new_str_column)));
}

void IncidenceMatrix::removeColumn(unsigned int index) {
    auto right = (1 << index) - 1, left = ((1 << count_column) - 1) - ((1 << (index + 1)) - 1);
    count_column--;
    for(auto &i : matrix){
        i = ((left & i) >> 1) + (right & i);
    }
    updateCountColumn();
}

void IncidenceMatrix::printToStream(std::ostream &o_stream) {
    for (unsigned long row : matrix) {
        std::string buf;
        for (int j = 0; j < count_column; j++){
            buf.push_back(static_cast<char>((row & 1) + '0'));
            row >>= 1;
        }
        std::reverse(buf.begin(), buf.end());
        o_stream << buf << std::endl;
    }
    o_stream << std::endl;
}

std::vector<bool> IncidenceMatrix::getColumn(unsigned int index) {
    std::vector<bool> result;
    unsigned long bit = static_cast<unsigned long>(1) << index;
    result.reserve(matrix.size());
    for (unsigned long i : matrix) {
        result.push_back(bool(i & bit));
    }
    return result;
}

void IncidenceMatrix::removeRow(unsigned int index) {
    matrix.erase(matrix.begin() + index);
    updateCountColumn();
}

std::vector<unsigned long> IncidenceMatrix::sumRows() {
    std::vector<unsigned long> result(getCountRow());
    for (int i = 0; i < matrix.size(); ++i) {
        for (unsigned long m = matrix[i]; m != 0; m >>= 1) {
            if (m & 1)
                result[i]++;
        }
    }
    return result;
}

std::vector<unsigned long> IncidenceMatrix::sumColumns() {
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
    if (index >= getCountColumn()){
        std::cout << "[setColumn] "<< index << " за пределами" << std::endl;
        return;
    }
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
    updateCountColumn();
}

void IncidenceMatrix::setColumn(unsigned long index, std::string new_value) {
    setColumn(index, stringToColumn(std::move(new_value)));
}

void IncidenceMatrix::setRow(unsigned int index, unsigned long new_value) {
    if (index >= getCountRow()){
        std::cout << "[setRow] "<< index << " за пределами" << std::endl;
        return;
    }
    matrix[index] = new_value;
    updateCountColumn();
}

void IncidenceMatrix::setRow(unsigned int index, std::string new_value) {
    setRow(index, stringToRow(std::move(new_value)));
}

void IncidenceMatrix::readFromStream(std::istream &i_stream) {
    if (!i_stream.eof()) {
        std::string buff;
        std::getline(i_stream, buff);
        while (!buff.empty()) {
            try {
                appendRow(buff);
            }
            catch (const std::invalid_argument &e) {
                std::cout << "Некоректный файл" << std::endl
                          << "(" << e.what() << ") строка: " << buff << std::endl;
                break;
            }
            std::getline(i_stream, buff);
        }
    } else {
        std::cout << "Конец файла" << std::endl;
    }
}

unsigned long IncidenceMatrix::size() {
    return getCountColumn() * getCountRow();
}

void IncidenceMatrix::transpose() {
    std::vector<unsigned long> new_matrix;
    for (unsigned int i = 0; i < getCountColumn(); ++i) {
        new_matrix.push_back(stringToRow(columnToString(getColumn(i))));
    }
    matrix.clear();
    matrix = new_matrix;
}

std::string IncidenceMatrix::columnToString(const std::vector<bool>& column) {
    std::string result;

    for (auto &&i : column) {
        result.push_back(i ? '1' : '0');
    }

    return result;
}
