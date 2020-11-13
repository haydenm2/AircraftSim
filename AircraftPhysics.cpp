#include "AircraftPhysics.hpp"


AircraftPhysics::AircraftPhysics()
{
    if(aircraftType == 0)
    {
        aircraft = new FixedWing(fixedWingType);
    }
    else if(aircraftType == 1)
    {
        //TODO: add quadrotor
    }
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

void AircraftPhysics::change_aircraft(int type)
{
}

//void AircraftPhysics::update_collisions()
//{
//    //TODO
//}

Vehicle *AircraftPhysics::get_aircraft_ptr()
{
    return aircraft;
}

const Eigen::Vector3f & AircraftPhysics::get_position()
{
    return aircraft->get_position();
}

const Eigen::Vector3f & AircraftPhysics::get_orientation()
{
    return aircraft->get_orientation();
}

const float & AircraftPhysics::get_gravity()
{
    return aircraft->get_gravity();
}

const Eigen::Vector3f & AircraftPhysics::get_wind()
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
