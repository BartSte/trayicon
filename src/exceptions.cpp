#include <exceptions.hpp>

KMonadTrayException::KMonadTrayException(const std::string &msg)
    : message(msg) {}

const char *KMonadTrayException::what() const noexcept {
  return message.c_str();
}
