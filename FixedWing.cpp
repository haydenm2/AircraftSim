#include "FixedWing.hpp"
#include <iostream>

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
    controlThresholds(0, 0) = math_tools::degrees2Radians(-25);
    controlThresholds(1, 0) = math_tools::degrees2Radians(25);
    controlThresholds(0, 1) = math_tools::degrees2Radians(-25);
    controlThresholds(1, 1) = math_tools::degrees2Radians(25);
    controlThresholds(0, 2) = math_tools::degrees2Radians(-25);
    controlThresholds(1, 2) = math_tools::degrees2Radians(25);
    controlThresholds(0, 3) = 0.0;
    controlThresholds(1, 3) = 1.0;
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

const Eigen::Vector4f & FixedWing::get_control()
{
    return control;
}

const Eigen::Vector3f & FixedWing::get_wind()
{
    return wind;
}

const float & FixedWing::get_gravity()
{
    return gravity;
}

void FixedWing::set_control(Eigen::Vector4f controlInput)
{
    Eigen::Vector4f saturatedControl;
    for(int index{0}; index < 4; index++)
    {
        saturatedControl[index] = math_tools::saturate(controlInput[index], controlThresholds(0, index), controlThresholds(1, index));
    }
    control = saturatedControl;
}

void FixedWing::set_wind(Eigen::Vector3f windInput)
{
    wind = windInput;
}

void FixedWing::set_gravity(float gravityInput)
{
    gravity = gravityInput;
}
