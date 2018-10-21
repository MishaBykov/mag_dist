//
// Created by misha on 11.10.18.
//

#include <iostream>
#include "incidence_matrix.hpp"


void IncidenceMatrix::appendRow(int new_row) {
    matrix.push_back( new_row );
}

void IncidenceMatrix::appendRow(std::string new_row) {
    int result = 0;
    for (unsigned long i = 0; i < new_row.size(); i++) {
        if (new_row[i] == '1') {
            int a = 1;
            a <<= new_row.size() - 1 - i;
            result += a;
        }
    }
    matrix.push_back(result);
}
