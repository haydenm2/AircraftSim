#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCore>

#include "OSGAircraftWidget.hpp"

namespace Ui {
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

private:
    Ui::MainWindowForm *mMainWindowUI;
};

#endif
