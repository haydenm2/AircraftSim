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
    void change_fixed_wing(FixedWing::FixedWingType type);
    void reset();

    Vehicle *get_aircraft_ptr() const;
    Eigen::Vector3f get_position() const;
    Eigen::Vector3f get_orientation() const;
    float get_gravity() const;
    Eigen::Vector3f get_wind() const;
    bool isWindActive() const;

    void toggle_wind(bool active);
    void set_wind(Eigen::Vector3f windInput);
    void set_control(Eigen::Vector4f controlInput);
    void set_gravity(float gravityInput);

protected:
    int aircraftType{0};
    FixedWing::FixedWingType fixedWingType{FixedWing::FixedWingType::EMB314};
    Vehicle *aircraft;
    float gravity{9.81};
    bool windActive{true};
    Eigen::Vector3f wind{0.0, 0.0, 0.0};

private:
//    void update_collisions();
};

#endif
