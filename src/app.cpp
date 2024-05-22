#include "exceptions.hpp"
#include <QApplication>
#include <QIcon>
#include <app.hpp>
#include <qsystemtrayicon.h>
#include <spdlog/spdlog.h>

App::App(int &argc, char **argv) : QApplication(argc, argv) {
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
  check_tray_available();
  gui.show();
  return QApplication::exec();
}
