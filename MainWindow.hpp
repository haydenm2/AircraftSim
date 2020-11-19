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
    enum TerrainType {WARZONE, CITY};

    void change_vehicle(FixedWingType type);
    void change_terrain(TerrainType type);

public slots:
    void on_actionExit_triggered();
    void on_actionEMB_312_triggered();
    void on_actionEMB_314_triggered();
    void on_actionF16_D_triggered();
    void on_actionMQ9_triggered();
    void on_actionWar_Zone_triggered();
    void on_actionCity_triggered();
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
    int physicsUpdateTimerId{1};

    void create_camera();
    void create_manipulator();
    void create_aircraft();
    void create_terrain();
    void create_timer();

    osgGA::EventQueue *getEventQueue() const;

    bool pauseFlag{true};
    float simulationFramesPerSecond{30.0};
    float physicsFramesPerSecond{100.0};

    float initialGroundPlaneSize{10};
    AircraftPhysics physics{AircraftPhysics()};

    TerrainType terrainType{TerrainType::CITY};
    VehicleType vehicleType{VehicleType::FIXEDWING};
    FixedWingType fixedWingType{FixedWingType::EMB314};
    QuadcopterType quadcopterType{QuadcopterType::PHANTOM};

    osg::ref_ptr<osg::Node> aircraftModelNode;
    osg::ref_ptr<osg::Node> terrainModelNode;
    osg::ref_ptr<osg::Node> warzoneTerrainModelNode;
    osg::ref_ptr<osg::Node> cityTerrainModelNode;

    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osgGA::NodeTrackerManipulator> manipulator;

};
#endif
