#include "Vehicle.hpp"

Vehicle::Vehicle()
{
}

Vehicle::Vehicle(Eigen::Vector3f positionInit, Eigen::Vector3f velocityInit, Eigen::Vector3f orientationInit, Eigen::Vector3f angularVelocityInit, Eigen::Vector4f controlInputsInit) :
    position{positionInit},
    velocity{velocityInit},
    orientation{orientationInit},
    angularVelocity{angularVelocityInit},
    controlInputs{controlInputsInit}
{
}
