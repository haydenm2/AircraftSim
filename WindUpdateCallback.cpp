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
    windScale[0] = windMagnitude/25.0;
    windScale[1] = 1.0;
    windScale[2] = windMagnitude/25.0;
    if(!(physicsPtr->isWindActive()))
    {
        windScale *= 0.0;
    }
    windTransformation->setScale(windScale);

    if(windMagnitude == 0)
    {
        windNormalized[0] = 1.0;
    }

    osg::Quat attitude;
    Eigen::Vector3f xAxis{Eigen::Vector3f{1.0, 0.0, 0.0}};
    Eigen::Quaternion<float> attitudeEigen{(math_tools::get_quaternion_between_vectors(xAxis, windNormalized)).inverse()};
    attitude[0] = attitudeEigen.x();
    attitude[1] = attitudeEigen.y();
    attitude[2] = attitudeEigen.z();
    attitude[3] = attitudeEigen.w();

    windTransformation->setAttitude(osgToNEDRotation*attitude);

    traverse(node, visitingNode);
}
