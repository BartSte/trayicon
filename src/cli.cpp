#include <cli.hpp>

#include <cxxopts.hpp>
#include <spdlog/spdlog.h>
#include <string>

#define DEFAULT cxxopts::value<std::string>()->default_value

/**
 * @brief Construct a new Arg Parse:: Arg Parse object
 *
 * @param argc The number of arguments
 * @param argv The arguments
 */
ArgParse::ArgParse(std::string program, std::string description)
    : options(program, description) {

  // clang-format off
  options.add_options()
    ("h,help", "Print help")

    ("v,version", "Returns the version number.")

    ("l,loglevel", "Set the loglevel to CRITICAL, ERROR, WARNING, INFO, or DEBUG", 
      DEFAULT("warning"));
  // clang-format on
}

/**
 * @brief Parse the arguments
 *
 * @return a cxxopts::ParseResult object
 */
cxxopts::ParseResult ArgParse::parse(int argc, char *argv[]) {
  return options.parse(argc, argv);
}

/**
 * @brief Get the help string
 *
 * @return The help string
 */
std::string ArgParse::help() { return options.help(); }
