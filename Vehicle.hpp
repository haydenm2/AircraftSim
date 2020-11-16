#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <Eigen/Dense>


class Vehicle
{
public:
    virtual void update(float deltaTime)=0;

    virtual Eigen::Vector3f get_position() const=0;
    virtual Eigen::Vector3f get_orientation() const=0;
    virtual Eigen::Vector4f get_control() const=0;
    virtual Eigen::Vector3f get_wind() const=0;
    virtual float get_gravity() const=0;

    virtual void set_control(Eigen::Vector4f controlInput)=0;
    virtual void set_wind(Eigen::Vector3f windInput)=0;
    virtual void set_gravity(float gravityInput)=0;
    virtual void set_initial_velocity(float inertialVelocityInput)=0;

protected:
    virtual Eigen::VectorXf get_derivatives(Eigen::VectorXf state, Eigen::Vector3f forces, Eigen::Vector3f moments) const=0;

};

#endif
