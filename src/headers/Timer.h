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

    explicit Timer(std::string file_out) : file_out(std::move(file_out)) {}
    ~Timer(){
        steady_clock::time_point timePointEnd = steady_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(timePointEnd - timePointBegin);

        std::ofstream stream_out(file_out);
        stream_out << "time work: " << time_span.count() << " seconds.";
        stream_out << std::endl;

    }

};


#endif //MAG_DIST_TIMER_H
