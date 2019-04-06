#include <iostream>
#include <memory>
#include <algorithm>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationIncidenceMatrix.h>
#include <Checker.h>


int main() {
    setlocale(LC_ALL, "rus");

    auto v_polyhedron = Polyhedron::readFromFile("../input_files/4d2sc.txt");

    int count_2sc = 0;
    for (auto &i : *v_polyhedron) {
        if( Checker::is4d2sc(i) )
            count_2sc++;
    }

    std::cout << v_polyhedron->size() << std::endl << count_2sc << std::endl;

    return 0;
}

