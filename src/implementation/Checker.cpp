//
// Created by misha on 18.03.19.
//

#include <algorithm>
#include <iostream>
#include <Checker.h>

bool Checker::is3dSimplex(const std::shared_ptr<Polyhedron>& polyhedron) {
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

bool Checker::is3dSimplicial(const std::shared_ptr<Polyhedron>& polyhedron) {
    if ( !polyhedron || polyhedron->getDimension() != 3 )
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

bool Checker::is3d2sc(const std::shared_ptr<Polyhedron>& polyhedron) {
    if(!polyhedron || polyhedron->getDimension() != 3)
        return false;
    auto sum_rows = polyhedron->getMatrix()->sumRows();

    for (auto sum_row : sum_rows) {
        if( sum_row != 3 )
            return false;
    }

    return true;
}

bool Checker::is4d2neighborly(const std::shared_ptr<Polyhedron>& polyhedron) {
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

bool Checker::is4d2sc(const std::shared_ptr<Polyhedron>& polyhedron) {
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

bool Checker::is5d2neighborly(const std::shared_ptr<Polyhedron>& polyhedron) {
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

bool Checker::isDepth3dSimplex(const std::shared_ptr<Polyhedron> &polyhedron) {
    switch (polyhedron->getDimension()) {
        case 3:
            return is3dSimplex(polyhedron);
        case 4:
            return is4d2neighborly(polyhedron);
        case 5:
            return is5d2neighborly(polyhedron);
        case 6:
            return is6d2neighborly(polyhedron);
        default:
            std::cout << "[Checker::isCompleteGraph][" << polyhedron->getDimension() <<"] Не известная размерность" << std::endl;
    }
    return false;
}

bool Checker::is6d2neighborly(const std::shared_ptr<Polyhedron>& polyhedron) {
    if(!polyhedron || polyhedron->getDimension() != 5)
        return false;
    unsigned int i = 0;
    for (i = 0; i < polyhedron->getMatrix()->getCountRow(); ++i) {
        if (!Checker::is5d2neighborly(polyhedron->getPolyhedronFacet(i))) {
            return false;
        }
    }
    return true;
}

bool Checker::isCompleteGraph(const std::shared_ptr<Polyhedron> &polyhedron) {
    auto transpose_matrix = polyhedron->getMatrix()->getTransposeMatrix();
    std::sort(transpose_matrix.rbegin(), transpose_matrix.rend());

    for (int i = 0; i < transpose_matrix.size(); ++i) {
        for (int j = i + 1; j < transpose_matrix.size(); ++j) {
            auto intersection_i_j = transpose_matrix[i] & transpose_matrix[j];
            for (int k = 0; k < transpose_matrix.size(); ++k) {
                if( k != i && k !=j && ( (transpose_matrix[k] & intersection_i_j) == intersection_i_j )  ) {
                   return false;
                }
            }
        }
    }
    return true;
}

bool Checker::isFacetsPolyhedronInVector(const std::shared_ptr<Polyhedron> &polyhedron,
        const std::vector<PolyhedronSPtr>& vector) {
    for (unsigned int i = 0; i < polyhedron->getMatrix()->getCountRow(); ++i) {
        auto facet = polyhedron->getPolyhedronFacet(i);
        bool f = false;
        for(const auto& item : vector ){
            if (*item == *facet) {
                f = true;
                break;
            }
        }
        if (!f)
            return false;
    }

    return true;
}
