//
// Created by misha on 08.06.2019.
//

#include <clocale>
#include <Polyhedron.h>
#include <iostream>
#include <vector>

int generate_table() {
    setlocale(LC_ALL, "rus");

    std::string name_file = "5d2sc.txt";

    auto v = Polyhedron::readFromFile("re_src/" + name_file);

    std::vector<std::vector<unsigned int>> result;

    for (unsigned int i = 0; i < v.size(); i++) {
        if (v[i]->getCountVertex() >= result.size()) {
            result.resize(v[i]->getCountVertex() + 1);
        }
        if (v[i]->getCountFacets() >= result[v[i]->getCountVertex()].size()) {
            result[v[i]->getCountVertex()].resize(v[i]->getCountFacets() + 1);
        }
        if (v[i]->getCountVertex() == 0 && v[i]->getCountFacets() == 0)
            std::cout << i << " ";
        result[v[i]->getCountVertex()][v[i]->getCountFacets()]++;
    }

    std::vector<std::string> table(1, "0");
    std::vector<std::string> table_latex(1);

    int max_size = 0;
    for (unsigned int i = 1; i < result.size(); ++i) {
        if (max_size < result[i].size())
            max_size = result[i].size();
        table.emplace_back();
        table[i] += std::to_string(i);
        for (unsigned int j = 0; j < result[i].size(); ++j) {
            table[i] += "\t" + std::to_string(result[i][j]);
        }
    }
    for (unsigned int i = 1; i < max_size; ++i) {
        table[0] += "\t" + std::to_string(i);
    }


    std::ofstream file_result("tables/" + name_file);

    for (int i = 0; i < table.size(); ++i) {
        file_result << table[i] << std::endl;
    }

//    file_result << "latex:" << std::endl;
//    file_result << table_latex[0] << std::endl;
//    file_result << table_latex[1] << std::endl;
//    file_result << table_latex[2] << std::endl;

    file_result.close();

    return 0;
}