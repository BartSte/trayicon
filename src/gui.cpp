#include <gui.hpp>
#include <qmessagebox.h>
#include <qobject.h>
#include <spdlog/spdlog.h>

Gui::Gui(const QString command, const QString icon, QObject *parent)
    : QSystemTrayIcon(parent), command(command) {
  setIcon(QIcon(icon));
  setToolTip("Running command: " + command);
  setContextMenu(&menu);

  connect(this, &QSystemTrayIcon::activated, this, &Gui::on_activated);

  spdlog::info("Icon set to: {}", icon.toStdString());
  spdlog::info("Tooltip set to: {}", command.toStdString());
}

void Gui::show_start_message(int duration_ms) {
  showMessage("Start", toolTip(), QSystemTrayIcon::Information, duration_ms);
}

void Gui::on_activated(QSystemTrayIcon::ActivationReason reason) {
  if (reason == QSystemTrayIcon::Trigger) {
    spdlog::info("Icon clicked.");
    show_start_message();
  }
}
