#ifndef FIXED_WING_HPP
#define FIXED_WING_HPP

#include <Eigen/Dense>

#include "Vehicle.hpp"


class FixedWing : Vehicle
{
public:
    FixedWing();
    const Eigen::Vector3f * getPosition();
    const Eigen::Vector3f * getVelocity();
    const Eigen::Vector3f * getAcceleration();
    const Eigen::Vector3f * getOrientation();
    const Eigen::Vector3f * getAngularVelocity();
    const Eigen::Vector3f * getAngularAcceleration();
    const Eigen::Vector3f * getWind();
    void setPosition(Eigen::Vector3f positionInput);
    void setVelocity(Eigen::Vector3f velocityInput);
    void setAcceleration(Eigen::Vector3f accelerationInput);
    void setOrientation(Eigen::Vector3f orientationInput);
    void setAngularVelocity(Eigen::Vector3f angularVelocityInput);
    void setAngularAcceleration(Eigen::Vector3f angularAccelerationInput);
    void setWind(Eigen::Vector3f windInput);

private:
    Eigen::Vector3f position{0.0, 0.0, 0.0};
    Eigen::Vector3f velocity{0.0, 0.0, 0.0};
    Eigen::Vector3f acceleration{0.0, 0.0, 0.0};
    Eigen::Vector3f orientation{0.0, 0.0, 0.0};
    Eigen::Vector3f angularVelocity{0.0, 0.0, 0.0};
    Eigen::Vector3f angularAcceleration{0.0, 0.0, 0.0};
    Eigen::Vector3f wind{0.0, 0.0, 0.0};
};

#endif
