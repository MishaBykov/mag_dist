//
// Created by misha on 12.05.19.
//

#ifndef MAG_DIST_LOGS_H
#define MAG_DIST_LOGS_H


#include <string>
#include <fstream>
#include <memory>

class Logs {

    static std::ofstream file_log;

public:

    explicit Logs(const std::string& name_file);

    ~Logs();

    static void print(const std::string& log);
};

#endif //MAG_DIST_LOGS_H
