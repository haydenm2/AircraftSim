#include "AircraftPhysics.hpp"


AircraftPhysics::AircraftPhysics()
{
    aircraft = new FixedWing(fixedWingType);
}

AircraftPhysics::~AircraftPhysics()
{
    delete aircraft;
}

void AircraftPhysics::update(float deltaTime)
{
    aircraft->update(deltaTime);
}

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
    aircraft->set_wind(wind);
}

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

bool AircraftPhysics::isWindActive() const
{
    return windActive;
}

void AircraftPhysics::toggle_wind(bool active)
{
    windActive = active;
    if(windActive)
    {
        aircraft->set_wind(wind);
    }
    else
    {
        aircraft->set_wind(Eigen::Vector3f{0.0f, 0.0f, 0.0f});
    }
}

void AircraftPhysics::set_wind(Eigen::Vector3f windInput)
{
    wind = windInput;
    if(windActive)
    {
        aircraft->set_wind(wind);
    }
}

void AircraftPhysics::set_control(Eigen::Vector4f controlInput)
{
    aircraft->set_control(controlInput);
}

void AircraftPhysics::set_gravity(float gravityInput)
{
    aircraft->set_gravity(gravityInput);
}
