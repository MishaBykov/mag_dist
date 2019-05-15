//
// Created by misha on 12.05.19.
//

#ifndef MAG_DIST_LOGS_H
#define MAG_DIST_LOGS_H


#include <string>
#include <fstream>
#include <memory>

namespace Logs {

    void print(const std::string& log, const std::string& name_file) {
        std::ofstream file_log(name_file);
        file_log << log << std::endl;
        file_log.close();
    }
};

#endif //MAG_DIST_LOGS_H
