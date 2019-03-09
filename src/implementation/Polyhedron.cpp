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
: dimension(dimension), incidenceMatrix(incidenceMatrix) {}

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
            result.back().incidenceMatrix.readFromFile(file_in);
        }
    }

    file_in.close();

    return result;
}

//void Polyhedron::printToStream(std::vector<Polyhedron> vecrtorIncidenceMatrix, const std::string file_name) {
//    std::ofstream file_out(file_name);
//
//    if(!file_out.is_open()) {
//        std::cout << "Файл(" << file_name << ") не может быть открыт!" << std::endl;
//        return;
//    }
//
//    for (auto &i : vecrtorIncidenceMatrix) {
//        i.printToStream(file_out);
//    }
//
//    file_out.close();
//}

//std::vector<IncidenceMatrix> Polyhedron::readFromFile(std::string file_name) {
//    return std::vector<IncidenceMatrix>();
//}
