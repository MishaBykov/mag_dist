//
// Created by misha on 11.03.19.
//

#ifndef MAG_DIST_GENERATIONINCIDENCEMATRIX_H
#define MAG_DIST_GENERATIONINCIDENCEMATRIX_H

#include <vector>
#include <IncidenceMatrix.h>

class GenerationIncidenceMatrix {
    unsigned int max_row = 0;
    unsigned int max_column = 0;

    IncidenceMatrix base;
    IncidenceMatrix result;

    std::vector<bool> bits;

public:

    explicit GenerationIncidenceMatrix(IncidenceMatrix base, unsigned int max_row, unsigned int  max_column);
    ~GenerationIncidenceMatrix();

    bool next();

    IncidenceMatrix getResult();
};


#endif //MAG_DIST_GENERATIONINCIDENCEMATRIX_H
