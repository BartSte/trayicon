#pragma once

#include <QApplication>
#include <cli.hpp>
#include <trayicon.hpp>

class App : public QApplication {

 private:
  Q_OBJECT;

  int argc;
  char **argv;
  TrayIcon gui;

  static std::string name;
  static std::string description;
  void check_command(cxxopts::ParseResult opts);
  void check_tray_available();

 public:
  App(int &argc, char **argv);
  int execute();
};
