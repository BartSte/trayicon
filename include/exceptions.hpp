#pragma once

#include <exception>
#include <string>

class TrayIconException : public std::exception {
 private:
  std::string message;

 public:
  explicit TrayIconException(const std::string &msg);
  const char *what() const noexcept override;
};
