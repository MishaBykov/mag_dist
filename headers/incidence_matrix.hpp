//
// Created by misha on 11.10.18.
//

#ifndef mag_dist_MATRIX_H
#define mag_dist_MATRIX_H


#include <vector>
#include <string>

class IncidenceMatrix {
    std::vector< int > matrix;

    static int stringToRow(std::string row);

public:
    IncidenceMatrix () = default;
    ~IncidenceMatrix () = default;

    void appendRow( int new_row );

    void appendRow( std::string new_row );
    int getRow(int index);
    void setRow(int index, int value);

    void setRow(int index, std::string value);

    void printToFile(const std::string& file_name);

    static std::vector<IncidenceMatrix> readFromFile(const std::string& file_name);

    static void printToFile(std::vector<IncidenceMatrix> incidenceMatrix, const std::string& file_name);
};


#endif // mag_dist_MATRIX_H
