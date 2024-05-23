#pragma once

#include "cli.hpp"
#include <QApplication>
#include <trayicon.hpp>

class App : public QApplication {

  Q_OBJECT;

  int argc;
  char **argv;
  TrayIcon gui;
  ArgParse parser;

 public:
  App(int &argc, char **argv);
  void check_tray_available();
  int execute();
};
