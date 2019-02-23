//
// Created by misha on 11.10.18.
//

#ifndef mag_dist_MATRIX_H
#define mag_dist_MATRIX_H


#include <vector>
#include <string>

class IncidenceMatrix {

    unsigned int count_column = 0;

    std::vector<unsigned long int> matrix;

    void updateCountColumn(unsigned long int new_row);

    static unsigned long int stringToRow(std::string row);

public:
    IncidenceMatrix() = default;
    ~IncidenceMatrix() = default;

    unsigned int getCountColumn();
    unsigned long getCountRow();

    void appendRow( unsigned long int &&new_row );
    void appendRow( std::string new_row );
    unsigned long getRow(unsigned int index);
    void setRow(unsigned long index, unsigned long int new_row);
    void setRow(unsigned long index, std::string value);

    void printToFile(std::ofstream& file_out);

    static std::vector<IncidenceMatrix> readFromFile(const std::string& file_name);

    static void printToFile(std::vector<IncidenceMatrix> incidenceMatrix, const std::string& file_name);
};


#endif // mag_dist_MATRIX_H
