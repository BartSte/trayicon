#include <QApplication>
#include <QIcon>
#include <QMenu>
#include <QString>
#include <app.hpp>
#include <cli.hpp>
#include <cxxopts.hpp>
#include <exceptions.hpp>
#include <iostream>
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
    return "Unknown error";
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
      cli(argc, argv, App::name, App::description),
      gui(),
      menu(),
      process() {
  setApplicationDisplayName(QString::fromStdString(App::name));
  setApplicationName(QString::fromStdString(App::name));
  setApplicationVersion(PROJECT_VERSION);
  connect_signals();
  setup_signal_handlers();
}

/**
 * @brief The QProcess signals are connected to the QApplication, and vice
 * versa, such that they both quit when the other quits.
 */
void App::connect_signals() {
  auto log_started = [&]() { spdlog::info("Process started"); };
  auto log_finished = [&](int exit_code) {
    spdlog::info("Process finished");
    spdlog::debug("Process finished with code: {}", exit_code);
  };
  auto log_quit = [&]() { spdlog::info("Quitting application"); };
  auto log_error = [&](QProcess::ProcessError error) {
    spdlog::debug("Process error occurred that is expected since processes are "
                  "killed instead of terminated. Error: {}",
                  err2str(error));
  };

  connect(this, &QApplication::aboutToQuit, log_quit);
  connect(&process, &QProcess::errorOccurred, log_error);
  connect(&process, &QProcess::started, log_started);
  connect(&process, &QProcess::finished, log_finished);

  connect(&process, &QProcess::errorOccurred, this, QApplication::quit);
  connect(&process, &QProcess::finished, this, QApplication::quit);
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
 * @brief The command on its validity.
 *
 * @param opts The parsed options
 */
void App::check_command(const cxxopts::ParseResult &opts) {
  if (opts.count("program")) {
    spdlog::info("Command to run: {}", opts["program"].as<std::string>());
  } else {
    throw TrayIconException("No command provided");
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

void App::show_gui(const cxxopts::ParseResult &opts) {
  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    spdlog::error("System tray not available. Not showing GUI.");
    return;
  }

  menu.addAction("Quit", QApplication::quit);
  gui.setContextMenu(&menu);

  std::string icon_path = opts["icon"].as<std::string>();
  spdlog::debug("Icon path: {}", icon_path);
  gui.setIcon(QIcon(QString::fromStdString(icon_path)));

  std::string command = opts["program"].as<std::string>();
  gui.setToolTip(QString::fromStdString(command));

  gui.show();
}

/**
 * @brief Start the command as a process.
 *
 * @param command
 */
bool App::start_process(const std::string &program_,
                        const std::vector<std::string> &args_) {
  QString program = QString::fromStdString(program_);
  QStringList args;
  for (auto &arg : args_) {
    args << QString::fromStdString(arg);
  }

  process.setProgram(program);
  process.setArguments(args);
  spdlog::debug("Starting following command: {}{}",
                process.program().toStdString(),
                process.arguments().join(" ").toStdString());
  process.start();
  return process.waitForStarted();
  ;
}

bool App::stop_process() {
  if (process.state() == QProcess::NotRunning) {
    return true;
  }
  process.kill();
  return process.waitForFinished();
}

int App::run_command(const cxxopts::ParseResult &opts) {
  check_command(opts);

  int exit_code = 0;
  bool has_started = start_process(opts["program"].as<std::string>(),
                                   opts["args"].as<std::vector<std::string>>());
  if (!has_started) {
    spdlog::error("Process failed to start: {}", err2str(process.error()));
    return 1;
  }

  spdlog::debug("Process started, starting event loop");
  exit_code = QApplication::exec();

  if (!stop_process()) {
    spdlog::error("Process failed to finish: {}.", err2str(process.error()));
    return 1;
  }

  return exit_code;
}
