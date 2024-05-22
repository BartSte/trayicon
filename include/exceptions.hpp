#pragma once

#include <exception>
#include <string>

class KMonadTrayException : public std::exception {
 private:
  std::string message;

 public:
  explicit KMonadTrayException(const std::string &msg);
  const char *what() const noexcept override;
};
