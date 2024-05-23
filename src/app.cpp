#include <exceptions.hpp>
#include <QApplication>
#include <QIcon>
#include <app.hpp>
#include <iostream>
#include <qsystemtrayicon.h>
#include <spdlog/spdlog.h>
#include <version.h>

App::App(int &argc, char **argv)
    : QApplication(argc, argv),
      argc(argc),
      argv(argv),
      gui(),
      parser("trayicon",
             "Display an icon in the system tray to control your application") {
  setApplicationDisplayName("Tray Icon");
  setApplicationName("trayicon");
  setApplicationVersion("0.0.0");
  /*setWindowIcon(QIcon(":/icon.svg"));*/
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
    std::cout << parser.help();
    return 0;
  }

  check_tray_available();
  gui.show();
  return QApplication::exec();
}
