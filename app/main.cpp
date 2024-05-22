#include "exceptions.hpp"
#include <app.hpp>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
  int exit_code = 1;
  try {
    App app(argc, argv);
    exit_code = app.execute();

  } catch (const TrayIconException &error) {
    spdlog::error(error.what());

  } catch (const std::exception &error) {
    spdlog::critical(error.what());

  } catch (...) {
    spdlog::critical("Unknown exception occurred");
  }
  return exit_code;
}
