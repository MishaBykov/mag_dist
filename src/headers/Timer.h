#include <utility>

//
// Created by misha on 05.06.19.
//

#ifndef MAG_DIST_TIMER_H
#define MAG_DIST_TIMER_H

#include <chrono>
#include <string>
#include <fstream>

using namespace std::chrono;

class Timer {

    std::string file_out;
    steady_clock::time_point timePointBegin = steady_clock::now();

public:
    explicit Timer(std::string file_out);
    ~Timer();
};


#endif //MAG_DIST_TIMER_H
