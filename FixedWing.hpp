#ifndef FIXED_WING_HPP
#define FIXED_WING_HPP

#include <Eigen/Dense>

#include "Vehicle.hpp"
#include "FixedWingParameters.hpp"


class FixedWing : Vehicle
{
public:
    FixedWing();
    void update(float deltaTime) override;
    const Eigen::Vector3f * get_position();
    const Eigen::Vector3f * get_velocity();
    const Eigen::Vector3f * get_acceleration();
    const Eigen::Vector3f * get_orientation();
    const Eigen::Vector3f * get_angular_velocity();
    const Eigen::Vector3f * get_angular_acceleration();
    const Eigen::Vector3f * get_wind();
    const FixedWingParameters * get_parameters();

    void set_position(Eigen::Vector3f positionInput);
    void set_velocity(Eigen::Vector3f velocityInput);
    void set_acceleration(Eigen::Vector3f accelerationInput);
    void set_orientation(Eigen::Vector3f orientationInput);
    void set_angular_velocity(Eigen::Vector3f angularVelocityInput);
    void set_angular_acceleration(Eigen::Vector3f angularAccelerationInput);
    void set_wind(Eigen::Vector3f windInput);
    void set_parameters(FixedWingParameters parameterInput);

private:
    Eigen::Vector3f calculate_gravitational_forces();
    Eigen::Vector3f calculate_aerodynamic_forces();
    Eigen::Vector3f calculate_propulsion_forces();

    Eigen::Vector3f position{0.0, 0.0, 0.0};
    Eigen::Vector3f velocity{0.0, 0.0, 0.0};
    Eigen::Vector3f acceleration{0.0, 0.0, 0.0};
    Eigen::Vector3f orientation{0.0, 0.0, 0.0};
    Eigen::Vector3f angularVelocity{0.0, 0.0, 0.0};
    Eigen::Vector3f angularAcceleration{0.0, 0.0, 0.0};
    Eigen::Vector3f wind{0.0, 0.0, 0.0};
    FixedWingParameters parameters;
};

#endif
