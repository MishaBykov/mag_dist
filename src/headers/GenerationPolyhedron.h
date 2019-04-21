//
// Created by misha on 07.04.19.
//

#ifndef MAG_DIST_GENERATIONPOLYHEDRON_H
#define MAG_DIST_GENERATIONPOLYHEDRON_H

#include <vector>
#include <Polyhedron.h>
#include <climits>

using LongInt = long long;

class GenerationPolyhedron {

    PolyhedronSPtr base = nullptr;
    PolyhedronSPtr result = nullptr;



public:

    explicit GenerationPolyhedron() = default;
    explicit GenerationPolyhedron(PolyhedronSPtr base);


    ~GenerationPolyhedron();

    bool next();

    PolyhedronSPtr getResult();



};


#endif //MAG_DIST_GENERATIONPOLYHEDRON_H
