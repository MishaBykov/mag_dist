//
// Created by misha on 24.02.19.
//

#include <iostream>
#include <memory>
#include <utility>
#include <IncidenceMatrix.h>

#include <Polyhedron.h>

Polyhedron::Polyhedron() = default;
Polyhedron::Polyhedron(unsigned int dimension) : dimension(dimension) {}
Polyhedron::Polyhedron(unsigned int dimension, std::shared_ptr<IncidenceMatrix> incidenceMatrix){
    if( checkIncidenceMatrix(incidenceMatrix, dimension) ) {
        this->matrix = incidenceMatrix;
        this->dimension = dimension;
    }
}

std::shared_ptr<std::vector<Polyhedron>> Polyhedron::readFromFile(std::string file_name) {
    std::shared_ptr<std::vector<Polyhedron>> result = std::make_shared<std::vector<Polyhedron>>();
    std::ifstream file_in(file_name);

    if(!file_in.is_open()) {
        std::cout << "Файл[" << file_name << "] не может быть открыт" << std::endl;
        return nullptr;
    }

    while (!file_in.eof()) {
        result->push_back(*readFromStream(file_in));
    }

    file_in.close();

    return result;
}

std::shared_ptr<Polyhedron> Polyhedron::readFromStream(std::istream &i_stream) {
    unsigned int dimension;
    if (!i_stream.eof()) {
        try {
            i_stream >> dimension;
            i_stream.get();
        }
        catch (const std::invalid_argument &e) {
            std::cout << "Некоректный файл" << std::endl
                      << "(" << e.what() << ") нет размерности" << std::endl;
        }
        std::shared_ptr<IncidenceMatrix> m = std::make_shared<IncidenceMatrix>();
        m->readFromStream(i_stream);
        return std::make_shared<Polyhedron>(dimension, m);
    } else {
        std::cout << "[Polyhedron] Конец файла" << std::endl;
    }
    return nullptr;
}


void Polyhedron::printToStream(std::ostream& out_stream) {
        out_stream << dimension << std::endl;
        matrix->printToStream(out_stream);
}

void Polyhedron::printToFile(std::vector<Polyhedron> &incidenceMatrix, const std::string &file_name) {
    std::ofstream out_file(file_name);
    for (auto &i : incidenceMatrix) {
        i.printToStream(out_file);
    }
    out_file.close();
}

std::shared_ptr<Polyhedron> Polyhedron::getVertexFigure(unsigned int index_column) {
    return std::make_shared<Polyhedron>();
}

std::shared_ptr<Polyhedron> Polyhedron::getFacetIncidenceMatrix(unsigned int index_row) {
    std::shared_ptr<IncidenceMatrix> new_matrix = std::make_shared<IncidenceMatrix>();
    unsigned int new_dimension = dimension - 1;

    for (unsigned int i = 0; i < matrix->getCountRow(); ++i) {
        if (index_row != i){
            new_matrix->appendRow(matrix->getRow(i) & matrix->getRow(index_row));
        }
    }

    auto sum_columns = new_matrix->sumColumns();
    for (unsigned int i = 0; i < sum_columns.size(); ++i) {
        if (sum_columns[i] < new_dimension) {
            new_matrix->removeColumn(i);
        }
    }

    return std::make_shared<Polyhedron>(new_dimension, new_matrix);
}

std::shared_ptr<IncidenceMatrix> Polyhedron::getMatrix() {
    return matrix;
}

void Polyhedron::setMatrix(std::shared_ptr<IncidenceMatrix> new_matrix) {
    if( checkIncidenceMatrix( new_matrix, dimension ) )
        matrix = std::move(new_matrix);
    else
        std::cout << "new matrix no check" << std::endl;
}

bool Polyhedron::checkIncidenceMatrix(std::shared_ptr<IncidenceMatrix> incidenceMatrix, unsigned int dimension) {
    auto sum_columns = incidenceMatrix->sumColumns();
    auto sum_rows = incidenceMatrix->sumRows();

    unsigned long max_size, min_size;
    bool min_size_columns = sum_columns.size() < sum_rows.size();
    if( min_size_columns ) {
        min_size = sum_columns.size();
        max_size = sum_rows.size();
    }
    else {
        min_size = sum_rows.size();
        max_size = sum_columns.size();
    }

    for (int i = 0; i < min_size; ++i) {
        if( sum_columns[i] < dimension || sum_rows[i] < dimension )
            return false;
    }
    if( min_size_columns ) {
        for (unsigned long i = min_size; i < max_size; ++i) {
            if( sum_rows[i] < dimension )
                return false;
        }
    }
    else {
        for (unsigned long i = min_size; i < max_size; ++i) {
            if( sum_columns[i] < dimension )
                return false;
        }
    }

    return true;
}

unsigned int Polyhedron::getDimension() {
    return dimension;
}

bool Polyhedron::isIinitialized() {
    return bool(matrix);
}


