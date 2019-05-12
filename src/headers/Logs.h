//
// Created by misha on 12.05.19.
//

#ifndef MAG_DIST_LOGS_H
#define MAG_DIST_LOGS_H


#include <string>
#include <fstream>
#include <memory>

namespace Logs {
    static std::ofstream file_log("log.txt");

    template <typename T>
    void print(const T log) {
        file_log << log << std::endl;
    }


}

#endif //MAG_DIST_LOGS_H
