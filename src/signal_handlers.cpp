#include <QApplication>
#include <app.hpp>
#include <csignal>
#include <signal_handlers.hpp>
#include <spdlog/spdlog.h>

#if defined(_WIN32) || defined(_WIN64)

BOOL WINAPI handle_console(DWORD signal) {
  if (signal == CTRL_C_EVENT) {
    spdlog::info("CTRL_C_EVENT received");
    QCoreApplication *app = App::instance();
    if (app == nullptr) {
      spdlog::warn("QApplication is a nullptr.");
    } else {
      app->quit();
    }
    return TRUE;
  }
  return FALSE;
}

void setup_signal_handlers() { SetConsoleCtrlHandler(handle_console, TRUE); }

#else

/**
 * @brief sigintHandler
 *
 * Handle the SIGINT signal.
 *
 * @param signal An integer representing the signal.
 */
void handle_sigint(int signal) {
  if (signal == SIGINT) {
    spdlog::info("SIGINT received");
    QCoreApplication *app = App::instance();
    if (app == nullptr) {
      spdlog::warn("QApplication is a nullptr.");
    } else {
      app->quit();
    }
  }
}

void setup_signal_handlers() { signal(SIGINT, handle_sigint); }

#endif
