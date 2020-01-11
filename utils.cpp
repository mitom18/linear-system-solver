//
// Created by tomanm10 on 05.12.2019.
//

#include <dirent.h>
#include <algorithm>

#include "utils.hpp"

std::ifstream FileReader::choose_file(std::ostream &ostream, std::istream &istream) {
    std::string chosen_file;
    bool is_read = false;
    while (!is_read) {
        print_files(ostream);
        istream >> chosen_file;
        std::vector<std::string> files = get_files();
        if (std::find(files.begin(), files.end(), chosen_file) != files.end()) {
            is_read = true;
        }
    }
    return read_file(chosen_file);
}

std::vector<std::string> FileReader::get_files() {
    std::vector<std::string> files;
    DIR* dirp = opendir(INPUTS_DIR);
    struct dirent * dp;
    while ((dp = readdir(dirp)) != nullptr) {
        std::string file(dp->d_name);
        if (file.substr(0, 1) != ".") {
            files.push_back(file);
        }
    }
    closedir(dirp);

    return files;
}

void FileReader::print_files(std::ostream &ostream) {
    ostream << "Files to choose from (write the file name with .txt as well):" << std::endl;
    for (auto &file : get_files()) {
        ostream << file << " ";
    }
    ostream << std::endl;
}

std::ifstream FileReader::read_file(std::string &file_name) {
    std::ifstream infile(INPUTS_DIR + file_name);
    return infile;
}
