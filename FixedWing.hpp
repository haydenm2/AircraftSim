#ifndef FIXED_WING_HPP
#define FIXED_WING_HPP

#include <Eigen/Dense>

#include "Vehicle.hpp"
#include "FixedWingParameters.hpp"
#include "FixedWingAerosondeParameters.hpp"
#include "MathTools.hpp"


class FixedWing : public Vehicle
{
public:
    FixedWing(int type=0);

    void update(float deltaTime) override;
    Eigen::Vector3f get_position() const override;
    Eigen::Vector3f get_orientation() const override;
    Eigen::Vector4f get_control() const override;
    Eigen::Vector3f get_wind() const override;
    float get_gravity() const override;

    void set_control(Eigen::Vector4f controlInput) override;
    void set_wind(Eigen::Vector3f windInput) override;
    void set_gravity(float gravityInput) override;
    void set_initial_velocity(float inertialVelocityInput) override;

private:
    Eigen::VectorXf get_derivatives(Eigen::VectorXf state, Eigen::Vector3f forces, Eigen::Vector3f moments) override;
    void calculate_forces_and_moments();
    void calculate_propulsion_forces_and_moments();
    void calculate_aerodynamic_forces_and_moments();

    Eigen::Vector3f forces{0.0, 0.0, 0.0};
    Eigen::Vector3f moments{0.0, 0.0, 0.0};

    Eigen::VectorXf state{Eigen::VectorXf(12)};
    Eigen::Vector3f wind{0.0, 0.0, 0.0};
    Eigen::Vector4f control{0.0, 0.0, 0.0, 0.0};
    Eigen::MatrixXf controlThresholds{Eigen::MatrixXf(2, 4)};

    FixedWingParameters parameters;
    float gravity{9.81};
};

#endif
