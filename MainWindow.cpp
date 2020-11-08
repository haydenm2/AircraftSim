#include <QMainWindow>

#include "MainWindow.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mMainWindowUI{new Ui::MainWindowForm},
    mRoot{new osg::Group},
    manipulator{new osgGA::NodeTrackerManipulator}
{
    mMainWindowUI->setupUi(this);
    QObject::connect(mMainWindowUI->osgWidget, &osgQOpenGLWidget::initialized, this, &MainWindow::setupOsgView);
}

MainWindow::~MainWindow()
{
    killTimer(simulationUpdateTimerId);
    delete mMainWindowUI;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::setupOsgView()
{
    create_camera();
    create_terrain();
    create_aircraft();
    create_manipulator();
    create_timer();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    QString keyString = event->text();
    const char* keyData = keyString.toLocal8Bit().data();
    if(*keyData == 'j')
    {
        aircraftPosition[1] += 1.0;
    }
    else if(*keyData == 'k')
    {
        aircraftPosition[0] -= 1.0;
    }
    else if(*keyData == 'l')
    {
        aircraftPosition[1] -= 1.0;
    }
    else if(*keyData == 'i')
    {
        aircraftPosition[0] += 1.0;
    }

    std::cout << "KEY PRESS: " << keyData << std::endl;
    mMainWindowUI->osgWidget->getOsgViewer()->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    QString keyString = event->text();
    const char* keyData = keyString.toLocal8Bit().data();
    std::cout << "KEY RELEASE: " << keyData << std::endl;
    mMainWindowUI->osgWidget->getOsgViewer()->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

osgGA::EventQueue* MainWindow::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mMainWindowUI->osgWidget->getOsgViewer()->getEventQueue();

    if(eventQueue)
        return eventQueue;
    else
        throw std::runtime_error("Unable to obtain valid event queue");
}

void MainWindow::timerEvent(QTimerEvent *)
{
    mMainWindowUI->osgWidget->getOsgViewer()->frame();
}

void MainWindow::create_timer()
{
    double framesPerSecond{30};
    double timeStep{1.0/framesPerSecond};
    double timerDurationInMilliSeconds{timeStep * 1000};
    simulationUpdateTimerId=startTimer(timerDurationInMilliSeconds);
}

void MainWindow::create_camera()
{
    float aspectRatio = static_cast<float>(this->width())/static_cast<float>(this->height());
    auto pixelRatio = this->devicePixelRatio();
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->setClearColor(osg::Vec4(0.529f, 0.808f, 0.922f, 0.7f));
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->setProjectionMatrixAsPerspective(45.f, aspectRatio, 1.f, 1000.f);
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->setViewMatrixAsLookAt(osg::Vec3d(0.0,-20.0,3.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
}

void MainWindow::create_manipulator()
{
    osg::Vec3 initialPosition{-15.0, 0.0, 5.0};
    osg::Vec3 initialPointingPosition{0, 0, 0};
    osg::Vec3 upVector{0,0,1};
    osgGA::NodeTrackerManipulator::TrackerMode track_mode{osgGA::NodeTrackerManipulator::NODE_CENTER};
    manipulator->setTrackerMode(track_mode);
    osgGA::NodeTrackerManipulator::RotationMode rot_mode{osgGA::NodeTrackerManipulator::TRACKBALL};
    manipulator->setRotationMode(rot_mode);
    manipulator->setTrackNode(aircraftModelNode);
    manipulator->setAllowThrow(false);
    manipulator->setHomePosition(initialPosition, initialPointingPosition, upVector);
    mMainWindowUI->osgWidget->getOsgViewer()->setCameraManipulator(manipulator);
    mMainWindowUI->osgWidget->getOsgViewer()->setSceneData(this->mRoot.get());
}

void MainWindow::create_aircraft()
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
    transformAircraft->setUpdateCallback(new VehicleUpdateCallback(&aircraftPosition));
    transformAircraft->addChild(aircraftModelNode);

    this->mRoot->addChild(transformAircraft);

    manipulator->setNode(aircraftModelNode);
}

void MainWindow::create_terrain()
{
    terrainModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/terrain/city/Amaryllis_City.3ds");
    if (!terrainModelNode)
        std::cout << "Problem opening terrain model" << std::endl;

    osg::StateSet *stateSetTerrain = terrainModelNode->getOrCreateStateSet();
    stateSetTerrain->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    this->mRoot->addChild(terrainModelNode);
}

void MainWindow::change_vehicle(VehicleType vehicleType)
{
}


AircraftPhysics *MainWindow::get_physics_ptr()
{
}

bool MainWindow::is_paused()
{
}

void MainWindow::set_input_1(float newInput1)
{
}

void MainWindow::set_input_2(float newInput2)
{
}

void MainWindow::set_input_3(float newInput3)
{
}

void MainWindow::set_input_4(float newInput4)
{
}

void MainWindow::set_pause_flag(bool pauseState)
{
}

