#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <Eigen/Dense>


class Vehicle
{
public:
    Vehicle();
    virtual void update(float deltaTime)=0;

protected:

};

#endif
