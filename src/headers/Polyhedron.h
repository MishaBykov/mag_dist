//
// Created by misha on 24.02.19.
//

#ifndef MAG_DIST_POLYHEDRON_H
#define MAG_DIST_POLYHEDRON_H


#include <IncidenceMatrix.h>
#include <vector>
#include <ostream>

class Polyhedron {

    unsigned int dimension = 0;
    IncidenceMatrix matrix;

    static void checkIncidenceMatrix(IncidenceMatrix &incidenceMatrix, unsigned int dimension);

public:

    Polyhedron();
    explicit Polyhedron(unsigned int dimension);
    Polyhedron(unsigned int dimension, IncidenceMatrix incidenceMatrix);

    void printToStream(std::ostream& out_stream);

    Polyhedron getVertexFigure(unsigned int index_column);

    Polyhedron getFacet(unsigned int index_row);

    IncidenceMatrix getMatrix();

    unsigned int getDimension();

    void setMatrix(IncidenceMatrix new_matrix);

    static std::vector<Polyhedron> readFromFile(std::string file_name);

    void readFromStream(std::istream &i_stream);

    static void printToStream(std::vector<Polyhedron>& incidenceMatrix,const std::string& file_name);
};


#endif //MAG_DIST_POLYHEDRON_H
