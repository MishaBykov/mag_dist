//
// Created by misha on 07.04.19.
//

#ifndef MAG_DIST_GENERATIONPOLYHEDRON_H
#define MAG_DIST_GENERATIONPOLYHEDRON_H

#include <vector>
#include <Polyhedron.h>
#include <climits>

using vec_uns_int = std::vector<unsigned int> ;


class GenerationPolyhedron {

    vec_uns_int countsRows;
    vec_uns_int countsColumns;

    PolyhedronSPtr vertexFigure = nullptr;
    PolyhedronSPtr result = nullptr;

public:

    explicit GenerationPolyhedron() = default;
    explicit GenerationPolyhedron(PolyhedronSPtr vertexFigure, vec_uns_int countsRows, vec_uns_int countsColumns);

    ~GenerationPolyhedron();

    bool next();

    PolyhedronSPtr getResult();



};


#endif //MAG_DIST_GENERATIONPOLYHEDRON_H
