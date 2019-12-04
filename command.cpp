//
// Created by tomanm10 on 04.12.2019.
//

#include <string>
#include <iostream>

#include "command.hpp"

Command CommandInterpreter::get_command(std::ostream &ostream, std::istream &istream) {
    std::string input;
    ostream << "Enter command to execute..." << std::endl;
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

void CommandInterpreter::process_command(std::ostream &ostream, const Command &cmd) {
    if (cmd == Command::QUIT) {
        ostream << "Shutting down..." << std::endl;
    } else if (cmd == Command::HELP) {
        print_help(ostream);
    } else if (cmd == Command::CMD_INPUT) {
        // TODO: cmd prompt input
        ostream << "todo cmd input" << std::endl;
    } else if (cmd == Command::TXT_INPUT) {
        // TODO: txt file input
        ostream << "todo txt input" << std::endl;
    }
}

