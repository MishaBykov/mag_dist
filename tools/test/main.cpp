//
// Created by misha on 08.06.2019.
//

#include <clocale>
#include <Polyhedron.h>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");

//    auto v_test = Polyhedron::readFromFile("test.txt");
    auto v_2sc = Polyhedron::readFromFile("re_src/3d2sc.txt");
    auto v_2n = Polyhedron::readFromFile("re_src/3d2n.txt");
    std::ofstream file_result("vf");
    for (unsigned int i = 0; i < v_test[0]->getCountVertex(); ++i) {
        for (unsigned int j = 0; j < v_2sc.size(); ++j) {
            auto vf = *v_test[0]->getVertexFigure(i);
            vf.printToStream(file_result);
            if (vf == *v_2sc[j])
                std::cout << i << " " << j << std::endl;
        }
    }
    file_result.close();
//
    auto vf = Polyhedron::readFromFile("vf");
    for (unsigned int i = 0; i < vf.size(); ++i) {
        for (unsigned int j = i + 1; j < vf.size(); ++j) {
            if (*vf[i] == *vf[j]) {
                vf.erase(vf.begin() + j);
                std::cout << "del " << j << std::endl;
                j--;
            }
        }
    }
    Polyhedron::printToFile(vf, "vf");

    return 0;
}