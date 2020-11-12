#ifndef AIRCRAFT_PHYSICS_HPP
#define AIRCRAFT_PHYSICS_HPP

#include "Vehicle.hpp"
#include "FixedWing.hpp"
#include <math.h>
#include <Eigen/Dense>

class AircraftPhysics
{
public:
    AircraftPhysics();
    void update(float deltaTime);
    void change_aircraft(int type);
    Vehicle *get_aircraft_ptr();
    Eigen::Vector3f get_position();
    Eigen::Vector3f get_velocity();
    Eigen::Vector3f get_orientation();
    Eigen::Vector3f get_angular_velocity();
    void set_position(Eigen::Vector3f positionInput);
    void set_orientation(Eigen::Vector3f orientationInput);
    void set_wind(Eigen::Vector3f windInput);
    void set_control(Eigen::Vector4f controlInputs);

protected:
    int aircraftType{0};
    Vehicle *aircraft;
    float gravity{9.81};
    float airDensity{1.225};

private:
    void update_collisions();
};

#endif
