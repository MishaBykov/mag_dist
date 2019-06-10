//
// Created by misha on 08.06.2019.
//

#include <clocale>
#include <Polyhedron.h>
#include <iostream>
#include <Checker.h>

int test() {
    setlocale(LC_ALL, "rus");

    auto v_test = Polyhedron::readFromFile("re_src/4d2sc.txt");

    for (int i = 0; i < v_test.size(); ++i) {
        auto sc = v_test[i]->getMatrix()->sumColumns();
        if (sc.empty()){
            v_test.erase(v_test.begin() + i);
            i--;
            continue;
        }
        if (sc.back() == 0) {
            v_test[i]->printToStream(std::cout);
            v_test[i]->getMatrix()->removeColumn(sc.size() - 1);
        }
        for (int j = 0; j < v_test[i]->getCountFacets(); ++j) {
            if ( !Checker::is3dSimplicial(v_test[i]->getPolyhedronFacet(j) ) )
            {
                std::cout << i << std::endl;
                v_test[i]->printToStream(std::cout);
                v_test.erase(v_test.begin() + i);
                i--;
                break;
            }
        }
    }
    Polyhedron::printToFile(v_test, "re_src/4d2sc.txt");

    return 0;
}