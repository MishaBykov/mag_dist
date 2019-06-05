//
// Created by misha on 24.02.19.
//

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

#include <Polyhedron.h>
#include <IncidenceMatrix.h>

Polyhedron::Polyhedron() = default;
Polyhedron::Polyhedron(unsigned int dimension) : dimension(dimension) {}
Polyhedron::Polyhedron(unsigned int dimension, const std::shared_ptr<IncidenceMatrix>& incidenceMatrix) {
    if (checkIncidenceMatrix(incidenceMatrix, dimension)) {
        this->matrix = incidenceMatrix;
        this->dimension = dimension;
    }
}

Polyhedron::Polyhedron(unsigned int dimension, IncidenceMatrix incidenceMatrix){
    auto s_ptr_incidenceMatrix =  std::make_shared<IncidenceMatrix>(incidenceMatrix);
    if( checkIncidenceMatrix(s_ptr_incidenceMatrix, dimension) ) {
        this->matrix = s_ptr_incidenceMatrix;
        this->dimension = dimension;
    }
}

std::vector<PolyhedronSPtr> Polyhedron::readFromFile(const std::string& file_name) {
    std::vector<PolyhedronSPtr> result;
    std::ifstream file_in(file_name);

    if(!file_in.is_open()) {
        std::cout << "Файл [" << file_name << "] не может быть открыт" << std::endl;
        return result;
    }

    while (!file_in.eof()) {
        auto polyhedron = readFromStream(file_in);
        if( polyhedron )
            result.push_back( polyhedron );
        else {
            std::cout << "Файл [" << file_name << "] позиция: " << file_in.tellg() << std::endl;
        }
    }

    file_in.close();

    return result;
}

std::shared_ptr<Polyhedron> Polyhedron::readFromStream(std::istream &i_stream) {
    unsigned int dimension = 0;
    if (!i_stream.eof()) {
        if( !(i_stream >> dimension) ) {
            std::cout << "Некоректный файл: нет размерности" << std::endl;
            return nullptr;
        }
        i_stream.get();

        return std::make_shared<Polyhedron>(dimension, IncidenceMatrix::readFromStream(i_stream));
    } else {
        std::cout << "[Polyhedron] Конец файла" << std::endl;
    }
    return nullptr;
}


void Polyhedron::printToStream(std::ostream& out_stream) {
        out_stream << dimension << std::endl;
        matrix->printToStream(out_stream);
}

void Polyhedron::printToFile(std::vector<PolyhedronSPtr> &polyhedrons, const std::string &file_name) {
    std::ofstream out_file(file_name);
    for (auto &i : polyhedrons) {
        i->printToStream(out_file);
    }
    out_file.close();
}

std::shared_ptr<Polyhedron> Polyhedron::getVertexFigure(unsigned int index_column) {
    if( !matrix )
        return nullptr;

    std::shared_ptr<IncidenceMatrix> new_matrix = std::make_shared<IncidenceMatrix>();
    unsigned int new_dimension = dimension - 1;
    auto select_column = matrix->getColumn(index_column);
    for(unsigned int i = 0; i < select_column.size(); i++) {
        if (select_column[i]) {
            new_matrix->appendRow(matrix->getRow(i));
        }
    }

    new_matrix->removeColumn(index_column);

    new_matrix->transpose();

    new_matrix->sort();

    for (int i = 0; i < new_matrix->getCountRow(); ++i) {
        auto i_row = new_matrix->getRow(i);
        for (int j = i + 1; j < new_matrix->getCountRow(); j++) {
            auto j_row = new_matrix->getRow(j);
            if( ( i_row & j_row ) == j_row ) {
                new_matrix->removeRow(j);
                j--;
            }
        }
    }
    new_matrix->transpose();
    return std::make_shared<Polyhedron>(new_dimension, new_matrix);
}

std::shared_ptr<Polyhedron> Polyhedron::getPolyhedronFacet(unsigned int index_row) {
    if( !matrix )
        return nullptr;
    std::shared_ptr<IncidenceMatrix> new_matrix = std::make_shared<IncidenceMatrix>();
    unsigned int new_dimension = dimension - 1;
    unsigned long select_row = matrix->getRow(index_row);
    for(unsigned int i = 0; select_row != 0; select_row >>= 1u, i++){
        if( select_row & 1u ) {
            new_matrix->appendColumn(matrix->getColumn(i));
        }
    }
    new_matrix->removeRow(index_row);

    new_matrix->sort();
    for (int i = 0; i < new_matrix->getCountRow(); ++i) {
        auto i_row = new_matrix->getRow(i);
        for (int j = i + 1; j < new_matrix->getCountRow(); j++) {
            auto j_row = new_matrix->getRow(j);
            if( ( i_row & j_row ) == j_row ) {
                new_matrix->removeRow(j);
                j--;
            }
        }
    }
    return std::make_shared<Polyhedron>(new_dimension, new_matrix);
}

std::shared_ptr<IncidenceMatrix> Polyhedron::getMatrix() {
    if( !matrix )
        return nullptr;
    return matrix;
}

void Polyhedron::setMatrix(std::shared_ptr<IncidenceMatrix> new_matrix) {
    if( !matrix )
        return;
    if( checkIncidenceMatrix( new_matrix, dimension ) )
        matrix = std::move(new_matrix);
    else
        std::cout << "new matrix no check" << std::endl;
}

bool Polyhedron::checkIncidenceMatrix(const std::shared_ptr<IncidenceMatrix>& incidenceMatrix, unsigned int dimension) {
    if( !incidenceMatrix )
        return false;
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

    for (int i = 0; i < incidenceMatrix->getCountRow(); ++i) {
        auto i_row = incidenceMatrix->getRow(i);
        for (int j = 1; j < incidenceMatrix->getCountRow(); j++) {
            auto j_row = incidenceMatrix->getRow(j);
            if( i_row != j_row &&  (( i_row & j_row ) == j_row || ( i_row & j_row ) == i_row )) {
                return false;
            }
        }
    }

    return true;
}

unsigned int Polyhedron::getDimension() {
    return dimension;
}

bool Polyhedron::isInitialized() {
    return bool(matrix);
}

unsigned int Polyhedron::getCountFacets() {
    if( !matrix )
        return 0;
    return matrix->getCountRow();
}

unsigned int Polyhedron::getCountVertex() {
    if( !matrix )
        return 0;
    return matrix->getCountColumn();
}

unsigned int Polyhedron::getCountOne() {
    if( !matrix )
        return 0;
    return matrix->getCountOne();
}

bool Polyhedron::operator==(Polyhedron &polyhedron) {
    if (dimension != polyhedron.dimension)
        return false;
    return *matrix == *polyhedron.matrix;
}


