//
// Created by misha on 24.02.19.
//

#include <iostream>
#include <memory>
#include <utility>
#include <IncidenceMatrix.h>
#include <Polyhedron.h>

#include "Polyhedron.h"

Polyhedron::Polyhedron(unsigned int dimension) : dimension(dimension) {}

Polyhedron::Polyhedron(unsigned int dimension, const IncidenceMatrix &incidenceMatrix)
: dimension(dimension), matrix(incidenceMatrix) {}

std::vector<Polyhedron> Polyhedron::readFromFile(std::string file_name) {
    std::vector<Polyhedron> result;
    std::string buff;
    std::ifstream file_in(file_name);

    if(!file_in.is_open()) {
        std::cout << "Файл[" << file_name << "] не может быть открыт" << std::endl;
        return result;
    }

    while(getline(file_in, buff)) {
        if(!buff.empty()) {
            unsigned int dimension = 0;
            try {
                file_in >> dimension;
            }
            catch (const std::invalid_argument &e) {
                std::cout << "Некоректный файл" << std::endl
                          << "(" << e.what() << ") строка: " << buff << std::endl;
                break;
            }
            result.emplace_back(dimension);
            result.back().matrix.readFromFile(file_in);
        }
    }

    file_in.close();

    return result;
}

void Polyhedron::printToStream(std::ostream& out_stream) {
        out_stream << dimension << std::endl;
        matrix.printToStream(out_stream);
}

void Polyhedron::printToStream(std::vector<Polyhedron>& incidenceMatrix, const std::string &file_name) {
    std::ofstream out_stream(file_name);
    for (auto &i : incidenceMatrix) {
        i.printToStream(out_stream);
    }
}

Polyhedron Polyhedron::getVertexFigure(unsigned int index_column) {
    return Polyhedron(0);
}

Polyhedron Polyhedron::getFacet(unsigned int index_row) {
    IncidenceMatrix new_matrix = matrix;
    unsigned int new_dimension = dimension - 1;

    for (unsigned int i = 0; i < new_matrix.getCountRow(); ++i) {
        if (index_row != i){
            new_matrix.appendRow(matrix.getRow(i) & matrix.getRow(index_row));
        }
    }

    auto sum_columns = new_matrix.sumColumns();
    for (unsigned int i = 0; i < sum_columns.size(); ++i) {
        if (sum_columns[i] < new_dimension) {
            new_matrix.removeColumn(i);
        }
    }

    return Polyhedron(new_dimension, new_matrix);
}
