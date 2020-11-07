#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <osgShadow/ShadowedScene>

class OutputWindow;

namespace Ui {
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionExit_triggered();
    void setupOsgView();
protected:
    void create_camera();
    void create_light();
    void create_shadowed_scene();
    void create_manipulator();

    osg::ref_ptr<osgShadow::ShadowedScene> shadowedScene;
    const int receivesShadowTraversalMask{0x1};
    const int castsShadowTraversalMask{0x2};

    Ui::MainWindowForm *mMainWindowUI;
    void create_geometry();
    void create_box();
    void create_sphere();
};

#endif // MAINWINDOW_H
