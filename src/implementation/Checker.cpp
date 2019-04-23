//
// Created by misha on 18.03.19.
//

#include <Checker.h>

bool Checker::is3dSimplex(std::shared_ptr<Polyhedron> polyhedron) {
    if ( !polyhedron ||
         polyhedron->getDimension() != 3 ||
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

bool Checker::is3d2sc(std::shared_ptr<Polyhedron> polyhedron) {
    if(!polyhedron || polyhedron->getDimension() != 3)
        return false;
    auto sum_rows = polyhedron->getMatrix()->sumRows();

    for (auto sum_row : sum_rows) {
        if( sum_row != 3 )
            return false;
    }

    return true;
}

bool Checker::is4d2neighborly(std::shared_ptr<Polyhedron> polyhedron) {
    if(!polyhedron || polyhedron->getDimension() != 4)
        return false;
    unsigned int i = 0;
    for (i = 0; i < polyhedron->getMatrix()->getCountRow(); ++i) {
        if (!Checker::is3dSimplex(polyhedron->getPolyhedronFacet(i))) {
            return false;
        }
    }
    return true;
}

bool Checker::is4d2sc(std::shared_ptr<Polyhedron> polyhedron) {
    if(!polyhedron || polyhedron->getDimension() != 4)
        return false;
    unsigned int i = 0;
    for (i = 0; i < polyhedron->getMatrix()->getCountRow(); ++i) {
        if (!Checker::is3d2sc(polyhedron->getPolyhedronFacet(i))) {
            return false;
        }
    }
    return true;
}

bool Checker::is5d2neighborly(std::shared_ptr<Polyhedron> polyhedron) {
    if(!polyhedron || polyhedron->getDimension() != 5)
        return false;
    unsigned int i = 0;
    for (i = 0; i < polyhedron->getMatrix()->getCountRow(); ++i) {
        if (!Checker::is4d2neighborly(polyhedron->getPolyhedronFacet(i))) {
            return false;
        }
    }
    return true;
}
