//
// Created by misha on 24.02.19.
//

#ifndef MAG_DIST_POLYHEDRON_H
#define MAG_DIST_POLYHEDRON_H


#include <IncidenceMatrix.h>
#include <vector>
#include <ostream>

class Polyhedron;
using PolyhedronSPtr = std::shared_ptr<Polyhedron>;

class Polyhedron {

    unsigned int dimension = 0;
    std::shared_ptr<IncidenceMatrix> matrix = nullptr;

    static bool checkIncidenceMatrix(const std::shared_ptr<IncidenceMatrix>& incidenceMatrix, unsigned int dimension);



public:

    Polyhedron();
    explicit Polyhedron(unsigned int dimension);
    Polyhedron(unsigned int dimension, const std::shared_ptr<IncidenceMatrix>& incidenceMatrix);

    bool isIinitialized();

    void printToStream(std::ostream& out_stream);

    PolyhedronSPtr getVertexFigure(unsigned int index_column);
    PolyhedronSPtr getFacetIncidenceMatrix(unsigned int index_row);

    std::shared_ptr<IncidenceMatrix> getMatrix();

    unsigned int getDimension();
    unsigned int getCountFacets();
    unsigned int getCountVertex();

    void setMatrix(std::shared_ptr<IncidenceMatrix> new_matrix);

    static PolyhedronSPtr readFromStream(std::istream &i_stream);
    static std::vector<PolyhedronSPtr> readFromFile(const std::string& file_name);

    static void printToFile(std::vector<PolyhedronSPtr> &incidenceMatrix, const std::string &file_name);
};


#endif //MAG_DIST_POLYHEDRON_H
