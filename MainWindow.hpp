#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtCore>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osg/ref_ptr>
#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osg/StateSet>
#include <osgDB/ReadFile>
#include <osgGA/EventQueue>
#include <osgViewer/ViewerEventHandlers>

#include <QKeyEvent>
#include <QWheelEvent>

#include <Eigen/Dense>

#include "ui_MainWindowForm.h"
#include "VehicleUpdateCallback.hpp"
#include "AircraftPhysics.hpp"


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

    enum VehicleType {FIXEDWING, QUADCOPTER};
    enum FixedWingType {EMB312, EMB314, F16D, MQ9};
    enum QuadcopterType {PHANTOM};

    void set_pause_flag(bool pauseState);
//    void change_vehicle(VehicleType vehicleType);

public slots:
    void on_actionExit_triggered();
    void setup_osg_view();

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void on_pushButton_Reset_clicked();

    void on_pushButton_Pause_toggled(bool checked);

    void on_pushButton_clicked();

private:
    Ui::MainWindowForm *mainWindowUI;
    void timerEvent(QTimerEvent *)override;
    int simulationUpdateTimerId{0};

    void create_camera();
    void create_manipulator();
    void create_aircraft();
    void create_terrain();
    void create_timer();

    osgGA::EventQueue *getEventQueue() const;

    bool pauseFlag{true};
    float deltaTime{1/30.0};

    float initialGroundPlaneSize{10};
    AircraftPhysics physics{AircraftPhysics()};

    VehicleType vehicleType{VehicleType::FIXEDWING};
    FixedWingType fixedWingType{FixedWingType::EMB314};
    QuadcopterType quadcopterType{QuadcopterType::PHANTOM};

    osg::ref_ptr<osg::Node> aircraftModelNode;
    osg::ref_ptr<osg::Node> terrainModelNode;

    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osgGA::NodeTrackerManipulator> manipulator;

};
#endif
