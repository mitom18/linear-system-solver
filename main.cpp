//
// Created by tomanm10 on 23.11.2019.
//

#include <string>
#include <iostream>

#include "command.hpp"

int main(int argc, char** argv) {
    auto cmd_itp = new CommandInterpreter();
    cmd_itp->print_help(std::cout);
    Command cmd_to_process = Command::UNKNOWN;

    while(cmd_to_process != Command::QUIT) {
        cmd_to_process = cmd_itp->get_command(std::cout, std::cin);
        cmd_itp->process_command(std::cout, cmd_to_process);
    }
}