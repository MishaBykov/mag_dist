//
// Created by misha on 08.06.2019.
//

#include <clocale>
#include <Polyhedron.h>
#include <iostream>
#include <Checker.h>

int test() {
    setlocale(LC_ALL, "rus");

    auto v_test = Polyhedron::readFromFile("result/4d to 5d less 12/result.txt");

    for(unsigned int i = 0; i < v_test.size(); i++ )
    {
        for(unsigned int j = i + 1; j < v_test.size(); j++ ) {
            if (*v_test[i] == *v_test[j]) {
                v_test.erase(v_test.begin() + j);
                j--;
            }
        }
    }

    Polyhedron::printToFile(v_test, "result/del copy/4d_to_5d_less_12.txt");


    return 0;
}