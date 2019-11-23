//
// Created by tomanm10 on 23.11.2019.
//

#include <string>
#include <iostream>

int main(int argc, char** argv) {
    std::string line;
    while(std::getline(std::cin, line)) {
        std::cout << line << '\n';
    }
}