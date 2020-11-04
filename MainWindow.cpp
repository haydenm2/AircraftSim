#include "MainWindow.hpp"
#include "ui_MainWindowForm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mMainWindowUI{new Ui::MainWindowForm}
{
    mMainWindowUI->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete mMainWindowUI;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
