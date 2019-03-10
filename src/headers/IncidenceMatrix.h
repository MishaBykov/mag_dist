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
    static std::vector<bool> stringToColumn(std::string row);

public:
    IncidenceMatrix() = default;
    ~IncidenceMatrix() = default;

    void readFromFile(std::istream& istream);

    unsigned long getCountColumn();
    unsigned long getCountRow();

    unsigned long size();

    void appendRow( unsigned long new_row );
    void appendRow( std::string new_row );
    void removeRow(unsigned long index);
    unsigned long getRow(unsigned int index);
    void setRow(unsigned int index, unsigned long new_value);
    void setRow(unsigned int index, std::string new_value);
    std::vector<unsigned long> sumRow();

    void appendColumn( std::vector<bool> new_column );
    void appendColumn( std::string new_column );
    void removeColumn(unsigned long index);
    std::vector<bool> getColumn(unsigned long index);
    void setColumn(unsigned long index, std::vector<bool> new_value);
    void setColumn(unsigned long index, std::string new_value);
    std::vector<unsigned long> sumColumns();

    void printToStream(std::ostream &ostream);

};


#endif //MAG_DIST_INCIDENCE_MATRIX_H
