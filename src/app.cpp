#include "gui.hpp"
#include <QApplication>
#include <QIcon>
#include <QMenu>
#include <QString>
#include <app.hpp>
#include <cli.hpp>
#include <cxxopts.hpp>
#include <exceptions.hpp>
#include <iostream>
#include <qcontainerfwd.h>
#include <qprocess.h>
#include <signal_handlers.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <version.h>

/**
 * @brief Converts a QProcess::ProcessError to a string.
 *
 * @param error the QProcess::ProcessError enum
 */
std::string err2str(QProcess::ProcessError error) {
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
    return "Unknown error code from QProcess";
  }
}

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
      last_command(""),
      process_restart(false),
      cli(argc, argv, App::name, App::description),
      process() {
  setApplicationDisplayName(QString::fromStdString(App::name));
  setApplicationName(QString::fromStdString(App::name));
  setApplicationVersion(PROJECT_VERSION);
  connect_logging_signals();
  connect_signals();
  setup_signal_handlers();
}

void App::connect_logging_signals() {
  auto log_started = [&]() { spdlog::debug("Process started"); };
  auto log_finished = [&](int exit_code) {
    spdlog::debug("Process finished. Restart is set to: {}", process_restart);
    spdlog::debug("Process exit code: {}", process.exitCode());
    spdlog::debug("Process error: {}", err2str(process.error()));
  };
  auto log_quit = [&]() { spdlog::debug("QApplication about to quit."); };
  auto log_error = [&](QProcess::ProcessError error) {
    spdlog::debug("Process error occurred that is expected since processes are "
                  "killed instead of terminated. Error: {}",
                  err2str(error));
  };

  connect(this, &App::aboutToQuit, log_quit);
  connect(&process, &QProcess::errorOccurred, log_error);
  connect(&process, &QProcess::started, log_started);
  connect(&process, &QProcess::finished, log_finished);
}

void App::connect_signals() {
  auto handle_finished = [&]() {
    if (!process_restart && !closingDown()) {
      quit();
    }
  };
  auto show_start_message = [&]() {
    if (gui) {
      gui->show_start_message();
    }
  };

  connect(&process, &QProcess::finished, handle_finished);
  connect(&process, &QProcess::errorOccurred, handle_finished);
  connect(&process, &QProcess::started, show_start_message);
  connect(this, &App::aboutToQuit, this, &App::stop_process);
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
    show_gui(opts);
    exit_code = run_command(opts);
  }

  spdlog::debug("Exiting with code: {}", exit_code);
  return exit_code;
}

/**
 * @brief Sets the logger level.
 *
 * @param log_level The log level to set
 */
void App::set_logger(const std::string &log_level) {
  spdlog::level::level_enum level = spdlog::level::from_str(log_level);
  spdlog::set_level(level);
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

void App::show_gui(const cxxopts::ParseResult &opts) {
  if (!Gui::isSystemTrayAvailable()) {
    spdlog::error("System tray not available. Not showing GUI.");
    return;
  }

  QString command = QString::fromStdString(opts["command"].as<std::string>());
  QString icon = QString::fromStdString(opts["icon"].as<std::string>());
  gui = std::make_unique<Gui>(command, icon, process, this);

  gui->contextMenu()->addAction("Restart", this, &App::restart_process);
  gui->contextMenu()->addAction("Quit", this, &App::quit);

  gui->show();
}

bool App::start_process(const std::string &command) {
  last_command = command;
  spdlog::info("Running command: {}", command);
  process.setProcessChannelMode(QProcess::ForwardedChannels);
  process.startCommand(QString::fromStdString(command));
  return process.waitForStarted();
}

bool App::stop_process() {
  process.kill();

  if (process.state() == QProcess::Running) {
    return process.waitForFinished();
  } else {
    return true;
  }
}

void App::restart_process() {
  process_restart = true;
  stop_process();
  start_process(last_command);
  process_restart = false;
}

int App::run_command(const cxxopts::ParseResult &opts) {
  if (start_process(opts["command"].as<std::string>())) {
    spdlog::debug("Starting event loop");
    return QApplication::exec();
  } else {
    spdlog::error("Process failed to start: {}", err2str(process.error()));
    return 1;
  }
}
