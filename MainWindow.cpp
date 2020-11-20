#include <QMainWindow>

#include "MainWindow.hpp"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mainWindowUI{new Ui::MainWindowForm},
    root{new osg::Group},
    manipulator{new osgGA::NodeTrackerManipulator}
{
    mainWindowUI->setupUi(this);
    QObject::connect(mainWindowUI->osgWidget, &osgQOpenGLWidget::initialized, this, &MainWindow::setup_osg_view);
}

MainWindow::~MainWindow()
{
    killTimer(simulationUpdateTimerId);
    killTimer(physicsUpdateTimerId);
    delete mainWindowUI;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionEMB_312_triggered()
{
    change_vehicle(FixedWing::FixedWingType::EMB312);
}

void MainWindow::on_actionEMB_314_triggered()
{
    change_vehicle(FixedWing::FixedWingType::EMB314);
}

void MainWindow::on_actionF16_D_triggered()
{
    change_vehicle(FixedWing::FixedWingType::F16D);
}

void MainWindow::on_actionMQ9_triggered()
{
    change_vehicle(FixedWing::FixedWingType::MQ9);
}

void MainWindow::on_actionWar_Zone_triggered()
{
    change_terrain(TerrainType::WARZONE);
}

void MainWindow::on_actionCity_triggered()
{
    change_terrain(TerrainType::CITY);
}

void MainWindow::on_actionMountains_triggered()
{
    change_terrain(TerrainType::MOUNTAINS);
}

void MainWindow::setup_osg_view()
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

    Eigen::Vector4f controlInputs{physics.get_aircraft_ptr()->get_control()};

    float deltaTheta{math_tools::degrees2Radians(1)};
    if(*keyData == 'j')
    {
        controlInputs[0] -= deltaTheta;
    }
    else if(*keyData == 'l')
    {
        controlInputs[0] += deltaTheta;
    }
    else if(*keyData == 'i')
    {
        controlInputs[1] -= deltaTheta;
    }
    else if(*keyData == 'k')
    {
        controlInputs[1] += deltaTheta;
    }
    else if(*keyData == 'a')
    {
        controlInputs[2] -= deltaTheta;
    }
    else if(*keyData == 'd')
    {
        controlInputs[2] += deltaTheta;
    }
    else if(*keyData == 'w')
    {
        controlInputs[3] += 0.05;
    }
    else if(*keyData == 's')
    {
        controlInputs[3] -= 0.05;
    }

    physics.set_control(controlInputs);

    mainWindowUI->osgWidget->getOsgViewer()->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

osgGA::EventQueue* MainWindow::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mainWindowUI->osgWidget->getOsgViewer()->getEventQueue();

    if(eventQueue)
        return eventQueue;
    else
        throw std::runtime_error("Unable to obtain valid event queue");
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(!pauseFlag)
    {
        if(event->timerId() == simulationUpdateTimerId)
            mainWindowUI->osgWidget->getOsgViewer()->frame();
        else if(event->timerId() == physicsUpdateTimerId)
            physics.update(1.0/physicsFramesPerSecond);
    }
}

void MainWindow::create_timer()
{
    double simulationTimeStep{1.0/simulationFramesPerSecond};
    double simulationTimerDurationInMilliSeconds{simulationTimeStep * 1000};
    simulationUpdateTimerId = startTimer(simulationTimerDurationInMilliSeconds);

    double physicsTimeStep{1.0/physicsFramesPerSecond};
    double physicsTimerDurationInMilliSeconds{physicsTimeStep * 1000};
    physicsUpdateTimerId = startTimer(physicsTimerDurationInMilliSeconds);
}

void MainWindow::create_camera()
{
    float aspectRatio = static_cast<float>(this->width())/static_cast<float>(this->height());
    auto pixelRatio = this->devicePixelRatio();
    mainWindowUI->osgWidget->getOsgViewer()->getCamera()->setClearColor(osg::Vec4(0.529f, 0.808f, 0.922f, 0.7f));
    mainWindowUI->osgWidget->getOsgViewer()->getCamera()->setProjectionMatrixAsPerspective(45.f, aspectRatio, 1.f, 1000.f);
    mainWindowUI->osgWidget->getOsgViewer()->getCamera()->setViewMatrixAsLookAt(osg::Vec3d(0.0,-20.0,3.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));
    mainWindowUI->osgWidget->getOsgViewer()->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    mainWindowUI->osgWidget->getOsgViewer()->getCamera()->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
}

void MainWindow::create_manipulator()
{
    osg::Vec3 initialPosition{0.0, 25.0, 5.0};
    osg::Vec3 initialPointingPosition{0, 0, 0};
    osg::Vec3 upVector{0,0,1};
    osgGA::NodeTrackerManipulator::TrackerMode track_mode{osgGA::NodeTrackerManipulator::NODE_CENTER_AND_ROTATION};
    manipulator->setTrackerMode(track_mode);
    osgGA::NodeTrackerManipulator::RotationMode rot_mode{osgGA::NodeTrackerManipulator::TRACKBALL};
    manipulator->setRotationMode(rot_mode);
    manipulator->setTrackNode(aircraftModelNode);
    manipulator->setAllowThrow(false);
    manipulator->setHomePosition(initialPosition, initialPointingPosition, upVector);
    mainWindowUI->osgWidget->getOsgViewer()->setCameraManipulator(manipulator);
    mainWindowUI->osgWidget->getOsgViewer()->setSceneData(this->root.get());
}

void MainWindow::create_aircraft()
{
    switch(fixedWingType)
    {
        case FixedWing::FixedWingType::EMB312:
            aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/EMB_312/EMB_312.obj");
            break;
        case FixedWing::FixedWingType::EMB314:
            aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/EMB_314/EMB_314.obj");
            break;
        case FixedWing::FixedWingType::F16D:
            aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/F-16D/F-16D.obj");
            break;
        case FixedWing::FixedWingType::MQ9:
            aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/MQ-9/MQ-9.obj");
            break;
        default:
            aircraftModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/fixedwing/EMB_314/EMB_314.obj");
            break;
    }

    if (!aircraftModelNode)
        std::cout << "Problem opening aircraft model" << std::endl;

    osg::StateSet *stateSetAircraft = aircraftModelNode->getOrCreateStateSet();
    stateSetAircraft->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    osg::PositionAttitudeTransform *transformAircraft = new osg::PositionAttitudeTransform;
    osg::Vec3f initialAircraftPosition{physics.get_position()[0], physics.get_position()[1], physics.get_position()[2]};
    transformAircraft->setPosition(initialAircraftPosition);
    transformAircraft->setUpdateCallback(new VehicleUpdateCallback(&physics));
    transformAircraft->addChild(aircraftModelNode);

    this->root->addChild(transformAircraft);

    manipulator->setNode(aircraftModelNode);
}

void MainWindow::create_terrain()
{
    // TODO: READ NODE FILE RELATIVE TO MAIN FILE PATH INSTEAD OF GLOBAL FILE PATH
    warzoneTerrainModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/terrain/warzone/warzone.3ds");
    cityTerrainModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/terrain/city/city.3ds");
    mountainTerrainModelNode = osgDB::readNodeFile("/home/haydenm2/me570/final-project-haydenm2/terrain/mountains/mountain.obj");

    terrainModelNode = cityTerrainModelNode;
    if (!terrainModelNode)
        std::cout << "Problem opening terrain model" << std::endl;

    osg::StateSet *stateSetTerrain = terrainModelNode->getOrCreateStateSet();
    stateSetTerrain->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    this->root->addChild(terrainModelNode);
}

void MainWindow::change_vehicle(FixedWing::FixedWingType type)
{
    pauseFlag = true;
    QPushButton *pausePlayButton = qobject_cast<QPushButton *>(findChild<QObject *>("pushButton_Pause"));
    pausePlayButton->setChecked(pauseFlag);
    fixedWingType = type;
    this->root->removeChild(1);
    this->root->removeObserver(0);
    create_aircraft();
    create_manipulator();
    physics.change_fixed_wing(type);
    physics.reset();
    manipulator->home(0);
}

void MainWindow::change_terrain(TerrainType type)
{
    pauseFlag = true;
    QPushButton *pausePlayButton = qobject_cast<QPushButton *>(findChild<QObject *>("pushButton_Pause"));
    pausePlayButton->setChecked(pauseFlag);
    terrainType = type;

    osg::ref_ptr<osg::Node> newTerrainModelNode;

    switch(terrainType)
    {
        case TerrainType::CITY:
            newTerrainModelNode = cityTerrainModelNode;
            break;
        case TerrainType::WARZONE:
            newTerrainModelNode = warzoneTerrainModelNode;
            break;
        case TerrainType::MOUNTAINS:
            newTerrainModelNode = mountainTerrainModelNode;
            break;
        default:
            newTerrainModelNode = cityTerrainModelNode;
            break;
    }

    if (!newTerrainModelNode)
        std::cout << "Problem opening terrain model" << std::endl;

    osg::StateSet *stateSetTerrain = newTerrainModelNode->getOrCreateStateSet();
    stateSetTerrain->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    this->root->replaceChild(terrainModelNode, newTerrainModelNode);
    terrainModelNode = newTerrainModelNode;
    physics.reset();
    manipulator->home(0);
}

void MainWindow::on_pushButton_Reset_clicked()
{
    physics.reset();
}

void MainWindow::on_pushButton_Pause_toggled(bool checked)
{
    pauseFlag = checked;
    QPushButton *pausePlayButton = qobject_cast<QPushButton *>(findChild<QObject *>("pushButton_Pause"));
    if(checked)
        pausePlayButton->setText(QString("PLAY"));
    else
        pausePlayButton->setText(QString("PAUSE"));
}

void MainWindow::on_pushButton_clicked()
{
    manipulator->home(0);
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    physics.toggle_wind(checked);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QSlider *eastWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_2"));
    QSlider *downWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_3"));
    Eigen::Vector3f windInput{float(value), float(eastWindSlider->value()), float(downWindSlider->value())};
    physics.set_wind(windInput);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    QSlider *northWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider"));
    QSlider *downWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_3"));
    Eigen::Vector3f windInput{float(northWindSlider->value()), float(value), float(downWindSlider->value())};
    physics.set_wind(windInput);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    QSlider *northWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider"));
    QSlider *eastWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_2"));
    Eigen::Vector3f windInput{float(northWindSlider->value()), float(eastWindSlider->value()), float(value)};
    physics.set_wind(windInput);
}

void MainWindow::on_pushButton_2_clicked()
{
    QSlider *northWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider"));
    QSlider *eastWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_2"));
    QSlider *downWindSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_3"));

    northWindSlider->setValue(0);
    eastWindSlider->setValue(0);
    downWindSlider->setValue(0);
}
