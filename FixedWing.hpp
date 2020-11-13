#ifndef FIXED_WING_HPP
#define FIXED_WING_HPP

#include <Eigen/Dense>

#include "Vehicle.hpp"
#include "FixedWingParameters.hpp"
#include "FixedWingAerosondeParameters.hpp"


class FixedWing : public Vehicle
{
public:
    FixedWing();
    FixedWing(int type);

    void update(float deltaTime) override;
    const Eigen::Vector3f & get_position() override;
    const Eigen::Vector3f & get_velocity() override;
    const Eigen::Vector3f & get_acceleration() override;
    const Eigen::Vector3f & get_orientation() override;
    const Eigen::Vector3f & get_angular_velocity() override;
    const Eigen::Vector3f & get_angular_acceleration() override;
    const Eigen::Vector4f & get_control() override;
    const Eigen::Vector3f & get_wind() override;
    const float & get_gravity() override;

    void set_control(Eigen::Vector4f controlInput) override;
    void set_wind(Eigen::Vector3f windInput) override;
    void set_gravity(float gravityInput) override;

private:
    Eigen::Vector3f calculate_aerodynamic_forces();
    Eigen::Vector3f calculate_propulsion_forces();

    Eigen::Vector3f position{0.0, 0.0, 0.0};
    Eigen::Vector3f velocity{0.0, 0.0, 0.0};
    Eigen::Vector3f acceleration{0.0, 0.0, 0.0};
    Eigen::Vector3f orientation{0.0, 0.0, 0.0};
    Eigen::Vector3f angularVelocity{0.0, 0.0, 0.0};
    Eigen::Vector3f angularAcceleration{0.0, 0.0, 0.0};
    Eigen::Vector3f wind{0.0, 0.0, 0.0};
    Eigen::Vector4f control{0.0, 0.0, 0.0, 0.0};

    FixedWingParameters parameters;
    float gravity{9.81};
    float airDensity;
};

#endif
