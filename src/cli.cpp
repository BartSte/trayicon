#include <cli.hpp>
#include <cxxopts.hpp>
#include <string>

#define DEFAULT cxxopts::value<std::string>()->default_value

/**
 * @brief Constructor.
 *
 * @param argc number of arguments
 * @param argv array of arguments
 * @param program the name of the program
 * @param description a description of the program
 */
Cli::Cli(int argc, char *argv[], const std::string &program,
         const std::string &description)
    : argc(argc), argv(argv), options(program, description) {

  // clang-format off
  options.add_options()
    ("h,help", "Print help")

    ("v,version", "Returns the version number.")

    ("i,icon", "The icon to display.", DEFAULT(":/default.png"))

    ("l,loglevel", "Set the loglevel to CRITICAL, ERROR, WARNING, INFO, or DEBUG", 
      DEFAULT("warning"))

    ("command", "The command to run.", DEFAULT(""));
  // clang-format on

  options.parse_positional("command");
}

/**
 * @brief Wrapper for cxxopts::Options::parse().
 *
 * @return the result of the parse
 */
cxxopts::ParseResult Cli::parse() { return options.parse(argc, argv); }

/**
 * @brief Wrapper for cxxopts::Options::help().
 *
 * @return the help message
 */
std::string Cli::help() { return options.help(); }
