//
// Created by misha on 07.04.19.
//

#include <utility>
#include <string>
#include <iostream>

#include <GenerationPolyhedron.h>

//GenerationPolyhedron::GenerationPolyhedron(
//            PolyhedronSPtr vertexFigure, vec_uns_int countsRows, vec_uns_int countsColumns
//        ) : vertexFigure(std::move(vertexFigure)),
//            countsRows(std::move(countsRows)),
//            countsColumns(std::move(countsColumns)) {}

GenerationPolyhedron::~GenerationPolyhedron() = default;

PolyhedronSPtr GenerationPolyhedron::getResult() {
    return result;
}

bool GenerationPolyhedron::next() {


    return true;
}

std::vector<int> GenerationPolyhedron::getCountsColumn(std::vector<std::shared_ptr<Polyhedron> > &polyhedrons) {
    std::set<int> counts_column;
    for (auto &i : polyhedrons) {
        counts_column.insert(i->getCountVertex());
    }
    return std::vector<int>(counts_column.begin(), counts_column.end());
}

std::vector<int> GenerationPolyhedron::getCountsRow(std::vector<std::shared_ptr<Polyhedron> > &polyhedrons) {
    std::set<int> counts_row;
    for (auto &i : polyhedrons) {
        counts_row.insert(i->getCountFacets());
    }
    return std::vector<int>(counts_row.begin(), counts_row.end());
}
