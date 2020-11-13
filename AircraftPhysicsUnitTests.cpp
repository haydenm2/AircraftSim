#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "AircraftPhysics.hpp"

//AircraftPhysics();
//void update(float deltaTime);
//Eigen::Vector3f get_position();
//int aircraftType{0};
//int fixedWingType{0};
//int quadrotorType{0};
//Vehicle *aircraft;
//float gravity{9.81};
//float airDensity{1.2682};

class AircraftPhysicsTests : public ::testing::Test
{
protected:
    AircraftPhysics physics;
    Eigen::Vector3f zeros3{0.0, 0.0, 0.0};
    Eigen::Vector3f ones3{1.0, 1.0, 1.0};
    Eigen::Vector4f zeros4{0.0, 0.0, 0.0, 0.0};
    Eigen::Vector4f ones4{1.0, 1.0, 1.0, 1.0};
};

TEST_F(AircraftPhysicsTests, WhenRequestingAircraftPointer_ExpectValidPointer)
{
    EXPECT_FALSE(physics.get_aircraft_ptr() == nullptr);
}

TEST_F(AircraftPhysicsTests, WhenUpdatingWithNoTimeStep_ExpectNoChanges)
{
    Eigen::Vector3f accelerationExpected{0.0, 0.0, -9.81};

    float deltaTime{0.0};
    physics.update(deltaTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_position(), zeros3);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_velocity(), zeros3);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_acceleration(), accelerationExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_orientation(), zeros3);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_angular_velocity(), zeros3);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_angular_acceleration(), zeros3);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_wind(), zeros3);
    EXPECT_VECTOR4_FLOAT_EQ(physics.get_aircraft_ptr()->get_inputs(), zeros4);
}
