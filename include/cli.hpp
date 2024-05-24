#pragma once

#include <cxxopts.hpp>
#include <string>

namespace cli {

cxxopts::Options make(std::string program, std::string description);

} // namespace cli
