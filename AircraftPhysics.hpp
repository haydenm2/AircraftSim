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
    ~AircraftPhysics();
//    AircraftPhysics(const AircraftPhysics &newAircraft);
//    void operator=(const AircraftPhysics &newAircraft);

    void update(float deltaTime);
    void change_aircraft(int type);
    Vehicle *get_aircraft_ptr();
    const Eigen::Vector3f & get_position();
    const Eigen::Vector3f & get_orientation();
    void set_wind(Eigen::Vector3f windInput);
    void set_control(Eigen::Vector4f controlInputs);

protected:
    int aircraftType{0};
    int fixedWingType{0};
    int quadrotorType{0};
    Vehicle *aircraft;
    float gravity{9.81};
    float airDensity{1.2682};

private:
    void update_collisions();
};

#endif
