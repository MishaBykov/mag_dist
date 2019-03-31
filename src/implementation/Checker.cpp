//
// Created by misha on 18.03.19.
//

#include <Checker.h>

bool Checker::isD3simplex(std::shared_ptr<Polyhedron> polyhedron) {
    if (polyhedron->getDimension() != 3 ||
        polyhedron->getMatrix()->getCountRow() != 4 ||
        polyhedron->getMatrix()->getCountColumn() != 4)
    {
        return false;
    }
    
    auto sum_rows = polyhedron->getMatrix()->sumRows();
    for (unsigned long sum_row : sum_rows) {
        if (sum_row != 3)
            return false;
    }
    
    return true;
}

bool Checker::isD3_2sc(std::shared_ptr<Polyhedron> polyhedron) {
    if(polyhedron->getDimension() != 3)
        return false;
    auto sum_rows = polyhedron->getMatrix()->sumRows();

    for (auto sum_row : sum_rows) {
        if( sum_row != 3 )
            return false;
    }

    return true;
}

bool Checker::is4d3dsimplex(std::shared_ptr<Polyhedron> polyhedron) {
    unsigned int i = 0;
    for (i = 0; i < polyhedron->getMatrix()->getCountRow(); ++i) {
        if (!Checker::isD3simplex(polyhedron->getFacetIncidenceMatrix(i))) {
            return false;
        }
    }
    return true;
}
