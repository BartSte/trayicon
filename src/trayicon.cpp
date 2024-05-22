#include <trayicon.hpp>

TrayIcon::TrayIcon(QObject *parent) : QSystemTrayIcon(parent) {
  /*setIcon(QIcon(":/icon.svg"));*/
  setToolTip("Some icon.");
}
