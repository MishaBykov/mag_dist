#include <utility>

#include <utility>

//
// Created by misha on 07.04.19.
//

#include <utility>
#include <string>
#include <iostream>

#include <GenerationPolyhedron.h>

GenerationPolyhedron::GenerationPolyhedron(
        PolyhedronSPtr vertexFigure, vec_uns_int countsRows, vec_uns_int countsColumns
        ) :  vertexFigure(std::move(vertexFigure)),
        countsRows(std::move(countsRows)),
        countsColumns(std::move(countsColumns)) {}

GenerationPolyhedron::~GenerationPolyhedron() = default;

PolyhedronSPtr GenerationPolyhedron::getResult() {
    return result;
}

bool GenerationPolyhedron::next() {


    return true;
}
