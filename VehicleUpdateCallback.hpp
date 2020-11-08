#ifndef VEHICLE_UPDATE_CALLBACK_HPP
#define VEHICLE_UPDATE_CALLBACK_HPP

#include "AircraftPhysics.hpp"

#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>

#include <eigen3/Eigen/Dense>


class VehicleUpdateCallback: public osg::NodeCallback
{
public:
    VehicleUpdateCallback(AircraftPhysics *systemPhysics);
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nodeVisitor);

protected:
    AircraftPhysics *physicsPtr;

};

#endif
