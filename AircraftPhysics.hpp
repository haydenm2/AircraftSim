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
//    void change_vehicle(VehiclePhysicsType type);
    void change_fixed_wing(FixedWing::FixedWingType type);
    void reset();

    Vehicle *get_aircraft_ptr() const;
    Eigen::Vector3f get_position() const;
    Eigen::Vector3f get_orientation() const;
    float get_gravity() const;
    Eigen::Vector3f get_wind() const;

    void set_wind(Eigen::Vector3f windInput);
    void set_control(Eigen::Vector4f controlInput);
    void set_gravity(float gravityInput);

//    enum FixedWingPhysicsType {EMB312, EMB314, F16D, MQ9};
//    enum QuadcopterPhysicsType {PHANTOM};

protected:
    int aircraftType{0};
    FixedWing::FixedWingType fixedWingType{FixedWing::FixedWingType::EMB314};
//    QuadcopterPhysicsType quadcopterType{QuadcopterPhysicsType::PHANTOM};
    Vehicle *aircraft;
    float gravity{9.81};
    Eigen::Vector3f wind{0.0, 0.0, 0.0};


private:
//    void update_collisions();
};

#endif
