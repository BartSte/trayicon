#pragma once

#include <QSystemTrayIcon>
#include <qmenu.h>
#include <qmessagebox.h>
#include <qobject.h>

class Gui : public QSystemTrayIcon {
  Q_OBJECT

  QString command;
  QMenu menu;

 public:
  explicit Gui(const QString command, const QString icon,
               QObject *parent = nullptr);
  void show_start_message(int duration_ms = 2000);
  void on_activated(QSystemTrayIcon::ActivationReason reason);
};
