#pragma once

#include <QSystemTrayIcon>
#include <qmenu.h>
#include <qobject.h>
#include <qprocess.h>

class Gui : public QSystemTrayIcon {
  Q_OBJECT

  const QString command;
  QMenu menu;
  const QProcess &process;

 public:
  explicit Gui(const QString command, const QString icon,
               const QProcess &process, QObject *parent = nullptr);

  void show_start_message(int duration_ms = 2000,
                          const Gui::MessageIcon icon = Gui::Information);

  void show_process_info(int duration_ms = 10000,
                         const Gui::MessageIcon icon = Gui::NoIcon);

  void on_activated(Gui::ActivationReason reason);
};
