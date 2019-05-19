//
// Created by misha on 12.05.19.
//

#include <Logs.h>

std::ofstream Logs::file_log;

Logs::Logs(const std::string& name_file) {
    file_log.open(name_file);
}

Logs::~Logs() {
    file_log.close();
}

void Logs::print(const std::string& log) {
    if (file_log.is_open())
        file_log << log << std::endl;
}
