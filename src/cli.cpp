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
cxxopts::Options cli::make(std::string program, std::string description) {

  cxxopts::Options options(program, description);

  // clang-format off
  options.add_options()
    ("h,help", "Print help")

    ("v,version", "Returns the version number.")

    ("i,icon", "The icon to display.", DEFAULT("icon.svg"))

    ("l,loglevel", "Set the loglevel to CRITICAL, ERROR, WARNING, INFO, or DEBUG", 
      DEFAULT("warning"))

    ("command", "The command to run.", cxxopts::value<std::string>());
  // clang-format on

  options.parse_positional("command");

  return options;
}
