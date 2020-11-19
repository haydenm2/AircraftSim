#include "MainWindow.hpp"
#include "KeyboardCommandWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication application(argc, argv);

  MainWindow mainWindow;
  mainWindow.show();

  KeyboardCommandWindow keyboardCommandWindow;
  keyboardCommandWindow.show();

  return application.exec();
}
