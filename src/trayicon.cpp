#include <trayicon.hpp>

TrayIcon::TrayIcon(QObject *parent) : QSystemTrayIcon(parent) {
  setIcon(QIcon(":/kmonad.svg"));
  setToolTip("KMonad");
}
