//
// Created by misha on 07.04.19.
//

#include <GenerationCombinations.h>

GenerationCombinations::InitSmallSc::InitSmallSc() {
    unsigned long MAX_N = 25;
    unsigned long N = 24;
    unsigned long K = 24;

    SMALL_SC = std::vector<std::vector<long long > > (MAX_N, std::vector<long long >(MAX_N, 0));;

    for (int i = 0; i <= N; i++)
        SMALL_SC[i][0] = 1;
    for (int i = 1;  i <= N; i++) {
        for (int j = 1; j <= K; j++) {
            if (SMALL_SC[i - 1][j] + SMALL_SC[i - 1][j - 1] < 0) {
                SMALL_SC[i][j] = LLONG_MAX;
            } else {
                SMALL_SC[i][j] = SMALL_SC[i - 1][j] + SMALL_SC[i - 1][j - 1];
            }
        }
    }
}

GenerationCombinations::GenerationCombinations(int n, int k) : k(k), n(n) {
    combination.resize(static_cast<unsigned long>(k));
    resetCombination();
}

std::vector<std::vector<long long> >& GenerationCombinations::getSmallSc() {
    return SMALL_SC;
}

std::vector<long long> GenerationCombinations::getCombinationByNum(long long num){
    std::vector<long long > result;

    long long sc = n;
    long long ls = 0;

    for (int i = 1; i <= k; i++) {
        int j = 1;
        while (num >= SMALL_SC[sc - j][k - i]) {
            num -= SMALL_SC[sc - j][k - i];
            j++;
        }
        combination[i - 1] = (ls + j);
        ls += j;
        sc -= j;
    }

    return result;
}

std::vector<long long> GenerationCombinations::getC() {
    return combination;
}

bool GenerationCombinations::next(){
        for (long long i = k - 1; i >= 0; i--)
            if (combination[i] < n - k + i + 1) {
                combination[i]++;
                for (long long j = i + 1; j < k; j++)
                    combination[j] = combination[j-1]+1;
                return true;
            }
        resetCombination();
        return false;
}

void GenerationCombinations::resetCombination() {
    for( int i = 0; i < combination.size(); i++)
        combination[i] = i + 1;
}

std::vector<std::vector<long long> > GenerationCombinations::SMALL_SC;