#include "WindUpdateCallback.hpp"


WindUpdateCallback::WindUpdateCallback(const AircraftPhysics *physics)
{
    physicsPtr = physics;
}

void WindUpdateCallback::operator()(osg::Node *node, osg::NodeVisitor *visitingNode)
{
    osg::PositionAttitudeTransform *windTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    osg::Vec3 position;
    position[0] = physicsPtr->get_aircraft_ptr()->get_position()[0];
    position[1] = physicsPtr->get_aircraft_ptr()->get_position()[1];
    position[2] = physicsPtr->get_aircraft_ptr()->get_position()[2];
    windTransformation->setPosition(position);

    Eigen::Vector3f wind = physicsPtr->get_wind();
    float windMagnitude = sqrt(pow(wind[0], 2) + pow(wind[1], 2) + pow(wind[2], 2));
    Eigen::Vector3f windNormalized = wind/windMagnitude;

    osg::Vec3 windScale;
    windScale[0] = windMagnitude/5.0;
    windScale[1] = 1.0;
    windScale[2] = windMagnitude/5.0;

    if(!(physicsPtr->isWindActive()))
    {
        windScale *= 0.0;
    }

    windTransformation->setScale(windScale);

    osg::Quat attitudeRPY;
    double phi = physicsPtr->get_aircraft_ptr()->get_orientation()[0];
    double theta = physicsPtr->get_aircraft_ptr()->get_orientation()[1];
    double psi = physicsPtr->get_aircraft_ptr()->get_orientation()[2];

    attitudeRPY[3] = cos(phi/2.0)*cos(theta/2.0)*cos(psi/2.0) + sin(phi/2.0)*sin(theta/2.0)*sin(psi/2.0);
    attitudeRPY[0] = sin(phi/2.0)*cos(theta/2.0)*cos(psi/2.0) - cos(phi/2.0)*sin(theta/2.0)*sin(psi/2.0);
    attitudeRPY[1] = cos(phi/2.0)*sin(theta/2.0)*cos(psi/2.0) + sin(phi/2.0)*cos(theta/2.0)*sin(psi/2.0);
    attitudeRPY[2] = cos(phi/2.0)*cos(theta/2.0)*sin(psi/2.0) - sin(phi/2.0)*sin(theta/2.0)*cos(psi/2.0);
    windTransformation->setAttitude(osgToNEDRotation*attitudeRPY);

    traverse(node, visitingNode);
}
