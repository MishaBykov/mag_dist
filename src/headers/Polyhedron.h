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
    std::shared_ptr<IncidenceMatrix> matrix = nullptr;

    static bool checkIncidenceMatrix(std::shared_ptr<IncidenceMatrix> incidenceMatrix, unsigned int dimension);

public:

    Polyhedron();
    explicit Polyhedron(unsigned int dimension);
    Polyhedron(unsigned int dimension, std::shared_ptr<IncidenceMatrix> incidenceMatrix);

    bool isIinitialized();

    void printToStream(std::ostream& out_stream);

    std::shared_ptr<Polyhedron> getVertexFigure(unsigned int index_column);
    std::shared_ptr<Polyhedron> getFacetIncidenceMatrix(unsigned int index_row);

    std::shared_ptr<IncidenceMatrix> getMatrix();

    unsigned int getDimension();

    void setMatrix(std::shared_ptr<IncidenceMatrix> new_matrix);

    static std::shared_ptr<Polyhedron> readFromStream(std::istream &i_stream);
    static std::shared_ptr<std::vector<Polyhedron>> readFromFile(std::string file_name);

    static void printToFile(std::vector<Polyhedron> &incidenceMatrix, const std::string &file_name);
};


#endif //MAG_DIST_POLYHEDRON_H
