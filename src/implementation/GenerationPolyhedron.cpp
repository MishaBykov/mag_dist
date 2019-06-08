#include <utility>

#include <utility>

#include <utility>

//
// Created by misha on 07.04.19.
//

#include <utility>
#include <string>
#include <iostream>
#include <algorithm>

#include <GenerationPolyhedron.h>
#include <GenerationCombinations.h>
#include <Logs.h>

std::string combToRow(unsigned int n, const std::vector<unsigned long>& combination){
    std::string result(n, '0');
    for( auto item : combination){
        result[item - 1] = '1';
    }
    return result;
}

GenerationPolyhedron::GenerationPolyhedron (unsigned int max_count_row,
            PolyhedronSPtr vertex_figure, const std::vector<PolyhedronSPtr>& v_2sc,
            const std::vector<PolyhedronSPtr>& v_2n) : base(std::move(vertex_figure))
{
    long long max_count_facet = 0;
    for (auto &item : v_2sc) {
        if (item->getCountVertex() == base->getCountVertex()) {
            select_vf_2sc.emplace_back(item->getCountVertex(), item->getCountFacets());
            if( select_vf_2sc.back().second > max_count_facet )
                max_count_facet = select_vf_2sc.back().second;
        }
    }

    for (auto &item : v_2n) {
        if (base->getDimension() < item->getCountVertex() && item->getCountVertex() <= base->getCountVertex()) {
            select_v_facet.push_back(item->getCountVertex());
        }
    }
    long long min_count_vertex = *std::min_element(select_v_facet.begin(), select_v_facet.end());

    incidenceMatrix = (*(base->getMatrix()));

    count_add_row = (base->getCountVertex() * max_count_facet - base->getCountOne()) / min_count_vertex;
    if( base->getCountFacets() + count_add_row > max_count_row )
        count_add_row = max_count_row - base->getCountFacets();
    if(count_add_row > std::max( max_count_row, base->getCountFacets()))
        count_add_row = 0;
    if (count_add_row != 0) {
        for (auto item : select_v_facet) {
            GenerationCombinations gc(base->getCountVertex(), item);
            do {
                all_comb.push_back(combToRow(base->getCountVertex(), gc.getCombination()) + '0');
            } while (gc.next());
        }

        std::vector<bool> column(base->getCountFacets(), true);
        incidenceMatrix.appendColumn(column);
        gc = GenerationCombinations(all_comb.size(), k);

        incidenceMatrix.appendRow(0);
        auto combination = gc.getCombination();
        for (unsigned int j = 0; j < combination.size(); j++) {
            incidenceMatrix.setRow(base->getCountFacets() + j, all_comb[combination[j] - 1]);
        }
        result = Polyhedron(base->getDimension() + 1, incidenceMatrix);
    }
}

GenerationPolyhedron::~GenerationPolyhedron() = default;

PolyhedronSPtr GenerationPolyhedron::getResult() {
    return std::make_shared<Polyhedron>(result);
}

bool GenerationPolyhedron::next() {
    auto combination = gc.getCombination();
    for (unsigned int j = 0; j < combination.size(); j++) {
        incidenceMatrix.setRow(base->getCountFacets() + j, all_comb[combination[j] - 1]);
    }
    result = Polyhedron(base->getDimension() + 1, incidenceMatrix);
    if (gc.next()) {
        return true;
    } else {
        incidenceMatrix.appendRow(0);
        k++;
        if (k > count_add_row)
            return false;
        gc = GenerationCombinations(all_comb.size(), k);
        return true;
    }
}

GenerationCombinations GenerationPolyhedron::getGenerationCombinations() {
    return gc;
}

void GenerationPolyhedron::setCombination(const std::vector<unsigned long> &combination) {
    while( k < combination.size() ){
        incidenceMatrix.appendRow(0);
        k++;
    }
    gc.setCombination(combination);
}
