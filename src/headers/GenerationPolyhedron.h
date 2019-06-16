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
    std::vector<long long> select_f_2sc;
    std::vector<long long> select_v_2n;
    std::vector<std::string> all_comb;

    long long count_add_row = 0;
    long long k = 1;
    GenerationCombinations gc;

    PolyhedronSPtr base;
    IncidenceMatrix incidenceMatrix;
    Polyhedron result;

public:

    explicit GenerationPolyhedron() = default;
    GenerationPolyhedron(
            unsigned int max_add_count_row, PolyhedronSPtr vertex_figure, const std::vector<PolyhedronSPtr>& v_2sc,
            const std::vector<PolyhedronSPtr>& v_2n);

    ~GenerationPolyhedron();

    GenerationCombinations getGenerationCombinations();

    bool next();

    PolyhedronSPtr getResult();

    void setCombination(const std::vector<unsigned long> &combination);

};


#endif //MAG_DIST_GENERATIONPOLYHEDRON_H
