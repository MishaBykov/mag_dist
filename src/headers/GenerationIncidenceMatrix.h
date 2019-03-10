//
// Created by misha on 11.03.19.
//

#ifndef MAG_DIST_GENERATIONINCIDENCEMATRIX_H
#define MAG_DIST_GENERATIONINCIDENCEMATRIX_H

#include <vector>
#include <IncidenceMatrix.h>

class GenerationIncidenceMatrix {
    unsigned int max_row, max_column;

    IncidenceMatrix base;

    IncidenceMatrix result;

    std::vector<bool> permutations;

public:
//    next();
};


#endif //MAG_DIST_GENERATIONINCIDENCEMATRIX_H
