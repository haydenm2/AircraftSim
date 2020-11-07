#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtCore>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>
#include <osg/Camera>
#include <osg/DisplaySettings>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osgDB/WriteFile>
#include <osgDB/ReadFile>
#include <osgGA/EventQueue>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>

#include <cassert>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>

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

    AircraftPhysics *get_physics_ptr();

    bool is_paused();
    void set_input_1(float newInput1);
    void set_input_2(float newInput2);
    void set_input_3(float newInput3);
    void set_input_4(float newInput4);
    void set_pause_flag(bool pauseState);
    void change_vehicle(VehicleType vehicleType);

public slots:
    void on_actionExit_triggered();
    void setupOsgView();

private:
    Ui::MainWindowForm *mMainWindowUI;
    void timerEvent(QTimerEvent *)override;
    int simulationUpdateTimerId{0};

    void create_camera();
    void create_manipulator();
    void create_aircraft();
    void create_terrain();
    void create_timer();

    osgGA::EventQueue *getEventQueue() const;

    bool pauseFlag{true};

    float initialGroundPlaneSize{10};
    osg::Vec3 initialAircraftPosition{0.f, 0.f, 0.f};
    osg::Quat osgToNEDRotation{0.f, 0.f, 0.7071, 0.7071};
    AircraftPhysics physics{AircraftPhysics()};

    VehicleType vehicleType{VehicleType::FIXEDWING};
    FixedWingType fixedWingType{FixedWingType::EMB314};
    QuadcopterType quadcopterType{QuadcopterType::PHANTOM};

    osg::ref_ptr<osg::Node> aircraftModelNode;
    osg::ref_ptr<osg::Node> terrainModelNode;

    osg::ref_ptr<osg::Group> mRoot;
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator;

};
#endif
