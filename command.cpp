//
// Created by tomanm10 on 04.12.2019.
//

#include <iostream>

#include "command.hpp"
#include "matrix.hpp"
#include "system_solver.hpp"

Command CommandInterpreter::get_command(std::ostream &ostream, std::istream &istream) {
    ostream << "Enter command to execute..." << std::endl;
    istream >> std::ws; // clear the whitespaces that left in the stream
    std::string input;
    std::getline(istream, input);
    return str_to_command(input);
}

void CommandInterpreter::print_help(std::ostream &ostream) {
    ostream << "######################" << std::endl;
    ostream << "AVAILABLE COMMANDS" << std::endl;
    ostream << "######################" << std::endl;
    for (auto &i : command_list) {
        ostream << i.first << " - " << get_command_help(i.second) << std::endl;
    }
    ostream << "######################" << std::endl;
}

Command CommandInterpreter::str_to_command(const std::string &cmd) {
    try {
        return command_list.at(cmd);
    } catch (std::out_of_range &e) {
        return Command::UNKNOWN;
    }
}

std::string CommandInterpreter::get_command_help(const Command &cmd) {
    try {
        return command_descriptions.at(cmd);
    } catch (std::out_of_range &e) {
        return "";
    }
}

void CommandInterpreter::process_command(std::ostream &ostream, std::istream &istream, const Command &cmd) {
    if (cmd == Command::QUIT) {
        ostream << "Shutting down..." << std::endl;
    } else if (cmd == Command::HELP) {
        print_help(ostream);
    } else if (cmd == Command::CMD_INPUT) {
        try {
            Matrix matrix = MatrixCreator::parse_from_cmd_line(ostream, istream);
            SystemSolver::solve(ostream, matrix);
        } catch (std::exception &e) {
            ostream << "An exception occurred: " << e.what() << std::endl;
        }
    } else if (cmd == Command::TXT_INPUT) {
        try {
            Matrix matrix = MatrixCreator::parse_from_txt_file(ostream, istream);
            SystemSolver::solve(ostream, matrix);
        } catch (std::exception &e) {
            ostream << "An exception occurred: " << e.what() << std::endl;
        }
    } else if (cmd == Command::UNKNOWN) {
        ostream << "Unknown command entered" << std::endl;
    }
}

