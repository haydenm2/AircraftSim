#include "OSGAircraftWidget.hpp"


OSGAircraftWidget::OSGAircraftWidget(QWidget *parent, Qt::WindowFlags flags):
    QOpenGLWidget{parent, flags},
    mGraphicsWindow{new osgViewer::GraphicsWindowEmbedded{this->x(),
                                                          this->y(),
                                                          this->width(),
                                                          this->height()}},
    mRoot{new osg::Group},
    mView{new osgViewer::View},
    mViewer{new osgViewer::CompositeViewer},
    camera{new osg::Camera},
    manipulator{new osgGA::TrackballManipulator}
{
    create_camera();
    create_manipulator();
    create_view();
    create_viewer();
    create_terrain();
    create_aircraft();
    configure_update();
}

OSGAircraftWidget::~OSGAircraftWidget()
{
    killTimer(simulationUpdateTimerId);
}

void OSGAircraftWidget::timerEvent(QTimerEvent *event)
{
    update();
}

void OSGAircraftWidget::paintEvent(QPaintEvent *)
{
    this->makeCurrent();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    this->paintGL();
    painter.end();
    this->doneCurrent();
}

void OSGAircraftWidget::paintGL()
{
    mViewer->frame();
}

void OSGAircraftWidget::resizeGL(int width, int height)
{
    this->getEventQueue()->windowResize(this->x(), this->y(), width, height);
    mGraphicsWindow->resized(this->x(), this->y(), width, height);
    this->on_resize(width, height);
}

void OSGAircraftWidget::on_resize(int width, int height)
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras(cameras);
    auto pixelRatio = this->devicePixelRatio();
    cameras[0]->setViewport(0, 0, width * pixelRatio, height * pixelRatio);
}

void OSGAircraftWidget::keyPressEvent(QKeyEvent *event)
{
    QString keyString = event->text();
    const char *keyData = keyString.toLocal8Bit().data();
    this->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGAircraftWidget::keyReleaseEvent(QKeyEvent *event)
{
    QString keyString = event->text();
    const char *keyData = keyString.toLocal8Bit().data();
    this->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGAircraftWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto pixelRatio = this->devicePixelRatio();
    this->getEventQueue()->mouseMotion(static_cast<float>(event->x()*pixelRatio),
                                       static_cast<float>(event->y()*pixelRatio));
}

void OSGAircraftWidget::mousePressEvent(QMouseEvent *event)
{
    auto pixelRatio = this->devicePixelRatio();
    unsigned int button = 0;

        switch(event->button())
        {
        case Qt::LeftButton:
            button = 1;
            break;

        case Qt::MiddleButton:
            button = 2;
            break;

        case Qt::RightButton:
            button = 3;
            break;

        default:
            break;
        }
    this->getEventQueue()->mouseButtonPress(static_cast<float>(event->x() * pixelRatio),
                                            static_cast<float>(event->y() * pixelRatio),
                                            button);
}

void OSGAircraftWidget::mouseReleaseEvent(QMouseEvent *event)
{
    auto pixelRatio = this->devicePixelRatio();
    unsigned int button = 0;

        switch(event->button())
        {
        case Qt::LeftButton:
            button = 1;
            break;

        case Qt::MiddleButton:
            button = 2;
            break;

        case Qt::RightButton:
            button = 3;
            break;

        default:
            break;
        }
    this->getEventQueue()->mouseButtonRelease(static_cast<float>(pixelRatio*event->x()),
                                              static_cast<float>(pixelRatio*event->y()),
                                              button);
}

void OSGAircraftWidget::wheelEvent(QWheelEvent *event)
{
    event->accept();
    int delta = event->delta();
    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
    this->getEventQueue()->mouseScroll(motion);
}

osgGA::EventQueue *OSGAircraftWidget::getEventQueue() const
{
    osgGA::EventQueue *eventQueue = mGraphicsWindow->getEventQueue();

    if(eventQueue)
    {
        return eventQueue;
    }
    else
    {
        throw std::runtime_error("Unable to obtain valid event queue");
    }
}

void OSGAircraftWidget::create_camera()
{
    float aspectRatio = static_cast<float>(this->width())/static_cast<float>(this->height());
    auto pixelRatio = this->devicePixelRatio();
    camera->setViewport(0, 0, this->width()*pixelRatio, this->height()*pixelRatio);
    camera->setClearColor(osg::Vec4(0.529f, 0.808f, 0.922f, 0.7f));
    camera->setProjectionMatrixAsPerspective(45.f, aspectRatio, 1.f, 1000.f);
    camera->setGraphicsContext(this->mGraphicsWindow);
}

void OSGAircraftWidget::create_manipulator()
{
    osg::Vec3 initialPosition{-15.0, 0.0, 5.0};
    osg::Vec3 initialPointingPosition{0, 0, 0};
    osg::Vec3 upVector{0,0,1};
    manipulator->setAllowThrow(false);
    manipulator->setHomePosition(initialPosition, initialPointingPosition, upVector);
}

void OSGAircraftWidget::create_view()
{
    mView->setCamera(camera);
    mView->setSceneData(this->mRoot.get());
    mView->addEventHandler(new osgViewer::StatsHandler);
    mView->setCameraManipulator(manipulator);
}

void OSGAircraftWidget::create_viewer()
{
    mViewer->addView(mView);
    mViewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
    mViewer->realize();
    mView->home();
}

void OSGAircraftWidget::create_aircraft()
{
    if(vehicleType == VehicleType::FIXEDWING)
    {
        switch(fixedWingType)
        {
            case FixedWingType::EMB312:
                aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/EMB_312/EMB_312.obj");
                break;
            case FixedWingType::EMB314:
                aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/EMB_314/EMB_314.obj");
                break;
            case FixedWingType::F16D:
                aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/F-16D/F-16D.0bj");
                break;
            case FixedWingType::MQ9:
                aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/MQ-9/MQ-9.obj");
                break;
            default:
                aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/EMB_314/EMB_314.obj");
                break;
        }
    }
    else if(vehicleType == VehicleType::QUADCOPTER)
    {
        switch(quadcopterType)
        {
            case QuadcopterType::PHANTOM:
                aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/quadcopter/PHANTOM/Drone.obj");
                break;
            default:
                aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/quadcopter/PHANTOM/Drone.obj");
                break;
        }
    }

    if (!aircraftModelNode)
        std::cout << "Problem opening aircraft model" << std::endl;

    osg::StateSet *stateSetAircraft = aircraftModelNode->getOrCreateStateSet();
    stateSetAircraft->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    osg::PositionAttitudeTransform *transformAircraft = new osg::PositionAttitudeTransform;
    transformAircraft->setPosition(initialAircraftPosition);
    transformAircraft->setAttitude(osgToNEDRotation);
    transformAircraft->addChild(aircraftModelNode);

    this->mRoot->addChild(transformAircraft);
}

void OSGAircraftWidget::create_terrain()
{
    terrainModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/terrain/city/Amaryllis_City.3ds");
    if (!terrainModelNode)
        std::cout << "Problem opening terrain model" << std::endl;

    osg::StateSet *stateSetTerrain = terrainModelNode->getOrCreateStateSet();
    stateSetTerrain->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    this->mRoot->addChild(terrainModelNode);
}

void OSGAircraftWidget::configure_update()
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setMinimumSize(100, 100);
    this->setMouseTracking(true);

    this->update();

    double simulationUpdateTimeStep{1.0/this->framesPerSecond};
    double simulationTimerDurationInMilliSeconds{simulationUpdateTimeStep * 1000};
    this->simulationUpdateTimerId = startTimer(simulationTimerDurationInMilliSeconds);
}

void OSGAircraftWidget::change_vehicle(VehicleType vehicleType)
{
}


AircraftPhysics *OSGAircraftWidget::get_physics_ptr()
{
}

bool OSGAircraftWidget::is_paused()
{
}

void set_input_1(float newInput1)
{
}

void set_input_2(float newInput2)
{
}

void set_input_3(float newInput3)
{
}

void set_input_4(float newInput4)
{
}

void OSGAircraftWidget::set_pause_flag(bool pauseState)
{
}

