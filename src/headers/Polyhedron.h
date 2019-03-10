//
// Created by misha on 24.02.19.
//

#ifndef MAG_DIST_POLYHEDRON_H
#define MAG_DIST_POLYHEDRON_H


#include <IncidenceMatrix.h>
#include <vector>
#include <ostream>

class Polyhedron {

    unsigned int dimension;
    IncidenceMatrix matrix;

public:

    explicit Polyhedron(unsigned int dimension);
    Polyhedron(unsigned int dimension, const IncidenceMatrix &incidenceMatrix);

    void printToStream(std::ostream& out_stream);

    Polyhedron getVertexFigure(unsigned int index_column);

    Polyhedron getFacet(unsigned int index_row);

    static std::vector<Polyhedron> readFromFile(std::string file_name);

    static void printToStream(std::vector<Polyhedron>& incidenceMatrix,const std::string& file_name);
};


#endif //MAG_DIST_POLYHEDRON_H
