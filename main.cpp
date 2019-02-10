#include <iostream>
#include <incidence_matrix.hpp>


int main() {
    setlocale(LC_ALL, "rus");
    IncidenceMatrix incidence_matrix;
    incidence_matrix.appendRow("0011001");
    incidence_matrix.readFromFile("../3d.txt");
    return 0;
}