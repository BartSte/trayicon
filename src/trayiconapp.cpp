#include <QApplication>
#include <spdlog/spdlog.h>
#include <trayiconapp.hpp>

TrayIconApp::TrayIconApp(int &argc, char **argv) : QApplication(argc, argv) {
  spdlog::info("Constructor called");
}

void TrayIconApp::foo() { spdlog::info("Foo called"); }
