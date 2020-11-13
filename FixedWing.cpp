#include "FixedWing.hpp"
#include <iostream>

FixedWing::FixedWing()
{
    parameters = FixedWingAerosondeParameters();
}

FixedWing::FixedWing(int type)
{
    switch(type)
    {
        case 0:
            parameters = FixedWingAerosondeParameters();
            break;
        default:
            parameters = FixedWingAerosondeParameters();
            break;
    }
}

void FixedWing::update(float deltaTime)
{
    Eigen::Vector3f gravity_force{0.0, 0.0, -gravity};
    Eigen::Vector3f aerodynamic_force = calculate_aerodynamic_forces();
    Eigen::Vector3f propulsion_force = calculate_propulsion_forces();

    acceleration = gravity_force + aerodynamic_force + propulsion_force;
    velocity = velocity + acceleration*deltaTime;
    position = position + velocity*deltaTime + 0.5*acceleration*pow(deltaTime, 2);
}

Eigen::Vector3f FixedWing::calculate_aerodynamic_forces()
{
    return Eigen::Vector3f{0.0, 0.0, 0.0};
}

Eigen::Vector3f FixedWing::calculate_propulsion_forces()
{
    return Eigen::Vector3f{0.0, 0.0, 0.0};
}

const Eigen::Vector3f & FixedWing::get_position()
{
    return position;
}

const Eigen::Vector3f & FixedWing::get_velocity()
{
    return velocity;
}

const Eigen::Vector3f & FixedWing::get_acceleration()
{
    return acceleration;
}

const Eigen::Vector3f & FixedWing::get_orientation()
{
    return orientation;
}

const Eigen::Vector3f & FixedWing::get_angular_velocity()
{
    return angularVelocity;
}

const Eigen::Vector3f & FixedWing::get_angular_acceleration()
{
    return angularAcceleration;
}

const Eigen::Vector4f & FixedWing::get_inputs()
{
    return inputs;
}

const Eigen::Vector3f & FixedWing::get_wind()
{
    return wind;
}

void FixedWing::set_inputs(Eigen::Vector4f inputsInput)
{
    inputs = inputsInput;
}

void FixedWing::set_wind(Eigen::Vector3f windInput)
{
    wind = windInput;
}
