//
// Created by misha on 07.04.19.
//

#include <utility>
#include <string>
#include <iostream>

#include <GenerationPolyhedron.h>


GenerationPolyhedron::GenerationPolyhedron(PolyhedronSPtr vertexFigure) : base(std::move(vertexFigure)) {

}

GenerationPolyhedron::~GenerationPolyhedron() = default;

PolyhedronSPtr GenerationPolyhedron::getResult() {
    return result;
}

bool GenerationPolyhedron::next() {


    return true;
}
