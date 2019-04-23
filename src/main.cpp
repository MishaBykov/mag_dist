#include <iostream>
#include <memory>
#include <algorithm>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationCombinations.h>
#include <Checker.h>


int main() {
    setlocale(LC_ALL, "rus");

    auto p5 = Polyhedron::readFromFile("out");
    for (const auto& i : p5) {
        auto c_c = i->getMatrix()->sumColumns();
        for(int j = 1; j < c_c.size(); j++){
            if(c_c[j] != c_c[0]) {

                break;
            }
        }
    }

    return 0;
}

