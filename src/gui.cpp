#include <gui.hpp>
#include <qobject.h>
#include <qsystemtrayicon.h>
#include <spdlog/spdlog.h>

Gui::Gui(const QString command, const QString icon, const QProcess &process,
         QObject *parent)
    : QSystemTrayIcon(parent), command(command), process(process) {
  setIcon(QIcon(icon));
  setToolTip("Running command: " + command);
  setContextMenu(&menu);

  connect(this, &QSystemTrayIcon::activated, this, &Gui::on_activated);

  spdlog::info("Icon set to: {}", icon.toStdString());
  spdlog::info("Tooltip set to: {}", command.toStdString());
}

void Gui::show_start_message(int duration_ms, Gui::MessageIcon icon) {
  showMessage("Process started", toolTip(), icon, duration_ms);
}

void Gui::show_process_info(int duration_ms, Gui::MessageIcon icon) {
  QString info = "PID: " + QString::number(process.processId()) + "\n";
  info += "Program: " + process.program() + "\n";
  info += "Arguments: " + process.arguments().join(" ") + "\n";
  showMessage("Process info", info, icon, duration_ms);
}

void Gui::on_activated(Gui::ActivationReason reason) {
  if (reason == Gui::Trigger) {
    spdlog::info("Icon clicked.");
    show_process_info();
  }
}
