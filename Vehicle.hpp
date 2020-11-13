#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <Eigen/Dense>


class Vehicle
{
public:
    virtual void update(float deltaTime)=0;

    virtual const Eigen::Vector3f & get_position()=0;
    virtual const Eigen::Vector3f & get_velocity()=0;
    virtual const Eigen::Vector3f & get_acceleration()=0;
    virtual const Eigen::Vector3f & get_orientation()=0;
    virtual const Eigen::Vector3f & get_angular_velocity()=0;
    virtual const Eigen::Vector3f & get_angular_acceleration()=0;
    virtual const Eigen::Vector4f & get_inputs()=0;
    virtual const Eigen::Vector3f & get_wind()=0;

    virtual void set_inputs(Eigen::Vector4f inputsInput)=0;
    virtual void set_wind(Eigen::Vector3f windInput)=0;
};

#endif
