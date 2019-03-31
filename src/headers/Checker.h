//
// Created by misha on 18.03.19.
//

#ifndef MAG_DIST_CHEKER_H
#define MAG_DIST_CHEKER_H

#include <memory>

#include <Polyhedron.h>

class Checker {
public:

    static bool isD3simplex(std::shared_ptr<Polyhedron> polyhedron);

    static bool isD3_2sc(std::shared_ptr<Polyhedron> polyhedron);

    static bool is4d3dsimplex(std::shared_ptr<Polyhedron> polyhedron);
};


#endif //MAG_DIST_CHEKER_H
