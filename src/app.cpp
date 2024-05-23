#include <QApplication>
#include <QIcon>
#include <QString>
#include <app.hpp>
#include <exceptions.hpp>
#include <iostream>
#include <qsystemtrayicon.h>
#include <spdlog/spdlog.h>
#include <version.h>

std::string App::name = "trayicon";

std::string App::description =
    "Display an icon in the system tray to control your application";

App::App(int &argc, char **argv)
    : QApplication(argc, argv),
      argc(argc),
      argv(argv),
      gui(),
      parser(App::name, App::description) {
  setApplicationDisplayName(QString::fromStdString(App::name));
  setApplicationName(QString::fromStdString(App::name));
  setApplicationVersion(PROJECT_VERSION);
}

void App::check_tray_available() {
  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    std::string msg = "System tray not available";
    throw TrayIconException(msg);
  } else {
    spdlog::info("System tray available");
  }
}

int App::execute() {
  cxxopts::ParseResult opts = parser.parse(argc, argv);
  if (opts.count("help")) {
    std::cout << parser.help() << std::endl;
    return 0;

  } else if (opts.count("version")) {
    std::cout << "trayicon version: " << PROJECT_VERSION << std::endl;
    return 0;

  } else {
    check_tray_available();
    gui.show();
    return QApplication::exec();
  }
}
