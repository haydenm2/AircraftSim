#include "VehicleUpdateCallback.hpp"


VehicleUpdateCallback::VehicleUpdateCallback(osg::Vec3 *position, std::array<double, 3> *attitude)
{
    positionPtr = position;
    attitudePtr = attitude;
}

void VehicleUpdateCallback::operator()(osg::Node *node, osg::NodeVisitor *visitingNode)
{
    osg::PositionAttitudeTransform *aircraftTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    aircraftTransformation->setPosition(*positionPtr);

    osg::Quat attitudeRPY;
    double phi = attitudePtr->at(0);
    double theta = attitudePtr->at(1);
    double psi = attitudePtr->at(2);

    attitudeRPY[3] = cos(phi/2.0)*cos(theta/2.0)*cos(psi/2.0) + sin(phi/2.0)*sin(theta/2.0)*sin(psi/2.0);
    attitudeRPY[0] = sin(phi/2.0)*cos(theta/2.0)*cos(psi/2.0) - cos(phi/2.0)*sin(theta/2.0)*sin(psi/2.0);
    attitudeRPY[1] = cos(phi/2.0)*sin(theta/2.0)*cos(psi/2.0) + sin(phi/2.0)*cos(theta/2.0)*sin(psi/2.0);
    attitudeRPY[2] = cos(phi/2.0)*cos(theta/2.0)*sin(psi/2.0) - sin(phi/2.0)*sin(theta/2.0)*cos(psi/2.0);
    aircraftTransformation->setAttitude(osgToNEDRotation*attitudeRPY);

    traverse(node, visitingNode);
}
