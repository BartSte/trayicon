#include <QApplication>
#include <QIcon>
#include <app.hpp>
#include <spdlog/spdlog.h>

App::App(int &argc, char **argv) : QApplication(argc, argv) {
  setWindowIcon(QIcon(":/kmonad.svg"));
  setApplicationDisplayName("KMonad Tray Icon");
  setApplicationName("kmonadtray");
}

void App::show() { gui.show(); }
