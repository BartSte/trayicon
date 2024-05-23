#pragma once

#include <cxxopts.hpp>
#include <string>

class ArgParse {

 public:
  ArgParse(std::string program, std::string description);
  cxxopts::ParseResult parse(int argc, char *argv[]);
  std::string help();

 private:
  cxxopts::Options options;
};
