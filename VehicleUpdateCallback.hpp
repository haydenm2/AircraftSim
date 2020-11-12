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
    VehicleUpdateCallback(osg::Vec3 *aircraftPosition, std::array<double, 3> *aircraftAttitude);
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nodeVisitor);

private:
    AircraftPhysics *physicsPtr;
    osg::Vec3 *positionPtr;
    std::array<double, 3> *attitudePtr;
    osg::Quat osgToNEDRotation{0.f, 0.f, 0.7071, 0.7071};


};

#endif
