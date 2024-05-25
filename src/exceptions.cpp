#include <exceptions.hpp>

/**
 * @brief Will be thrown when an error on our side occurs.
 *
 * @param msg
 */
TrayIconException::TrayIconException(const std::string &msg) : message(msg) {}

/**
 * @brief Returns the error message.
 *
 * @return error message
 */
const char *TrayIconException::what() const noexcept { return message.c_str(); }
