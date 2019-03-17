#include <iostream>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationIncidenceMatrix.h>

int main() {
    setlocale(LC_ALL, "rus");

    auto vp = Polyhedron::readFromFile("../input_files/5d_temp.txt");

    std::ofstream out_file("../input_files/5d.txt");

    for (auto &i : vp) {
        if (i.getMatrix().getCountRow() < 22) {
            i.printToStream(out_file);
        }
    }

    out_file.close();

    return 0;
}