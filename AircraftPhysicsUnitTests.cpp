#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "AircraftPhysics.hpp"


class AircraftPhysicsTests : public ::testing::Test
{
protected:
    AircraftPhysics physics;
    FixedWingParameters parameters{FixedWingAerosondeParameters()};
    Eigen::Vector3f zeros3{0.0, 0.0, 0.0};
    Eigen::Vector3f ones3{1.0, 1.0, 1.0};
    Eigen::Vector4f zeros4{0.0, 0.0, 0.0, 0.0};
    Eigen::Vector4f ones4{1.0, 1.0, 1.0, 1.0};
    float threshold{1e-5};
    float gravity{9.81};
};

TEST_F(AircraftPhysicsTests, WhenRequestingAircraftPointer_ExpectValidPointer)
{
    EXPECT_FALSE(physics.get_aircraft_ptr() == nullptr);
}

TEST_F(AircraftPhysicsTests, WhenUpdatingWithNoTimeStep_ExpectNoChanges)
{
    Eigen::Vector3f accelerationExpected{0.0, 0.0, -gravity};
    float deltaTime{0.0};

    physics.update(deltaTime);

    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_position(), zeros3, threshold);
    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_orientation(), zeros3, threshold);
    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_wind(), zeros3, threshold);
    EXPECT_VECTOR4_FLOAT_NEAR(physics.get_aircraft_ptr()->get_control(), zeros4, threshold);
}

//TEST_F(AircraftPhysicsTests, WhenUpdatingWithTimeStepAndOnlyGravity_ExpectCorrectStateUpdates)
//{
//    float deltaTime{1.0};
//    Eigen::Vector3f accelerationExpected{0.0, 0.0, -gravity};
//    Eigen::Vector3f velocityExpected{accelerationExpected*deltaTime};
//    Eigen::Vector3f positionExpected{velocityExpected*deltaTime + 0.5*accelerationExpected*pow(deltaTime,2)};

//    physics.update(deltaTime);

//    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_position(), positionExpected, threshold);
//    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_velocity(), velocityExpected, threshold);
//    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_acceleration(), accelerationExpected, threshold);
//}

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
    Eigen::Vector4f controlExpected{Eigen::Vector4f{0.1, 0.1, 0.1, 0.1}};

    physics.set_control(controlExpected);

    EXPECT_VECTOR4_FLOAT_EQ(physics.get_aircraft_ptr()->get_control(), controlExpected);
}

TEST_F(AircraftPhysicsTests, WhenGettingDefaultGravity_ExpectCorrectValue)
{
    EXPECT_EQ(physics.get_gravity(), gravity);
}

TEST_F(AircraftPhysicsTests, WhenSettingGravity_ExpectCorrectValue)
{
    float gravityExpected{20.0};

    physics.set_gravity(gravityExpected);

    EXPECT_EQ(physics.get_gravity(), gravityExpected);
}

//TEST_F(AircraftPhysicsTests, WhenUpdatingAerosondeWithTimeStepWithGravityAndPropulsion_ExpectCorrectStateUpdates)
//{
//    float deltaTime{1.0};

//    Eigen::Vector4f controlInput{Eigen::Vector4f{0, 0, 0, 0.5}};
//    physics.set_control(controlInput);

//    Eigen::Vector3f accelerationGravity{0.0, 0.0, -gravity};
//    Eigen::Vector3f accelerationPropulsion{(0.5*parameters.propS*parameters.propC*pow((parameters.kMotor*controlInput[3]), 2))/parameters.mass, 0.0, 0.0};

//    Eigen::Vector3f accelerationExpected{accelerationGravity + accelerationPropulsion};
//    Eigen::Vector3f velocityExpected{accelerationExpected*deltaTime};
//    Eigen::Vector3f positionExpected{velocityExpected*deltaTime + 0.5*accelerationExpected*pow(deltaTime,2)};

//    physics.update(deltaTime);

//    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_position(), positionExpected, threshold);
//    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_velocity(), velocityExpected, threshold);
//    EXPECT_VECTOR3_FLOAT_NEAR(physics.get_aircraft_ptr()->get_acceleration(), accelerationExpected, threshold);
//}
