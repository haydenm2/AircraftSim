#ifndef VEHICLE_UPDATE_CALLBACK_HPP
#define VEHICLE_UPDATE_CALLBACK_HPP

#include "AircraftPhysics.hpp"
#include "MainWindow.hpp"

#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>

#include <Eigen/Dense>


class VehicleUpdateCallback: public osg::NodeCallback
{
public:
    VehicleUpdateCallback(const Eigen::Vector3f *aircraftPosition, const Eigen::Vector3f *aircraftAttitude);
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nodeVisitor);

private:
    AircraftPhysics *physicsPtr;
    const Eigen::Vector3f *positionPtr;
    const Eigen::Vector3f *attitudePtr;
    osg::Quat osgToNEDRotation{0.f, 0.f, 0.7071, 0.7071};


};

#endif
