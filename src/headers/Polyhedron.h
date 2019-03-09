//
// Created by misha on 24.02.19.
//

#ifndef MAG_DIST_POLYHEDRON_H
#define MAG_DIST_POLYHEDRON_H


#include <IncidenceMatrix.h>
#include <vector>
#include <fstream>

class Polyhedron {

    unsigned int dimension;
    IncidenceMatrix incidenceMatrix;

public:

    explicit Polyhedron(unsigned int dimension);
    Polyhedron(unsigned int dimension, const IncidenceMatrix &incidenceMatrix);

    static std::vector<Polyhedron> readFromFile(std::string file_name);

//    static void printToStream(std::vector<Polyhedron> incidenceMatrix, std::string file_name);
};


#endif //MAG_DIST_POLYHEDRON_H
