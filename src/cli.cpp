#include <cli.hpp>

#include <cxxopts.hpp>
#include <spdlog/spdlog.h>
#include <string>

#define DEFAULT cxxopts::value<std::string>()->default_value

Cli::Cli(int argc, char *argv[], std::string program, std::string description)
    : argc(argc), argv(argv), options(program, description) {

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
}

cxxopts::ParseResult Cli::parse() { return options.parse(argc, argv); }

std::string Cli::help() { return options.help(); }
