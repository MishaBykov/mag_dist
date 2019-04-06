//
// Created by misha on 18.03.19.
//

#ifndef MAG_DIST_CHEKER_H
#define MAG_DIST_CHEKER_H

#include <memory>

#include <Polyhedron.h>

class Checker {
public:

    static bool is3dSimplex(std::shared_ptr<Polyhedron> polyhedron);

    static bool is3d2sc(std::shared_ptr<Polyhedron> polyhedron);

    static bool is4d3dsimplex(std::shared_ptr<Polyhedron> polyhedron);

    static bool is4d2sc(std::shared_ptr<Polyhedron> polyhedron);
};


#endif //MAG_DIST_CHEKER_H
