#pragma once

#include <cxxopts.hpp>
#include <string>

class Cli {
 private:
  int argc;
  char **argv;
  cxxopts::Options options;

 public:
  Cli(int argc, char *argv[], const std::string &program, const std::string &description);
  cxxopts::ParseResult parse();
  std::string help();
  static std::string join_args(const std::vector<std::string> &args);
};
