#include <QApplication>

class TrayIconApp : public QApplication {

  Q_OBJECT;

 public:
  TrayIconApp(int &argc, char **argv);
  void foo();
};
