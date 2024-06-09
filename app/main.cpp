#include <app.hpp>
#include <exceptions.hpp>
#include <spdlog/spdlog.h>

/**
 * @brief entry point of the application. All errors that are not expected to
 * occur are logged as critical errors. Expected errors are logged as errors and
 * are typically thrown as TrayIconExceptions.
 *
 * @return int exit code of the application
 */
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

  spdlog::info("Exiting with code {}", exit_code);
  return exit_code;
}
