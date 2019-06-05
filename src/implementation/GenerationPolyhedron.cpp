#include <utility>

//
// Created by misha on 07.04.19.
//

#include <utility>
#include <string>
#include <iostream>

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

GenerationPolyhedron::GenerationPolyhedron (
            Polyhedron& vertexFigure, const std::vector<PolyhedronSPtr>& v_2sc, const std::vector<PolyhedronSPtr>& v_2n)
            : base(vertexFigure)
{
    std::vector<std::pair<long long, long long> > wh_2sc;
    std::vector<long long> w_facet;

    wh_2sc.reserve(v_2sc.size());
    for (auto &item : v_2sc) {
        wh_2sc.emplace_back(item->getCountVertex(), item->getCountFacets());
    }

    w_facet.reserve(v_2n.size());
    for (auto &item : v_2n) {
        w_facet.push_back(item->getCountFacets());
    }

    incidenceMatrix = (*(base.getMatrix()));

    for (auto &item : wh_2sc) {
        if (item.first == base.getCountVertex())
            select_wh_2sc.push_back(item);
    }
    for (auto &item : w_facet) {
        if (base.getDimension() < item && item <= base.getCountVertex())
            select_w_facet.push_back(item);
    }

    // todo исправить
    count_add_row = (base.getCountVertex() * select_wh_2sc.back().second - base.getCountOne()) / select_w_facet[0];

    for (auto item : select_w_facet) {
        GenerationCombinations gc(base.getCountVertex(), item);
        do {
            all_comb.push_back(combToRow(base.getCountVertex(), gc.getCombination()) + '0');
        } while (gc.next());
    }

    std::vector<bool> column(base.getCountFacets(), true);
    incidenceMatrix.appendColumn(column);
    gc = GenerationCombinations(all_comb.size(), k);
    incidenceMatrix.appendRow(0);
}

GenerationPolyhedron::~GenerationPolyhedron() = default;

PolyhedronSPtr GenerationPolyhedron::getResult() {
    return std::make_shared<Polyhedron>(result);
}

bool GenerationPolyhedron::next() {
    auto combination = gc.getCombination();
    for (unsigned int j = 0; j < combination.size(); j++) {
        incidenceMatrix.setRow(base.getCountFacets() + j, all_comb[combination[j] - 1]);
    }
    result = Polyhedron(base.getDimension() + 1, incidenceMatrix);
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
