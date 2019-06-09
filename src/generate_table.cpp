//
// Created by misha on 08.06.2019.
//

#include <clocale>
#include <Polyhedron.h>
#include <iostream>
#include <vector>

int main() {
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

    std::vector<std::string> table(3);
    std::vector<std::string> table_latex(3);

    for (unsigned int i = 0; i < result.size(); ++i) {
        for (unsigned int j = 0; j < result[i].size(); ++j) {
            if (result[i][j]) {
                table[0] += std::to_string(i) + "\t";
                table[1] += std::to_string(j) + "\t";
                table[2] += std::to_string(result[i][j]) + "\t";

                table_latex[0] += std::to_string(i) + " & ";
                table_latex[1] += std::to_string(j) + " & ";
                table_latex[2] += std::to_string(result[i][j]) + " & ";
            }
        }
    }


    std::ofstream file_result("tables/" + name_file);

    file_result << table[0] << std::endl;
    file_result << table[1] << std::endl;
    file_result << table[2] << std::endl << std::endl;

    file_result << "latex:" << std::endl;
    file_result << table_latex[0] << std::endl;
    file_result << table_latex[1] << std::endl;
    file_result << table_latex[2] << std::endl;

    file_result.close();

    return 0;
}