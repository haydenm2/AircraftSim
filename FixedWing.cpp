#include "FixedWing.hpp"

FixedWing::FixedWing()
{
}

const Eigen::Vector3f * FixedWing::getPosition()
{
    return &position;
}

const Eigen::Vector3f * FixedWing::getVelocity()
{
    return &velocity;
}

const Eigen::Vector3f * FixedWing::getAcceleration()
{
    return &acceleration;
}

const Eigen::Vector3f * FixedWing::getOrientation()
{
    return &orientation;
}

const Eigen::Vector3f * FixedWing::getAngularVelocity()
{
    return &angularVelocity;
}

const Eigen::Vector3f * FixedWing::getAngularAcceleration()
{
    return &angularAcceleration;
}

void FixedWing::setPosition(Eigen::Vector3f positionInput)
{
    position = positionInput;
}

void FixedWing::setVelocity(Eigen::Vector3f velocityInput)
{
    velocity = velocityInput;
}

void FixedWing::setAcceleration(Eigen::Vector3f accelerationInput)
{
    acceleration = accelerationInput;
}

void FixedWing::setOrientation(Eigen::Vector3f orientationInput)
{
    orientation = orientationInput;
}

void FixedWing::setAngularVelocity(Eigen::Vector3f angularVelocityInput)
{
    angularVelocity = angularVelocityInput;
}

void FixedWing::setAngularAcceleration(Eigen::Vector3f angularAccelerationInput)
{
    angularAcceleration = angularAccelerationInput;
}
