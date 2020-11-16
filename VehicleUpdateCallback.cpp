#include "VehicleUpdateCallback.hpp"


VehicleUpdateCallback::VehicleUpdateCallback(const Vehicle *aircraft)
{
    aircraftPtr = aircraft;
}

void VehicleUpdateCallback::operator()(osg::Node *node, osg::NodeVisitor *visitingNode)
{
    osg::PositionAttitudeTransform *aircraftTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    osg::Vec3 position;
    position[0] = aircraftPtr->get_position()[0];
    position[1] = aircraftPtr->get_position()[1];
    position[2] = aircraftPtr->get_position()[2];
    aircraftTransformation->setPosition(position);

    osg::Quat attitudeRPY;
    double phi = aircraftPtr->get_orientation()[0];
    double theta = aircraftPtr->get_orientation()[1];
    double psi = aircraftPtr->get_orientation()[2];

    attitudeRPY[3] = cos(phi/2.0)*cos(theta/2.0)*cos(psi/2.0) + sin(phi/2.0)*sin(theta/2.0)*sin(psi/2.0);
    attitudeRPY[0] = sin(phi/2.0)*cos(theta/2.0)*cos(psi/2.0) - cos(phi/2.0)*sin(theta/2.0)*sin(psi/2.0);
    attitudeRPY[1] = cos(phi/2.0)*sin(theta/2.0)*cos(psi/2.0) + sin(phi/2.0)*cos(theta/2.0)*sin(psi/2.0);
    attitudeRPY[2] = cos(phi/2.0)*cos(theta/2.0)*sin(psi/2.0) - sin(phi/2.0)*sin(theta/2.0)*cos(psi/2.0);
    aircraftTransformation->setAttitude(osgToNEDRotation*attitudeRPY);

    traverse(node, visitingNode);
}
