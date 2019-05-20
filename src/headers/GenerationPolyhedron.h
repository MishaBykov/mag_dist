//
// Created by misha on 07.04.19.
//

#ifndef MAG_DIST_GENERATIONPOLYHEDRON_H
#define MAG_DIST_GENERATIONPOLYHEDRON_H

#include <vector>
#include <climits>
#include <set>
#include <Polyhedron.h>
#include "GenerationCombinations.h"


class GenerationPolyhedron {
//  На размерность меньше генерируемого
    std::vector<std::pair<long long, long long> > select_wh_2sc;
    std::vector<long long> select_w_facet;
    std::vector<std::string> all_comb;

    long long count_add_row = 0;
    long long k = 1;
    GenerationCombinations gc;

    Polyhedron base;
    IncidenceMatrix incidenceMatrix;
    Polyhedron result;

public:

    explicit GenerationPolyhedron() = default;
    GenerationPolyhedron(Polyhedron& vertexFigure, const std::string& file_name_2sc, const std::string& file_name_2n);

    ~GenerationPolyhedron();

    GenerationCombinations getGenerationCombinations();

    bool next();

    PolyhedronSPtr getResult();



};


#endif //MAG_DIST_GENERATIONPOLYHEDRON_H