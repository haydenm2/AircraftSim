#include "MainWindow.hpp"
#include "ui_MainWindowForm.h"

#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mMainWindowUI{new Ui::MainWindowForm}
{
    mMainWindowUI->setupUi(this);
    QObject::connect(mMainWindowUI->osgWidget, &osgQOpenGLWidget::initialized, this, &MainWindow::setupOsgView);
}

void MainWindow::setupOsgView()
{
    create_camera();
    create_manipulator();
    create_shadowed_scene();
    create_light();
    create_geometry();
}

MainWindow::~MainWindow()
{
    delete mMainWindowUI;
}

void MainWindow::create_camera()
{
    float aspectRatio = static_cast<float>( this->width() ) / static_cast<float>( this->height() );
    auto pixelRatio   = this->devicePixelRatio();

    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->setClearColor( osg::Vec4( 0.f, 0.f, .5, 1.f ) );
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->setProjectionMatrixAsPerspective( 45.f, aspectRatio, 1.f, 1000.f );
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->setViewMatrixAsLookAt(osg::Vec3d(0.0,-20.0,3.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    mMainWindowUI->osgWidget->getOsgViewer()->getCamera()->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
}

void MainWindow::create_manipulator()
{
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
    manipulator->setHomePosition(osg::Vec3d(0.0,-20.0,3.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));
    mMainWindowUI->osgWidget->getOsgViewer()->setCameraManipulator( manipulator );
}

void MainWindow::create_shadowed_scene()
{
    shadowedScene = new osgShadow::ShadowedScene;
    shadowedScene->setReceivesShadowTraversalMask(receivesShadowTraversalMask);
    shadowedScene->setCastsShadowTraversalMask(castsShadowTraversalMask);
    shadowedScene->getShadowSettings()->setDebugDraw(true);

//    osg::ref_ptr<osgShadow::ShadowMap> sm = new osgShadow::ShadowMap;
//    sm->setLight(ls->getLight());
//    sm->setTextureSize(osg::Vec2s(1024,1024));
//    sm->setTextureUnit(1);

    osg::ref_ptr<osgShadow::ShadowTexture> st = new osgShadow::ShadowTexture;
    shadowedScene->setShadowTechnique(st.get());
    mMainWindowUI->osgWidget->getOsgViewer()->setSceneData( shadowedScene );
}

void MainWindow::create_geometry()
{
    create_sphere();
    create_box();
}

void MainWindow::create_box()
{
    osg::Box* box    = new osg::Box( osg::Vec3( 0.f, 0.f, -5.0 ), 20.0f,20.0f,1.0f );
    osg::ShapeDrawable* boxSD = new osg::ShapeDrawable( box );
    boxSD->setColor( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
    boxSD->setName( "Box" );

    osg::Geode* boxGeode = new osg::Geode;
    boxGeode->addDrawable( boxSD );
    osg::StateSet* boxStateSet = boxGeode->getOrCreateStateSet();
    osg::Material* boxMaterial = new osg::Material;
    boxMaterial->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    boxStateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    boxStateSet->setAttributeAndModes( boxMaterial, osg::StateAttribute::ON );
    boxGeode->setNodeMask(receivesShadowTraversalMask);
    shadowedScene->addChild(boxGeode);
}

void MainWindow::create_sphere()
{
    osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 2.0f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
    sd->setColor( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
    sd->setName( "Sphere" );

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );
    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;
    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    geode->setNodeMask(castsShadowTraversalMask);
    shadowedScene->addChild(geode);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

