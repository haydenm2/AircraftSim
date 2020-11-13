#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "AircraftPhysics.hpp"


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
    EXPECT_VECTOR4_FLOAT_EQ(physics.get_aircraft_ptr()->get_control(), zeros4);
}

TEST_F(AircraftPhysicsTests, WhenUpdatingWithTimeStepAndOnlyGravity_ExpectCorrectStateUpdates)
{
    float deltaTime{0.1};
    Eigen::Vector3f accelerationExpected{0.0, 0.0, -9.81};
    Eigen::Vector3f velocityExpected{accelerationExpected*deltaTime};
    Eigen::Vector3f positionExpected{velocityExpected*deltaTime + 0.5*accelerationExpected*pow(deltaTime,2)};

    physics.update(deltaTime);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_position(), positionExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_velocity(), velocityExpected);
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_acceleration(), accelerationExpected);
}

TEST_F(AircraftPhysicsTests, WhenGettingDefaultAircraftPosition_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_position(), zeros3);
}

TEST_F(AircraftPhysicsTests, WhenGettingDefaultAircraftOrientation_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(physics.get_orientation(), zeros3);
}

TEST_F(AircraftPhysicsTests, WhenSettingAircraftWind_ExpectCorrectValues)
{
    physics.set_wind(ones3);

    EXPECT_VECTOR3_FLOAT_EQ(physics.get_aircraft_ptr()->get_wind(), ones3);
}

TEST_F(AircraftPhysicsTests, WhenSettingAircraftControl_ExpectCorrectValues)
{
    physics.set_control(ones4);

    EXPECT_VECTOR4_FLOAT_EQ(physics.get_aircraft_ptr()->get_control(), ones4);
}

TEST_F(AircraftPhysicsTests, WhenGettingDefaultGravity_ExpectCorrectValue)
{
    EXPECT_EQ(physics.get_gravity(), 9.81f);
}

TEST_F(AircraftPhysicsTests, WhenSettingGravity_ExpectCorrectValue)
{
    float gravityExpected{20.0};

    physics.set_gravity(gravityExpected);

    EXPECT_EQ(physics.get_gravity(), gravityExpected);
}

