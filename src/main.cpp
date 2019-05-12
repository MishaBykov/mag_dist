#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationCombinations.h>
#include <Checker.h>
#include <Logs.h>

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
    auto v_2sc = Polyhedron::readFromFile("re_src/3d2sc.txt");
    wh_2sc.reserve(v_2sc.size());
    for (auto &item : v_2sc) {
        wh_2sc.emplace_back(item->getCountVertex(), item->getCountFacets());
    }
    auto v_2n = Polyhedron::readFromFile("re_src/3d.txt");
    w_facet.reserve(v_2n.size());
    for (auto &item : v_2n) {
        w_facet.push_back(item->getCountFacets());
    }

    PolyhedronSPtr base = v_2sc[4];
    PolyhedronSPtr result;

    IncidenceMatrixSPtr incidenceMatrix = std::make_shared<IncidenceMatrix>(*(base->getMatrix()));

    std::vector<std::pair<long long, long long> > select_wh_2sc;
    std::vector<long long> select_w_facet;
    for (auto &item : wh_2sc) {
        if (item.first == base->getCountVertex())
            select_wh_2sc.push_back(item);
    }
    for (auto &item : w_facet) {
        if (base->getDimension() < item && item <= base->getCountVertex())
            select_w_facet.push_back(item);
    }

    long long count_add_row =
            (base->getCountVertex() * select_wh_2sc.back().second - base->getCountOne()) / select_w_facet[0];
    Logs::print(count_add_row);

    std::vector<std::string> all_comb;

    for (auto item : select_w_facet) {
        GenerationCombinations gc(base->getCountVertex(), item);
        do {
            all_comb.push_back(combToRow(base->getCountVertex(), gc.getC()) + '0');
        } while (gc.next());
    }
    Logs::print(all_comb.size());

    std::vector<bool> column(base->getCountFacets(), true);
    incidenceMatrix->appendColumn(column);

    for (unsigned int i = 1; i <= count_add_row; i++) {
        GenerationCombinations gc(all_comb.size(), i);
        std::shared_ptr<Polyhedron> p;
        incidenceMatrix->appendRow(0);
        do {
            auto c = gc.getC();
            for (unsigned int j = 0; j < c.size(); j++) {
                incidenceMatrix->setRow(base->getCountFacets() + j, all_comb[c[j] - 1]);
            }
            result = std::make_shared<Polyhedron>(base->getDimension() + 1, incidenceMatrix);
            if (!result->isInitialized()) {
                Logs::print("[result] not initialized");
                continue;
            }
            if (Checker::is2neighborly(result)) {
                Logs::print("[result] true");
                result->printToStream(std::cout);
            } else {
                Logs::print("[result] false");
            }
        } while (gc.next());
    }

    return 0;
}

