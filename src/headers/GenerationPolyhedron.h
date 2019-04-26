//
// Created by misha on 07.04.19.
//

#ifndef MAG_DIST_GENERATIONPOLYHEDRON_H
#define MAG_DIST_GENERATIONPOLYHEDRON_H

#include <vector>
#include <climits>
#include <set>
#include <Polyhedron.h>


class GenerationPolyhedron {
//  На размерность меньше генерируемого
    std::vector<PolyhedronSPtr> vertexFigures;
    std::vector<PolyhedronSPtr> polyhedrons2neighborly;

    PolyhedronSPtr vertexFigure = nullptr;
    PolyhedronSPtr result = nullptr;

public:

    explicit GenerationPolyhedron() = default;
    explicit GenerationPolyhedron(PolyhedronSPtr vertexFigure,
                                  std::vector<PolyhedronSPtr> vertexFigures,
                                  std::vector<PolyhedronSPtr> polyhedrons2neighborly);

    ~GenerationPolyhedron();

    static std::vector<int> getCountsRow(std::vector< std::shared_ptr< Polyhedron > >& polyhedrons);
    static std::vector<int> getCountsColumn(std::vector< std::shared_ptr< Polyhedron > >& polyhedrons);

    bool next();

    PolyhedronSPtr getResult();



};


#endif //MAG_DIST_GENERATIONPOLYHEDRON_H
