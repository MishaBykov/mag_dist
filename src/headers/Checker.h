//
// Created by misha on 18.03.19.
//

#ifndef MAG_DIST_CHEKER_H
#define MAG_DIST_CHEKER_H

#include <memory>

#include <Polyhedron.h>

class Checker {
public:

    static bool is3dSimplexDepth(const std::shared_ptr<Polyhedron>& polyhedron);

    static bool is3dSimplex(const std::shared_ptr<Polyhedron>& polyhedron);

    static bool is3d2sc(const std::shared_ptr<Polyhedron>& polyhedron);

    static bool is4d2neighborly(const std::shared_ptr<Polyhedron>& polyhedron);

    static bool is4d2sc(const std::shared_ptr<Polyhedron>& polyhedron);

    static bool is5d2neighborly(const std::shared_ptr<Polyhedron>& polyhedron);

    static bool is6d2neighborly(const std::shared_ptr<Polyhedron>& polyhedron);

    static bool isCompleteGraph(const std::shared_ptr<Polyhedron> &polyhedron);
};


#endif //MAG_DIST_CHEKER_H
