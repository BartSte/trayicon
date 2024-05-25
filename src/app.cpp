#include <QApplication>
#include <QIcon>
#include <QString>
#include <app.hpp>
#include <cli.hpp>
#include <cxxopts.hpp>
#include <exceptions.hpp>
#include <iostream>
#include <qprocess.h>
#include <qsystemtrayicon.h>
#include <spdlog/spdlog.h>
#include <version.h>

std::string App::name = "trayicon";

std::string App::description =
    "Display an icon in the system tray to control your application";

/**
 * @brief Constructor.
 *
 * @param argc number of arguments
 * @param argv array of arguments
 */
App::App(int &argc, char **argv)
    : QApplication(argc, argv),
      cli(argc, argv, App::name, App::description),
      gui(),
      process(std::make_unique<QProcess>()) {
  setApplicationDisplayName(QString::fromStdString(App::name));
  setApplicationName(QString::fromStdString(App::name));
  setApplicationVersion(PROJECT_VERSION);
  connect_signals();
}

/**
 * @brief The QProcess signals are connected to the QApplication, and vice
 * versa, such that they both quit when the other quits.
 */
void App::connect_signals() {
  connect(process.get(), &QProcess::started,
          [&]() { spdlog::info("Process started"); });

  connect(process.get(), &QProcess::finished,
          [&](int exit_code, QProcess::ExitStatus status) {
            spdlog::info("Process finished with exit code: {}", exit_code);
            QApplication::quit();
          });

  connect(process.get(), &QProcess::errorOccurred,
          [&](QProcess::ProcessError error) {
            std::string msg = error_to_string(error);
            spdlog::error("Process error occurred with message: {}", msg);
            QApplication::quit();
          });

  connect(this, &QApplication::aboutToQuit, [&]() {
    spdlog::info("Application is about to quit");
    process->kill();
  });
}

/**
 * @brief Converts a QProcess::ProcessError to a string.
 *
 * @param error the QProcess::ProcessError enum
 */
std::string App::error_to_string(QProcess::ProcessError error) {
  switch (error) {
  case QProcess::FailedToStart:
    return "Failed to start";
  case QProcess::Crashed:
    return "Crashed";
  case QProcess::Timedout:
    return "Timed out";
  case QProcess::WriteError:
    return "Write error";
  case QProcess::ReadError:
    return "Read error";
  case QProcess::UnknownError:
    return "Unknown error";
  default:
    return "Unknown error";
  }
}

/**
 * @brief Runs the application.
 *
 * @return exit code of the application
 */
int App::execute() {
  int exit_code = 0;
  cxxopts::ParseResult opts = cli.parse();

  set_logger(opts["loglevel"].as<std::string>());

  if (opts.count("help")) {
    print_help();

  } else if (opts.count("version")) {
    print_version();

  } else {
    check_command(opts);
    check_tray_available();
    gui.show();
    start_process(opts["command"].as<std::string>());

    spdlog::debug("Starting event loop");
    exit_code = QApplication::exec();
  }

  return exit_code;
}

/**
 * @brief Sets the logger level.
 *
 * @param log_level The log level to set
 */
void App::set_logger(std::string log_level) {
  spdlog::level::level_enum level = spdlog::level::from_str(log_level);
  spdlog::set_level(level);
}

/**
 * @brief The command on its validity.
 *
 * @param opts The parsed options
 */
void App::check_command(cxxopts::ParseResult opts) {
  if (opts.count("command")) {
    spdlog::info("Command to run: {}", opts["command"].as<std::string>());
  } else {
    throw TrayIconException("No command provided");
  }
}

/**
 * @brief Checks if the system tray is available.
 */
void App::check_tray_available() {
  if (QSystemTrayIcon::isSystemTrayAvailable()) {
    spdlog::info("System tray available");
  } else {
    spdlog::warn("System tray not available");
  }
}

/**
 * @brief Prints the help message to the standard output.
 */
void App::print_help() { std::cout << cli.help() << std::endl; }

/**
 * @brief Prints the version to the standard output.
 */
void App::print_version() {
  std::cout << "trayicon version: " << PROJECT_VERSION << std::endl;
}

/**
 * @brief Start the command as a process.
 *
 * @param command
 */
void App::start_process(std::string command) {
  process->setProgram(QString::fromStdString(command));
  spdlog::debug("Starting process: {}", command);
  process->start();
}
