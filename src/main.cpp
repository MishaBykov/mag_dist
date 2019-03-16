#include <iostream>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationIncidenceMatrix.h>

int main() {
    setlocale(LC_ALL, "rus");

    IncidenceMatrix base;
    base.appendRow("11");
    base.appendRow("11");

    base.printToStream(std::cout);

    GenerationIncidenceMatrix gim(base, 3, 4);

    while (gim.next())
        gim.getResult().printToStream(std::cout);

    return 0;
}