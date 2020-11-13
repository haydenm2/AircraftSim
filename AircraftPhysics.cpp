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

void AircraftPhysics::update_collisions()
{
}

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

void AircraftPhysics::set_wind(Eigen::Vector3f windInput)
{
}

void AircraftPhysics::set_control(Eigen::Vector4f controlInputs)
{
}
