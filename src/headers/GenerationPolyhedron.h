//
// Created by misha on 07.04.19.
//

#ifndef MAG_DIST_GENERATIONPOLYHEDRON_H
#define MAG_DIST_GENERATIONPOLYHEDRON_H

#include <vector>
#include <climits>
#include <set>
#include <Polyhedron.h>

using vec_uns_int = std::vector<unsigned int> ;


class GenerationPolyhedron {

    vec_uns_int countsRows;
    vec_uns_int countsColumns;

    PolyhedronSPtr vertexFigure = nullptr;
    PolyhedronSPtr result = nullptr;

public:

    explicit GenerationPolyhedron() = default;
    explicit GenerationPolyhedron(PolyhedronSPtr vertexFigure, vec_uns_int countsRows, vec_uns_int countsColumns);

    ~GenerationPolyhedron();

    static std::vector<int> getCountsRow(std::vector< std::shared_ptr< Polyhedron > >& polyhedrons) {
        std::set<int> counts_row;
        for (auto &i : polyhedrons) {
            counts_row.insert(i->getCountFacets());
        }
        return std::vector<int>(counts_row.begin(), counts_row.end());
    }
    static std::vector<int> getCountsColumn(std::vector< std::shared_ptr< Polyhedron > >& polyhedrons) {
        std::set<int> counts_column;
        for (auto &i : polyhedrons) {
            counts_column.insert(i->getCountVertex());
        }
        return std::vector<int>(counts_column.begin(), counts_column.end());
    }

    bool next();

    PolyhedronSPtr getResult();



};


#endif //MAG_DIST_GENERATIONPOLYHEDRON_H
