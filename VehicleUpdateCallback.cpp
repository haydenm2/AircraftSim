#include "VehicleUpdateCallback.hpp"


VehicleUpdateCallback::VehicleUpdateCallback(const Eigen::Vector3f *position, const Eigen::Vector3f *attitude)
{
    positionPtr = position;
    attitudePtr = attitude;
}

void VehicleUpdateCallback::operator()(osg::Node *node, osg::NodeVisitor *visitingNode)
{
    osg::PositionAttitudeTransform *aircraftTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    osg::Vec3 position;
    position[0] = positionPtr->data()[0];
    position[1] = positionPtr->data()[1];
    position[2] = positionPtr->data()[2];
    aircraftTransformation->setPosition(position);

    osg::Quat attitudeRPY;
    double phi = attitudePtr->data()[0];
    double theta = attitudePtr->data()[1];
    double psi = attitudePtr->data()[2];

    attitudeRPY[3] = cos(phi/2.0)*cos(theta/2.0)*cos(psi/2.0) + sin(phi/2.0)*sin(theta/2.0)*sin(psi/2.0);
    attitudeRPY[0] = sin(phi/2.0)*cos(theta/2.0)*cos(psi/2.0) - cos(phi/2.0)*sin(theta/2.0)*sin(psi/2.0);
    attitudeRPY[1] = cos(phi/2.0)*sin(theta/2.0)*cos(psi/2.0) + sin(phi/2.0)*cos(theta/2.0)*sin(psi/2.0);
    attitudeRPY[2] = cos(phi/2.0)*cos(theta/2.0)*sin(psi/2.0) - sin(phi/2.0)*sin(theta/2.0)*cos(psi/2.0);
    aircraftTransformation->setAttitude(osgToNEDRotation*attitudeRPY);

    traverse(node, visitingNode);
}
