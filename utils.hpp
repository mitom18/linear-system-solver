//
// Created by tomanm10 on 05.12.2019.
//

#ifndef LINEAR_SYSTEM_SOLVER_UTILS_HPP
#define LINEAR_SYSTEM_SOLVER_UTILS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

/**
 * Constant representing directory in which all program txt file inputs are located.
 */
#define INPUTS_DIR "../inputs/"

class FileReader {
private:
    /**
     * @return vector of strings with names of files in directory set by constant INPUTS_DIR
     */
    static std::vector<std::string> get_files();

    /**
     * Prints names of all files in directory set by constant INPUTS_DIR.
     *
     * @param ostream output stream to write information to
     */
    static void print_files(std::ostream &ostream);

    /**
     * Opens the file with given file name and returns it as an input stream.
     *
     * @param file_name name of the file to be opened
     * @return input stream from the file with the given name
     */
    static std::ifstream read_file(std::string &file_name);

public:
    /**
     * Lets user choose from which file program should parse the matrix of the linear system.
     *
     * @param ostream output stream to write information to
     * @param istream input stream to read from
     * @return input stream from file that user chose
     */
    static std::ifstream choose_file(std::ostream &ostream, std::istream &istream);
};

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

#endif //LINEAR_SYSTEM_SOLVER_UTILS_HPP
