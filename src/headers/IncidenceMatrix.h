//
// Created by misha on 11.10.18.
//

#ifndef MAG_DIST_INCIDENCE_MATRIX_H
#define MAG_DIST_INCIDENCE_MATRIX_H


#include <vector>
#include <fstream>
#include <string>

class IncidenceMatrix {


    unsigned long max_row = 0;
    unsigned long count_column = 0;

    std::vector<unsigned long> matrix;

    void updateCountColumn(unsigned long new_row);
    static unsigned long stringToRow(std::string row);

public:
    IncidenceMatrix() = default;
    ~IncidenceMatrix() = default;

    unsigned long getCountColumn();
    unsigned long getCountRow();

    void appendRow( unsigned long new_row );
    void appendRow( std::string new_row );
    unsigned long getRow(unsigned int index);

    void appendColumn( std::vector<bool> &new_column );
    void appendColumn( std::string new_column );
    void removeColumn(unsigned long index);

    void printToStream(std::ostream &ostream);

};


#endif //MAG_DIST_INCIDENCE_MATRIX_H
