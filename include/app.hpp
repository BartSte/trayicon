#pragma once

#include <QApplication>
#include <trayicon.hpp>

class App : public QApplication {

  Q_OBJECT;

  TrayIcon gui;

 public:
  App(int &argc, char **argv);
  void show();
};
