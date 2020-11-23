#ifndef WIND_UPDATE_CALLBACK_HPP
#define WIND_UPDATE_CALLBACK_HPP

#include "AircraftPhysics.hpp"
#include "MainWindow.hpp"

#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>

#include <Eigen/Dense>


class WindUpdateCallback: public osg::NodeCallback
{
public:
    WindUpdateCallback(const AircraftPhysics *physicsPtr);
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nodeVisitor);

private:
    const AircraftPhysics *physicsPtr;
    osg::Quat osgToNEDRotation{0.f, 0.f, 0.7071, 0.7071};

};

#endif
