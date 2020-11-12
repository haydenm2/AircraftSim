#include "FixedWing.hpp"

FixedWing::FixedWing()
{
}

void FixedWing::update(float deltaTime)
{

}

Eigen::Vector3f FixedWing::calculate_gravitational_forces()
{

}

Eigen::Vector3f FixedWing::calculate_aerodynamic_forces()
{

}

Eigen::Vector3f FixedWing::calculate_propulsion_forces()
{

}

const Eigen::Vector3f * FixedWing::get_position()
{
    return &position;
}

const Eigen::Vector3f * FixedWing::get_velocity()
{
    return &velocity;
}

const Eigen::Vector3f * FixedWing::get_acceleration()
{
    return &acceleration;
}

const Eigen::Vector3f * FixedWing::get_orientation()
{
    return &orientation;
}

const Eigen::Vector3f * FixedWing::get_angular_velocity()
{
    return &angularVelocity;
}

const Eigen::Vector3f * FixedWing::get_angular_acceleration()
{
    return &angularAcceleration;
}

const Eigen::Vector3f * FixedWing::get_wind()
{
    return &wind;
}

void FixedWing::set_position(Eigen::Vector3f positionInput)
{
    position = positionInput;
}

void FixedWing::set_velocity(Eigen::Vector3f velocityInput)
{
    velocity = velocityInput;
}

void FixedWing::set_acceleration(Eigen::Vector3f accelerationInput)
{
    acceleration = accelerationInput;
}

void FixedWing::set_orientation(Eigen::Vector3f orientationInput)
{
    orientation = orientationInput;
}

void FixedWing::set_angular_velocity(Eigen::Vector3f angularVelocityInput)
{
    angularVelocity = angularVelocityInput;
}

void FixedWing::set_angular_acceleration(Eigen::Vector3f angularAccelerationInput)
{
    angularAcceleration = angularAccelerationInput;
}

void FixedWing::set_wind(Eigen::Vector3f windInput)
{
    wind = windInput;
}
