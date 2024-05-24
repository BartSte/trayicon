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

void App::connect_signals() {
  connect(process.get(), &QProcess::started,
          [&]() { spdlog::info("Process started"); });

  connect(process.get(), &QProcess::finished,
          [&](int exit_code, QProcess::ExitStatus status) {
            spdlog::info("Process finished with exit code: {}", exit_code);
            QApplication::quit();
          });
}

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

void App::set_logger(std::string log_level) {
  spdlog::level::level_enum level = spdlog::level::from_str(log_level);
  spdlog::set_level(level);
}

void App::check_command(cxxopts::ParseResult opts) {
  if (opts.count("command")) {
    spdlog::info("Command to run: {}", opts["command"].as<std::string>());
  } else {
    throw TrayIconException("No command provided");
  }
}

void App::check_tray_available() {
  if (QSystemTrayIcon::isSystemTrayAvailable()) {
    spdlog::info("System tray available");
  } else {
    spdlog::warn("System tray not available");
  }
}

void App::print_help() { std::cout << cli.help() << std::endl; }

void App::print_version() {
  std::cout << "trayicon version: " << PROJECT_VERSION << std::endl;
}

void App::start_process(std::string command) {
  process->setProgram(QString::fromStdString(command));
  spdlog::debug("Starting process: {}", command);
  process->start();
}
