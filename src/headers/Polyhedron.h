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
    Polyhedron(unsigned int dimension, IncidenceMatrix incidenceMatrix);

    bool isInitialized();

    void printToStream(std::ostream& out_stream);

    PolyhedronSPtr getVertexFigure(unsigned int index_column);
    PolyhedronSPtr getPolyhedronFacet(unsigned int index_row);

    std::shared_ptr<IncidenceMatrix> getMatrix();

    unsigned int getDimension();
    unsigned int getCountFacets();
    unsigned int getCountVertex();
    int getCountOne();

    void setMatrix(std::shared_ptr<IncidenceMatrix> new_matrix);

    static PolyhedronSPtr readFromStream(std::istream &i_stream);
    static std::vector<PolyhedronSPtr> readFromFile(const std::string& file_name);
    static std::vector<PolyhedronSPtr> readFromFile(
            const std::string& file_name,  unsigned int max_row, unsigned int max_column, bool count_column_fix);

    static void printToFile(std::vector<PolyhedronSPtr> &incidenceMatrix, const std::string &file_name);

    bool operator==(Polyhedron &polyhedron);
};


#endif //MAG_DIST_POLYHEDRON_H
