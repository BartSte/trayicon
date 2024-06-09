#pragma once

#include <QApplication>
#include <QMenu>
#include <cli.hpp>
#include <qprocess.h>
#include <qsystemtrayicon.h>

/**
 * @class App
 * @brief Main application class that handles the execution of the application.
 *
 */
class App : public QApplication {

 private:
  Q_OBJECT;

  int pid;
  Cli cli;
  QSystemTrayIcon gui;
  QMenu menu;
  QProcess process;

  static std::string name;
  static std::string description;
  static std::string tooltip;

  void connect_signals();
  void check_command(const cxxopts::ParseResult &opts);
  void set_logger(const std::string &log_level);
  void print_help();
  void print_version();
  void show_gui(const cxxopts::ParseResult &opts);
  bool start_process(const std::vector<std::string> &command);
  void stop_process();
  int run_command(const cxxopts::ParseResult &opts);

 public:
  App(int &argc, char **argv);
  int execute();
};
