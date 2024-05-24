#include <QApplication>
#include <QIcon>
#include <QString>
#include <app.hpp>
#include <cli.hpp>
#include <cxxopts.hpp>
#include <exceptions.hpp>
#include <iostream>
#include <qsystemtrayicon.h>
#include <spdlog/spdlog.h>
#include <version.h>

std::string App::name = "trayicon";

std::string App::description =
    "Display an icon in the system tray to control your application";

App::App(int &argc, char **argv)
    : QApplication(argc, argv), argc(argc), argv(argv), gui() {
  setApplicationDisplayName(QString::fromStdString(App::name));
  setApplicationName(QString::fromStdString(App::name));
  setApplicationVersion(PROJECT_VERSION);
}

int App::execute() {
  cxxopts::Options parser = cli::make(App::name, App::description);
  cxxopts::ParseResult opts = parser.parse(argc, argv);
  if (opts.count("help")) {
    std::cout << parser.help() << std::endl;
    return 0;

  } else if (opts.count("version")) {
    std::cout << "trayicon version: " << PROJECT_VERSION << std::endl;
    return 0;

  } else {
    check_command(opts);
    check_tray_available();
    gui.show();
    std::string command = opts["command"].as<std::string>();
    system(command.c_str());
    return QApplication::exec();
  }
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
    throw TrayIconException("System tray not available");
  }
}
