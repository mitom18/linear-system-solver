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
    /**
     * @return vector of strings with names of files in directory set by constant INPUTS_DIR
     */
    static std::vector<std::string> get_files();

    /**
     * Prints names of all files in directory set by constant INPUTS_DIR.
     * @param ostream
     */
    static void print_files(std::ostream &ostream);

    /**
     * @param file_name
     * @return input stream from the file with the given name
     */
    static std::ifstream read_file(std::string &file_name);
public:
    /**
     * Constant representing directory in which all program txt file inputs are located.
     */
    static const std::string INPUTS_DIR;

    /**
     * Lets user choose from which file program should parse the linear system matrix.
     * @param ostream
     * @param istream
     * @return input stream from file that user chose
     */
    static std::ifstream choose_file(std::ostream &ostream, std::istream &istream);
};

#endif //LINEAR_SYSTEM_SOLVER_UTILS_HPP
