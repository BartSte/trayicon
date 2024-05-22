#pragma once

#include <QSystemTrayIcon>

class TrayIcon : public QSystemTrayIcon {
  Q_OBJECT
 public:
  TrayIcon(QObject *parent = nullptr);
};
