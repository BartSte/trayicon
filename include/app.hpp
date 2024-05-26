#pragma once

#include <QApplication>
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

  Cli cli;
  QSystemTrayIcon gui;
  std::unique_ptr<QProcess> process;

  static std::string name;
  static std::string description;
  static std::string tooltip;

  void connect_signals();
  std::string error_to_string(QProcess::ProcessError error);
  void check_command(cxxopts::ParseResult opts);
  void check_tray_available();
  void set_logger(std::string log_level);
  void print_help();
  void print_version();
  void show_gui(cxxopts::ParseResult opts);
  void start_process(std::string program_, std::vector<std::string> args_);

 public:
  App(int &argc, char **argv);
  int execute();
};
