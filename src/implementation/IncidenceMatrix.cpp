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

void IncidenceMatrix::appendColumn(std::vector<bool> &new_column) {
    count_column++;
    for(int i = 0; i < matrix.size(); ++i) {
        matrix[i] <<= 1;
        matrix[i] += new_column[i];
    }
}

void IncidenceMatrix::appendColumn(std::string new_str_column) {
    std::vector<bool> new_column;
    new_column.reserve(new_str_column.size());
    for (auto &i : new_str_column) {
        new_column.push_back(bool(int(i - '0')));
    }
    appendColumn(new_column);
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
