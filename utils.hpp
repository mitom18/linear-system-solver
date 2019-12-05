//
// Created by tomanm10 on 05.12.2019.
//

#ifndef LINEAR_SYSTEM_SOLVER_UTILS_HPP
#define LINEAR_SYSTEM_SOLVER_UTILS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class FileReader {
private:
    static std::vector<std::string> get_files();

    static void print_files(std::ostream &ostream);

    static std::ifstream read_file(std::string &file_name);
public:
    static const std::string INPUTS_DIR;

    static std::ifstream choose_file(std::ostream &ostream, std::istream &istream);
};

#endif //LINEAR_SYSTEM_SOLVER_UTILS_HPP
