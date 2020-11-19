#include "AircraftPhysics.hpp"


AircraftPhysics::AircraftPhysics()
{
    aircraft = new FixedWing(fixedWingType);
}

//AircraftPhysics::AircraftPhysics(const AircraftPhysics &newPhysics)
//{
//    //TODO
//}

//void operator=(const AircraftPhysics &newPhysics)
//{
//    //TODO
//}

AircraftPhysics::~AircraftPhysics()
{
    delete aircraft;
}

void AircraftPhysics::update(float deltaTime)
{
    aircraft->update(deltaTime);
}

//void AircraftPhysics::change_vehicle(VehiclePhysicsType type)
//{
//}

void AircraftPhysics::change_fixed_wing(FixedWing::FixedWingType type)
{
    delete aircraft;
    fixedWingType = type;
    aircraft = new FixedWing(fixedWingType);
}

void AircraftPhysics::reset()
{
    delete aircraft;
    aircraft = new FixedWing(fixedWingType);
}

//void AircraftPhysics::update_collisions()
//{
//    //TODO
//}

Vehicle *AircraftPhysics::get_aircraft_ptr() const
{
    return aircraft;
}

Eigen::Vector3f AircraftPhysics::get_position() const
{
    return aircraft->get_position();
}

Eigen::Vector3f AircraftPhysics::get_orientation() const
{
    return aircraft->get_orientation();
}

float AircraftPhysics::get_gravity() const
{
    return aircraft->get_gravity();
}

Eigen::Vector3f AircraftPhysics::get_wind() const
{
    return aircraft->get_wind();
}

void AircraftPhysics::set_wind(Eigen::Vector3f windInput)
{
    wind = windInput;
    aircraft->set_wind(windInput);
}

void AircraftPhysics::set_control(Eigen::Vector4f controlInput)
{
    aircraft->set_control(controlInput);
}

void AircraftPhysics::set_gravity(float gravityInput)
{
    aircraft->set_gravity(gravityInput);
}
