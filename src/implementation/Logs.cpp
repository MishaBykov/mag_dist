//
// Created by misha on 12.05.19.
//

#include <Logs.h>
#include <iostream>

void Logs::print(const std::string& file_name, const std::string& log) {
    std::ofstream file_log(file_name);
    if (file_log.is_open()) {
        file_log << log << std::endl;
        file_log.close();
    } else {
        std::cout << "file:[" + file_name + "]" << std::endl;
    }
}
