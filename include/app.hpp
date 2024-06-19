#pragma once

#include <QApplication>
#include <memory>
#include <qprocess.h>

#include <cli.hpp>
#include <gui.hpp>

/**
 * @class App
 * @brief Main application class that handles the execution of the application.
 *
 */
class App : public QApplication {

 private:
  Q_OBJECT;

  std::string last_command;
  bool process_restart;
  Cli cli;
  QProcess process;
  std::unique_ptr<Gui> gui;

  void connect_logging_signals();
  void connect_signals();
  void set_logger(const std::string &log_level);
  void print_help();
  void print_version();
  void show_gui(const cxxopts::ParseResult &opts);
  int run_command(const cxxopts::ParseResult &opts);
  bool start_process(const std::string &command);
  bool stop_process();
  void restart_process();

 public:
  App(int &argc, char **argv);
  int execute();
};
