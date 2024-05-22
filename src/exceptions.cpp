#include <exceptions.hpp>

TrayIconException::TrayIconException(const std::string &msg)
    : message(msg) {}

const char *TrayIconException::what() const noexcept {
  return message.c_str();
}
