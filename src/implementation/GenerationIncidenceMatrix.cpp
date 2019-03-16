//
// Created by misha on 11.03.19.
//

#include <string>

#include <GenerationIncidenceMatrix.h>
#include <iostream>

GenerationIncidenceMatrix::GenerationIncidenceMatrix
(IncidenceMatrix base, unsigned int max_row, unsigned int  max_column)
        : base(base), max_row(max_row), max_column(max_column)
{
    bits.resize(max_row * max_column - base.size());
}

GenerationIncidenceMatrix::~GenerationIncidenceMatrix() {
    bits.clear();
}

bool GenerationIncidenceMatrix::next() {
    unsigned int i;
    for (i = 0; bits.size() > i && bits[i] != 0; ++i) {
        bits[i] = false;
    }
    if (i == bits.size())
        return false;
    bits[i] = true;

    i = 0;
    result = base;

    for (int j = 0; j < max_column - base.getCountColumn(); ++j, i += base.getCountRow()) {
        result.appendColumn(std::vector<bool>(bits.begin() + i, bits.begin() + i + base.getCountRow() ));
    }

    for (int j = 0; j < max_row - base.getCountRow(); ++j, i += max_column ) {
        std::string row;
        for (int k = i; k <= i + max_row; ++k) {
            row.push_back(bits[k] ? '1' : '0');
        }
        result.appendRow(row);
    }

    return true;
}

IncidenceMatrix GenerationIncidenceMatrix::getResult() {
    return result;
}
