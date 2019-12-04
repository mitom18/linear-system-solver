//
// Created by tomanm10 on 04.12.2019.
//

#ifndef LINEAR_SYSTEM_SOLVER_COMMAND_HPP
#define LINEAR_SYSTEM_SOLVER_COMMAND_HPP

#include <string>
#include <map>

/**
 * Enumeration for all commands in the application.
 */
enum class Command {
    QUIT,
    HELP,
    CMD_INPUT,
    TXT_INPUT,
    UNKNOWN
};

/**
 * Class for working with commands.
 */
class CommandInterpreter {
private:
    std::map<std::string, Command> command_list{
            {"q",   Command::QUIT},
            {"h",   Command::HELP},
            {"cmd", Command::CMD_INPUT},
            {"txt", Command::TXT_INPUT}
    };

    std::map<Command, std::string> command_descriptions{
            {Command::QUIT, "shuts down the program"},
            {Command::HELP, "shows help"},
            {Command::CMD_INPUT, "selects input from command line"},
            {Command::TXT_INPUT, "selects input from text file"}
    };

    /**
     * Converts command string alias to Command enum field.
     * @param cmd
     * @return Command
     */
    Command str_to_command(const std::string &cmd);

    /**
     * Returns help for given Command enum field.
     * @param cmd
     * @return std::string
     */
    std::string get_command_help(const Command &cmd);
public:
    /**
     * Asks user for command alias and returns Command enum field for given alias.
     * @param ostream
     * @param istream
     * @return Command
     */
    Command get_command(std::ostream &ostream, std::istream &istream);

    /**
     * Processes the given Command enum field.
     * @param ostream
     * @param cmd
     */
    void process_command(std::ostream &ostream, const Command &cmd);

    /**
     * Prints program help.
     * @param ostream
     */
    void print_help(std::ostream &ostream);
};


#endif //LINEAR_SYSTEM_SOLVER_COMMAND_HPP
