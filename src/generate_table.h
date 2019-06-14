//
// Created by misha on 08.06.2019.
//

#include <clocale>
#include <Polyhedron.h>
#include <iostream>
#include <vector>
#include <Checker.h>

int generate_table() {
    setlocale(LC_ALL, "rus");

    auto v = Polyhedron::readFromFile("result/d5 to d6/5d_to_6d_less14.txt");

    std::vector<std::vector<unsigned int>> result;

    for (unsigned int i = 0; i < v.size(); i++) {
        if (v[i]->getCountFacets() >= result.size()) {
            result.resize(v[i]->getCountFacets() + 1);
        }
        if (v[i]->getCountVertex() >= result[v[i]->getCountFacets()].size()) {
            result[v[i]->getCountFacets()].resize(v[i]->getCountVertex() + 1);
        }
        if (v[i]->getCountFacets() == 0 && v[i]->getCountVertex() == 0)
            std::cout << i << " ";
        result[v[i]->getCountFacets()][v[i]->getCountVertex()]++;
    }

    std::vector<std::string> table1;
    std::vector<std::string> table_latex1;
    std::vector<std::string> table2(3);
    std::vector<std::string> table_latex2(3);

    for (unsigned int i = 0; i < result.size(); ++i) {
        table1.emplace_back();
        table1[i] += std::to_string(i);
        for (unsigned int j = 0; j < result[i].size(); ++j) {
            table1[i] += "\t" + std::to_string(result[i][j]);
        }
    }
    for (unsigned int i = 0; i < result.size(); ++i) {
        table_latex1.emplace_back();
        table_latex1[i] += std::to_string(i);
        for (unsigned int j = 0; j < result[i].size(); ++j) {
            table_latex1[i] += " & " + std::to_string(result[i][j]);
        }
    }

    for (unsigned int i = 0; i < result.size(); ++i) {
        for (unsigned int j = 0; j < result[i].size(); ++j) {
            if (result[i][j]) {
                table2[0] += std::to_string(i) + "\t";
                table2[1] += std::to_string(j) + "\t";
                table2[2] += std::to_string(result[i][j]) + "\t";

                table_latex2[0] += " & " + std::to_string(i);
                table_latex2[1] += " & " + std::to_string(j);
                table_latex2[2] += " & " + std::to_string(result[i][j]);
            }
        }
    }


    std::ofstream file_result("tables/5d_to_6d_less14.txt");
    file_result << "tables1:" << std::endl;
    for (int i = 0; i < table1.size(); ++i) {
        file_result << table1[i] << std::endl;
    }
    file_result << std::endl << "latex:" << std::endl;
    for (int i = 0; i < table_latex1.size(); ++i) {
        file_result << table_latex1[i] << std::endl;
    }
    file_result << std::endl;
    file_result << "tables2:" << std::endl;
    file_result << table2[0] << std::endl;
    file_result << table2[1] << std::endl;
    file_result << table2[2] << std::endl;
    file_result << std::endl;
    file_result << "latex2:" << std::endl;
    file_result << table_latex2[0] << std::endl;
    file_result << table_latex2[1] << std::endl;
    file_result << table_latex2[2] << std::endl;

    file_result.close();

    return 0;
}