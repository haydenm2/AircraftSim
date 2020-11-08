#include "VehicleUpdateCallback.hpp"


VehicleUpdateCallback::VehicleUpdateCallback(osg::Vec3 *position)
{
    positionPtr = position;
}

void VehicleUpdateCallback::operator()(osg::Node *node, osg::NodeVisitor *visitingNode)
{
    osg::PositionAttitudeTransform *aircraftTransformation = dynamic_cast<osg::PositionAttitudeTransform *> (node);
    aircraftTransformation->setPosition(*positionPtr);

    traverse(node, visitingNode);
}
