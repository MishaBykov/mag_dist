#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationCombinations.h>
#include <Checker.h>

std::string combToRow(unsigned int n, const std::vector<unsigned long>& combination){
    std::string result(n, '0');
    for( auto item : combination){
        result[item - 1] = '1';
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "rus");

    std::vector<std::pair<long long, long long> > wh_2sc;
    std::vector<long long> w_facet;
    auto v_2sc = Polyhedron::readFromFile("re_source/3dsc.txt");
    wh_2sc.reserve(v_2sc.size());
    for (auto &item : v_2sc) {
        wh_2sc.emplace_back(item->getCountVertex(), item->getCountFacets());
    }
    auto v_2n = Polyhedron::readFromFile("re_source/3d.txt");
    w_facet.reserve(v_2n.size());
    for (auto &item : v_2n) {
        w_facet.push_back(item->getCountFacets());
    }

    PolyhedronSPtr base = v_2sc[1];
    PolyhedronSPtr result = std::make_shared<Polyhedron>(base->getDimension() + 1);

    std::vector<std::pair<long long, long long> > select_wh_2sc;
    std::vector<long long> select_w_facet;
    for (auto &item : wh_2sc) {
        if (item.first == base->getCountVertex())
            select_wh_2sc.push_back(item);
    }
    for (auto &item : w_facet) {
        if (base->getDimension() <= item && item <= base->getCountVertex())
            select_w_facet.push_back(item);
    }

    long long count_add_row =
            (base->getCountVertex() * select_wh_2sc.back().first - base->getCountOne()) / select_w_facet[0];

    std::vector<std::string> all_comb;

    for( auto item : select_w_facet ){
        GenerationCombinations generationCombinations(base->getCountVertex(), item);
        all_comb.push_back(combToRow(base->getCountVertex(), generationCombinations.getC()));
        while (generationCombinations.next()){
            all_comb.push_back(combToRow(base->getCountVertex(), generationCombinations.getC()));
        }
    }

    for( unsigned int i = 1; i <= count_add_row; i++ ){
        std::vector<std::string> add_str;
        GenerationCombinations gp(all_comb.size(), i);
        for( auto item : gp.getC()){
            add_str.push_back(all_comb[item - 1]);
        }
        // добавить в result add_str
        // проверить result на 2n
    }

    return 0;
}

