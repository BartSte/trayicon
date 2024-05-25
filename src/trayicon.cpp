#include <trayicon.hpp>

/**
 * @brief TODO:
 *
 * @param parent 
 */
TrayIcon::TrayIcon(QObject *parent) : QSystemTrayIcon(parent) {
  /*setIcon(QIcon(":/icon.svg"));*/
  setToolTip("Some icon.");
}
