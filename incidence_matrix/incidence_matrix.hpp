//
// Created by misha on 11.10.18.
//

#ifndef mag_dist_MATRIX_H
#define mag_dist_MATRIX_H


#include <vector>
#include <string>

class IncidenceMatrix {
    std::vector< int > matrix;

public:
    IncidenceMatrix () = default;
    ~IncidenceMatrix () = default;

    void appendRow( int new_row );
    void appendRow( std::string new_row );

    int getRow(int index);
    void setRow(int index, int value);
    void setRow(int index, std::string value);

    void readFromFile(std::string file_name);

private:
    static int stringToRow(std::string row);
};


#endif // mag_dist_MATRIX_H
