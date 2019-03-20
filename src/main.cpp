#include <iostream>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationIncidenceMatrix.h>
#include <Chekcer.h>

int main() {
    setlocale(LC_ALL, "rus");

    IncidenceMatrix base;
    base.appendRow("0111");
    base.appendRow("1011");
    base.appendRow("1101");
    base.appendRow("1110");

//    GenerationIncidenceMatrix gip(base, 9, 20);
    GenerationIncidenceMatrix gip(base, 6, 14);

unsigned long k = 0;
    while (gip.next()){
        k++;
        Polyhedron polyhedron(4, gip.getResult());

        if (polyhedron.getMatrix().getCountRow() < 5 || polyhedron.getMatrix().getCountColumn() < 5) {
            continue;
        }
        auto sum_row = polyhedron.getMatrix().sumRows();
        bool f = false;
        for (unsigned long j : sum_row) {
            if (j != 4) {
                f = true;
                break;
            }
        }
        if (f) {
            continue;
        }
        bool d3simplex = true;
        unsigned int i = 0;
        for (i = 0; i < polyhedron.getMatrix().getCountRow(); ++i) {
            if (!Chekcer::d3simplex(polyhedron.getFacet(i))) {
                d3simplex = false;
                break;
            }
        }
        if (d3simplex)
            polyhedron.printToStream(std::cout);
    }

    return 0;
}