#include "VehicleUpdateCallback.hpp"


VehicleUpdateCallback::VehicleUpdateCallback(AircraftPhysics *systemPhysics): physicsPtr{systemPhysics}
{
}

void VehicleUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* visitingNode)
{
    osg::Group *parent = node->getParent(0);
    traverse(node, visitingNode);
}
