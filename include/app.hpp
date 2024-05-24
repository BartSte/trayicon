#pragma once

#include <QApplication>
#include <cli.hpp>
#include <qprocess.h>
#include <trayicon.hpp>

class App : public QApplication {

 private:
  Q_OBJECT;

  Cli cli;
  TrayIcon gui;
  std::unique_ptr<QProcess> process;

  static std::string name;
  static std::string description;

  void connect_signals();
  void check_command(cxxopts::ParseResult opts);
  void check_tray_available();
  void set_logger(std::string log_level);
  void print_help();
  void print_version();
  void start_process(std::string command);

 public:
  App(int &argc, char **argv);
  int execute();
};
