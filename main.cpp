#include <iostream>
#include <incidence_matrix.hpp>


int main() {
    setlocale(LC_ALL, "rus");
    IncidenceMatrix incidence_matrix;
    incidence_matrix.appendRow("0011001");
    auto i = IncidenceMatrix::readFromFile("../input_files/3d.txt");
    i[0].printToFile("out.txt");
    return 0;
}