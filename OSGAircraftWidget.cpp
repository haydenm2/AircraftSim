#include "OSGAircraftWidget.hpp"


OSGAircraftWidget::OSGAircraftWidget(QWidget* parent, Qt::WindowFlags flags):
    QOpenGLWidget{parent,flags},
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
    create_ground_plane();
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

void OSGAircraftWidget::paintEvent(QPaintEvent* /* paintEvent */)
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

void OSGAircraftWidget::keyPressEvent(QKeyEvent* event)
{
    QString keyString = event->text();
    const char* keyData = keyString.toLocal8Bit().data();
    this->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGAircraftWidget::keyReleaseEvent(QKeyEvent* event)
{
    QString keyString = event->text();
    const char* keyData = keyString.toLocal8Bit().data();
    this->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGAircraftWidget::mouseMoveEvent(QMouseEvent* event)
{
    auto pixelRatio = this->devicePixelRatio();
    this->getEventQueue()->mouseMotion(static_cast<float>(event->x()*pixelRatio),
                                       static_cast<float>(event->y()*pixelRatio));
}

void OSGAircraftWidget::mousePressEvent(QMouseEvent* event)
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
    this->getEventQueue()->mouseButtonPress(static_cast<float>( event->x() * pixelRatio),
                                            static_cast<float>( event->y() * pixelRatio),
                                            button);
}

void OSGAircraftWidget::mouseReleaseEvent(QMouseEvent* event)
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

void OSGAircraftWidget::wheelEvent(QWheelEvent* event)
{
    event->accept();
    int delta = event->delta();
    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
    this->getEventQueue()->mouseScroll(motion);
}

osgGA::EventQueue* OSGAircraftWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if(eventQueue)
        return eventQueue;
    else
        throw std::runtime_error("Unable to obtain valid event queue");
}

void OSGAircraftWidget::create_camera()
{
    float aspectRatio = static_cast<float>(this->width())/static_cast<float>(this->height());
    auto pixelRatio = this->devicePixelRatio();
    camera->setViewport(0, 0, this->width()*pixelRatio, this->height()*pixelRatio);
    camera->setClearColor(osg::Vec4(0.8f, 0.8f, 0.8f, 0.7f));
    camera->setProjectionMatrixAsPerspective(45.f, aspectRatio, 1.f, 1000.f);
    camera->setGraphicsContext(this->mGraphicsWindow);
}

void OSGAircraftWidget::create_manipulator()
{
    osg::Vec3 initialPosition{0.0, -15.0, 15.0};
    osg::Vec3 initialPointingPosition{0, 0, 0};
    osg::Vec3 upVector{0,0,1};
    manipulator->setAllowThrow( false );
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

void OSGAircraftWidget::change_aircraft(int type)
{
}

void OSGAircraftWidget::create_aircraft()
{
}

void OSGAircraftWidget::create_ground_plane()
{
    osg::Vec4 groundPlaneColor{0.04f, 0.4f, 0.14f, 0.0f};
    osg::ref_ptr<osg::Vec3Array> groundPlaneVertices = new osg::Vec3Array;
    groundPlaneVertices->push_back(osg::Vec3(-initialGroundPlaneSize, -initialGroundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(initialGroundPlaneSize, -initialGroundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(initialGroundPlaneSize, initialGroundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(-initialGroundPlaneSize, initialGroundPlaneSize, 0.0f));
    osg::ref_ptr<osg::Vec3Array> groundPlaneNormals = new osg::Vec3Array;
    groundPlaneNormals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    osg::ref_ptr<osg::Vec4Array> groundColor = new osg::Vec4Array;
    groundColor->push_back(groundPlaneColor);
    osg::ref_ptr<osg::Geometry> groundGeometry = new osg::Geometry;
    groundGeometry->setVertexArray(groundPlaneVertices.get());
    groundGeometry->setNormalArray(groundPlaneNormals.get());
    groundGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
    groundGeometry->setColorArray(groundColor.get());
    groundGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    groundGeometry->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
    osg::Geode* geodeGroundPlane = new osg::Geode;
    geodeGroundPlane->addDrawable(groundGeometry.get());
    osg::StateSet* stateSetGround = geodeGroundPlane->getOrCreateStateSet();
    osg::Material* materialGround = new osg::Material;
    materialGround->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    stateSetGround->setAttributeAndModes(materialGround, osg::StateAttribute::ON);
    stateSetGround->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    this->mRoot->addChild(geodeGroundPlane);
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

AircraftPhysics* OSGAircraftWidget::get_physics_ptr()
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

