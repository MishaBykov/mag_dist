//
// Created by misha on 20.04.19.
//

#ifndef MAG_DIST_GENERATIONCOMBINATIONS_H
#define MAG_DIST_GENERATIONCOMBINATIONS_H


#include <vector>
#include <climits>
#include <iostream>

class GenerationCombinations {

    long long n = 0, k = 0;

    static std::vector<std::vector<long long> > SMALL_SC;

    std::vector<long long > combination;

    class InitSmallSc {
    public:
        InitSmallSc();
    };

    InitSmallSc initSmallSc;

public:

    GenerationCombinations(int n, int k);

    static std::vector<std::vector<long long> >& getSmallSc();

    std::vector<long long> getWhByNum (long long l);

    std::vector<long long> getC();

    bool nextCombination();

    void resetCombination();

};

#endif //MAG_DIST_GENERATIONCOMBINATIONS_H
