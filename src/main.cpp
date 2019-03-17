#include <iostream>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationIncidenceMatrix.h>

int main() {
    setlocale(LC_ALL, "rus");

    auto vp = Polyhedron::readFromFile("../input_files/4d_temp.txt");
    std::cout << vp.size() << std::endl;

    int j = 0;
    for (auto &i : vp) {
        if (i.getMatrix().getCountRow() < 22)
            j++;
            i.printToStream(std::cout);
    }

    std::cout << j << std::endl;

    return 0;
}