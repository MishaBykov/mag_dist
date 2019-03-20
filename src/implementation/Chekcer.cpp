//
// Created by misha on 18.03.19.
//

#include <Chekcer.h>

#include "Chekcer.h"

bool Chekcer::d3simplex(Polyhedron polyhedron) {
    if (polyhedron.getDimension() != 3 || 
        polyhedron.getMatrix().getCountRow() != 4 || 
        polyhedron.getMatrix().getCountColumn() != 4)
    {
        return false;
    }
    
    auto sum_rows = polyhedron.getMatrix().sumRows();
    for (unsigned long sum_row : sum_rows) {
        if (sum_row != 3)
            return false;
    }
    
    return true;
}
