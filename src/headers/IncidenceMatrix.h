//
// Created by misha on 11.10.18.
//

#ifndef MAG_DIST_INCIDENCE_MATRIX_H
#define MAG_DIST_INCIDENCE_MATRIX_H


#include <vector>
#include <fstream>
#include <string>
#include <memory>

class IncidenceMatrix;
using IncidenceMatrixSPtr = std::shared_ptr<IncidenceMatrix>;

class IncidenceMatrix {

    unsigned int count_column = 0;
    std::vector<unsigned long> matrix;

    bool sorted = false;

    void updateCountColumn();

    static unsigned long stringToRow(const std::string& row);
    static std::vector<bool> stringToColumn(std::string row);
    static std::string columnToString(const std::vector<bool>& column);

public:
    IncidenceMatrix() = default;
    ~IncidenceMatrix() = default;

    unsigned int getCountColumn();
    unsigned int getCountRow();
    unsigned long size();
    void clear();
    void sort();
    void appendRow( unsigned long new_row );
    void appendRow( std::string& new_row );
    void removeRow(unsigned long index);
    unsigned long getRow(unsigned int index);
    void setRow(unsigned int index, unsigned long new_value);
    void setRow(unsigned int index, const std::string& new_value);
    std::vector<unsigned long> sumRows();

    void appendColumn( std::vector<bool> new_column );
    void appendColumn( std::string new_column );
    void removeColumn(unsigned long index);
    std::vector<bool> getColumn(unsigned int index);
    void setColumn(unsigned long index, std::vector<bool> new_value);
    void setColumn(unsigned long index, std::string new_value);
    std::vector<unsigned long> sumColumns();

    void transpose();

    static IncidenceMatrixSPtr readFromStream(std::istream &i_stream);
    void printToStream(std::ostream &o_stream);

    int getCountOne();
};

#endif //MAG_DIST_INCIDENCE_MATRIX_H
