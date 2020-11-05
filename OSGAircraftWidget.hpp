#ifndef OSG_AIRCRAFT_WIDGET_HPP
#define OSG_AIRCRAFT_WIDGET_HPP

#include "VehicleUpdateCallback.hpp"

#include <cassert>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>
#include <QOpenGLWidget>

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
#include <osg/LineWidth>

class OSGAircraftWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OSGAircraftWidget( QWidget* parent = 0,
         Qt::WindowFlags f = 0 );

    virtual ~OSGAircraftWidget();

    enum VehicleType {FIXEDWING, QUADCOPTER};
    enum FixedWingType {EMB312, EMB314, F16D, MQ9};
    enum QuadcopterType {PHANTOM};

    AircraftPhysics* get_physics_ptr();

    bool is_paused();
    void set_input_1(float newInput1);
    void set_input_2(float newInput2);
    void set_input_3(float newInput3);
    void set_input_4(float newInput4);
    void set_pause_flag(bool pauseState);

protected:
    virtual void paintEvent( QPaintEvent* paintEvent );
    virtual void paintGL();
    virtual void resizeGL( int width, int height );

    void timerEvent(QTimerEvent *);

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);

    void create_camera();
    void create_manipulator();
    void create_view();
    void create_viewer();
    void create_aircraft();
    void change_aircraft(int type);
    void create_ground_plane();
    void configure_update();

    float initialGroundPlaneSize{10};
    AircraftPhysics physics{AircraftPhysics()};

    bool pauseFlag{true};
    VehicleType vehicleType{VehicleType::FIXEDWING};
    FixedWingType fixedWingType{FixedWingType::EMB314};
    QuadcopterType quadcopterType{QuadcopterType::PHANTOM};

private:
    virtual void on_resize( int width, int height );
    osgGA::EventQueue* getEventQueue() const;

    int simulationUpdateTimerId{0};
    double framesPerSecond{30};

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
    osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
    osg::ref_ptr<osgViewer::View> mView;
    osg::ref_ptr<osg::Group> mRoot;
    osg::Camera* camera;
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator;
};

#endif
