//
// Created by tomanm10 on 23.11.2019.
//

#include <iostream>
#include <memory>

#include "command.hpp"

int main(int argc, char **argv) {
    auto cmd_itp = std::make_unique<CommandInterpreter>();
    cmd_itp->print_help(std::cout);
    Command cmd_to_process = Command::UNKNOWN;

    while (cmd_to_process != Command::QUIT) {
        cmd_to_process = cmd_itp->get_command(std::cout, std::cin);
        cmd_itp->process_command(std::cout, std::cin, cmd_to_process);
    }
}