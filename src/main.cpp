#include <iostream>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>

int main() {
    setlocale(LC_ALL, "rus");
    Polyhedron p(3);
    Polyhedron::readFromFile("in.txt");
    return 0;
}