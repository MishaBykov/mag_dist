//
// Created by misha on 05.06.19.
//

#include <Timer.h>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

Timer::Timer(std::string file_out) : file_out(std::move(file_out)) {}

Timer::~Timer(){
    steady_clock::time_point timePointEnd = steady_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(timePointEnd - timePointBegin);

    std::ofstream stream_out(file_out);
    stream_out << "time work: " << time_span.count() << " seconds.";
    stream_out << std::endl;
}