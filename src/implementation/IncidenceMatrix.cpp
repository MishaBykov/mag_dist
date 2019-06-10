//
// Created by misha on 11.10.18.
//

#include <IncidenceMatrix.h>

#include <algorithm>
#include <iostream>

void IncidenceMatrix::updateCountColumn() {
    if (matrix.empty()){
        return;
    }
    unsigned long max_row = *std::max_element(matrix.begin(), matrix.end());
    for (count_column = 0; max_row != 0; max_row >>= 1u, count_column++);
}

unsigned long IncidenceMatrix::stringToRow(const std::string& row) {
    return row.empty() ? 0 : std::stoull(row, nullptr, 2);
}

std::vector<bool> IncidenceMatrix::stringToColumn(std::string row) {
    std::vector<bool> result(row.size());
    for (int i = 0; i < row.size(); ++i) {
        result[i] = row[i] - '0';
    }
    return result;
}

void IncidenceMatrix::appendRow(unsigned long new_row) {
    sorted = false;
    bliss_canon_f = false;
    matrix.push_back(new_row);
    updateCountColumn();
}

void IncidenceMatrix::appendRow(const std::string& new_str_row) {
    appendRow(stringToRow(new_str_row));
}

unsigned long IncidenceMatrix::getRow(unsigned int index) {
    if(matrix.size() > index)
        return matrix[index];
    return 0;
}

unsigned int IncidenceMatrix::getCountRow() {
    return static_cast<unsigned int>(matrix.size());
}

unsigned int IncidenceMatrix::getCountColumn() {
    return count_column;
}

void IncidenceMatrix::appendColumn(std::vector<bool> new_column) {
    sorted = false;
    bliss_canon_f = false;
    if (getCountRow() < new_column.size()) {
        matrix.resize(new_column.size());
    }
    count_column++;
    for(int i = 0; i < matrix.size(); ++i) {
        matrix[i] <<= 1u;
        matrix[i] += new_column[i];
    }
    updateCountColumn();
}

void IncidenceMatrix::appendColumn(std::string new_str_column) {
    appendColumn(stringToColumn(std::move(new_str_column)));
}

void IncidenceMatrix::removeColumn(unsigned long index) {
    sorted = false;
    bliss_canon_f = false;
    auto right = (1u << index) - 1, left = ((1u << count_column) - 1) - ((1u << (index + 1)) - 1);
    for(unsigned long &i : matrix){
        i = ((left & i) >> 1u) + (right & i);
    }
    updateCountColumn();
}

void IncidenceMatrix::printToStream(std::ostream &o_stream) {
    if ( getCountColumn() == 0 || getCountRow() == 0){
        o_stream << "IncidenceMatrix empty" << std::endl << std::endl;
        return;
    }
    for (unsigned long row : matrix) {
        std::string buf;
        for (int j = 0; j < count_column; j++){
            buf.push_back((row & 1u) ? '1' : '0');
            row >>= 1u;
        }
        std::reverse(buf.begin(), buf.end());
        o_stream << buf << std::endl;
    }
    o_stream << std::endl;
}

std::vector<bool> IncidenceMatrix::getColumn(unsigned int index) {
    std::vector<bool> result;
    unsigned long bit = static_cast<unsigned long>(1) << index;
    result.reserve(matrix.size());
    for (unsigned long i : matrix) {
        result.push_back(bool(i & bit));
    }
    return result;
}

void IncidenceMatrix::removeRow(unsigned long index) {
    bliss_canon_f = false;
    matrix.erase(matrix.begin() + index);
    updateCountColumn();
}

std::vector<unsigned long> IncidenceMatrix::sumRows() {
    std::vector<unsigned long> result(getCountRow());
    for (int i = 0; i < matrix.size(); ++i) {
        for (unsigned long m = matrix[i]; m != 0; m >>= 1u) {
            if (m & 1u)
                result[i]++;
        }
    }
    return result;
}

std::vector<unsigned long> IncidenceMatrix::sumColumns() {
    std::vector<unsigned long> result(getCountColumn());
    for (unsigned long m : matrix) {
        for (int i = 0; m != 0; i++, m >>= 1u) {
            if (m & 1u)
                result[i]++;
        }
    }
    return result;
}

void IncidenceMatrix::setColumn(unsigned long index, std::vector<bool> new_value) {
    if (index >= getCountColumn()){
        std::cout << "[setColumn] "<< index << " за пределами" << std::endl;
        return;
    }
    sorted = false;
    bliss_canon_f = false;
    unsigned long bit = 1;
    bit <<= index;
    for (int i = 0; i < matrix.size(); ++i) {
        if (new_value[i] != (bit && matrix[i])){
            if (bit && matrix[i]){
                matrix[i] -= bit;
            }
            if (new_value[i]){
                matrix[i] += bit;
            }
        }

    }
    updateCountColumn();
}

void IncidenceMatrix::setColumn(unsigned long index, std::string new_value) {
    if (index >= getCountRow()){
        std::cout << "[setColumn] "<< index << " за пределами" << std::endl;
        return;
    }
    setColumn(index, stringToColumn(std::move(new_value)));
}

void IncidenceMatrix::setRow(unsigned int index, unsigned long new_value) {
    sorted = false;
    bliss_canon_f = false;
    if (index >= getCountRow()){
        std::cout << "[setRow] "<< index << " за пределами" << std::endl;
        return;
    }
    matrix[index] = new_value;
    updateCountColumn();
}

void IncidenceMatrix::setRow(unsigned int index, const std::string& new_value) {
    setRow(index, stringToRow(new_value));
}

IncidenceMatrixSPtr IncidenceMatrix::readFromStream(std::istream &i_stream) {
    if (!i_stream.eof()) {
        std::shared_ptr<IncidenceMatrix> result = std::make_shared<IncidenceMatrix>();
        do {
            std::string buff;
            std::getline(i_stream, buff);
            if( buff.empty() )
                break;
            try {
                result->appendRow(buff);
            }
            catch (const std::invalid_argument &e) {
                std::cout << "Некоректный файл" << std::endl
                          << "(" << e.what() << ") строка: " << buff << std::endl;
                break;
            }

        } while (!i_stream.eof());
        return result;
    } else {
        std::cout << "[IncidenceMatrix] Конец файла" << std::endl;
    }
    return nullptr;
}

unsigned long IncidenceMatrix::size() {
    return getCountColumn() * getCountRow();
}

void IncidenceMatrix::transpose() {
    matrix = getTransposeMatrix();
    updateCountColumn();
    sorted = false;
    bliss_canon_f = false;
}

std::vector<unsigned long> IncidenceMatrix::getTransposeMatrix() {
    std::vector<unsigned long> result;
    for (unsigned int i = 0; i < getCountColumn(); ++i) {
        result.push_back(stringToRow(columnToString(getColumn(i))));
    }

    return result;
}

std::string IncidenceMatrix::columnToString(const std::vector<bool>& column) {
    std::string result;

    for (auto &&i : column) {
        result.push_back(i ? '1' : '0');
    }

    return result;
}

void IncidenceMatrix::clear() {
    matrix.clear();
    count_column = 0;
    bliss_canon_f = false;
    sorted = false;
}

void IncidenceMatrix::sort() {
    if( !sorted ) {
        sorted = true;
        std::sort(matrix.rbegin(), matrix.rend());
    }
}

int IncidenceMatrix::getCountOne() {
    int result = 0;
    auto s_r = sumRows();
    for (unsigned long i : s_r) {
        result += i;
    }
    return result;
}

void IncidenceMatrix::appendRow(const std::vector<bool>& new_row) {
    appendRow(columnToString(new_row));
}


void IncidenceMatrix::bliss_canon() {
    if( bliss_canon_f )
        return;

    bliss::Digraph g(count_column + matrix.size());
    bliss::Digraph::SplittingHeuristic shs_directed = bliss::Digraph::shs_fsm;
    g.set_splitting_heuristic(shs_directed);
    g.set_verbose_level(0);
    g.set_verbose_file(stdout);
    g.set_failure_recording(true);
    g.set_component_recursion(true);

// Copy data from matrix to the graph g
    unsigned int one = 1u << (count_column - 1u);
    for (int f = 0; f < matrix.size(); f++) {
        unsigned int row = matrix[f];
        for (int v = 0; v < count_column; v++, row <<= 1u) {
            if (row & one)
                g.add_edge(count_column + f, v);
        }
    }

    bliss::Stats stats;
// Canonical labeling
/* todo
    throw при
    1110
    1101
    1011
    0111
 */
    const unsigned int *cl = g.canonical_form(stats, nullptr, stdout);
// Permute to canonical labeling
    bliss::Digraph *cf = g.permute(cl);

    one = 1;
    for (int f = 0; f < matrix.size(); f++) {
        std::vector<unsigned int> *edges_out = &(cf->vertices[count_column + f].edges_out);
        int len = edges_out->size();
        unsigned int *vs = edges_out->data();
        matrix[f] = 0;
        for (int v = 0; v < len; v++) {
            matrix[f] |= one << vs[v];
        }
    }
    delete cf;
    delete cl;
    bliss_canon_f = true;
}

bool IncidenceMatrix::operator==(IncidenceMatrix &incidenceMatrix) {

    if( count_column != incidenceMatrix.count_column || matrix.size() != incidenceMatrix.matrix.size() )
        return false;

    bliss_canon();
    incidenceMatrix.bliss_canon();

    for (int i = 0; i < matrix.size(); ++i) {
        if( matrix[i] != incidenceMatrix.matrix[i])
            return false;
    }

    return true;
}
