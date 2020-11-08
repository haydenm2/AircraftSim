#ifndef VEHICLE_UPDATE_CALLBACK_HPP
#define VEHICLE_UPDATE_CALLBACK_HPP

#include "AircraftPhysics.hpp"
#include "MainWindow.hpp"

#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>

#include <eigen3/Eigen/Dense>


class VehicleUpdateCallback: public osg::NodeCallback
{
public:
    VehicleUpdateCallback(osg::Vec3 *aircraftPosition);
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nodeVisitor);

protected:
    AircraftPhysics *physicsPtr;
    osg::Vec3 *positionPtr;

};

#endif
