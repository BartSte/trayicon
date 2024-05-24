#pragma once

#include <cxxopts.hpp>
#include <string>

class Cli {
 private:
  int argc;
  char **argv;
  cxxopts::Options options;

 public:
  Cli(int argc, char *argv[], std::string program, std::string description);
  cxxopts::ParseResult parse();
  std::string help();
};
