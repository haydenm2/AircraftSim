#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "AircraftPhysics.hpp"


class AircraftPhysicsTests : public ::testing::Test, public AircraftPhysics
{
protected:
    FixedWingParameters parameters{FixedWingEMBParameters()};
    Eigen::Vector3f zeros3{0.0, 0.0, 0.0};
    Eigen::Vector3f ones3{1.0, 1.0, 1.0};
    float threshold{1e-5};
    float gravity{9.81};
};

TEST_F(AircraftPhysicsTests, WhenRequestingAircraftPointer_ExpectValidPointer)
{
    EXPECT_FALSE(get_aircraft_ptr() == nullptr);
}

TEST_F(AircraftPhysicsTests, WhenUpdatingWithNoTimeStep_ExpectNoChanges)
{
    Eigen::Vector4f controlExpected{0.0, 0.032, 0.0, 0.78144714};
    float deltaTime{0.0};

    update(deltaTime);

    EXPECT_VECTOR3_FLOAT_NEAR(get_aircraft_ptr()->get_position(), zeros3, threshold);
    EXPECT_VECTOR3_FLOAT_NEAR(get_aircraft_ptr()->get_orientation(), zeros3, threshold);
    EXPECT_VECTOR3_FLOAT_NEAR(get_aircraft_ptr()->get_wind(), zeros3, threshold);
    EXPECT_VECTOR4_FLOAT_NEAR(get_aircraft_ptr()->get_control(), controlExpected, threshold);
}

TEST_F(AircraftPhysicsTests, WhenGettingDefaultAircraftPosition_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(get_position(), zeros3);
}

TEST_F(AircraftPhysicsTests, WhenGettingDefaultAircraftOrientation_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(get_orientation(), zeros3);
}

TEST_F(AircraftPhysicsTests, WhenSettingAircraftWind_ExpectCorrectValues)
{
    set_wind(ones3);

    EXPECT_VECTOR3_FLOAT_EQ(get_aircraft_ptr()->get_wind(), ones3);
}

TEST_F(AircraftPhysicsTests, WhenSettingAircraftControl_ExpectCorrectValues)
{
    Eigen::Vector4f controlExpected{Eigen::Vector4f{0.1, 0.1, 0.1, 0.1}};

    set_control(controlExpected);

    EXPECT_VECTOR4_FLOAT_EQ(get_aircraft_ptr()->get_control(), controlExpected);
}

TEST_F(AircraftPhysicsTests, WhenGettingDefaultGravity_ExpectCorrectValue)
{
    EXPECT_EQ(get_gravity(), gravity);
}

TEST_F(AircraftPhysicsTests, WhenSettingGravity_ExpectCorrectValue)
{
    float gravityExpected{20.0};

    set_gravity(gravityExpected);

    EXPECT_EQ(get_gravity(), gravityExpected);
}

TEST_F(AircraftPhysicsTests, WhenResettingAircraft_ExpectInitializedStatesAndValidPointer)
{
    set_control(Eigen::Vector4f{1.0, 1.0, 1.0, 1.0});
    set_gravity(100.0);
    set_wind(ones3);
    update(10.0);

    reset();

    EXPECT_FALSE(get_aircraft_ptr() == nullptr);
    EXPECT_EQ(get_gravity(), gravity);
    EXPECT_VECTOR3_FLOAT_EQ(get_wind(), zeros3);
    EXPECT_VECTOR3_FLOAT_EQ(get_position(), zeros3);
    EXPECT_VECTOR3_FLOAT_EQ(get_orientation(), zeros3);
}

TEST_F(AircraftPhysicsTests, WhenChangingFixedWingAircraftToEMB12_ExpectCorrectAircraftType)
{
    FixedWing *fixedWingPtr = dynamic_cast<FixedWing *>(get_aircraft_ptr());
    change_fixed_wing(FixedWing::EMB312);

    EXPECT_EQ(fixedWingPtr->fixedWingType, FixedWing::EMB312);
}

TEST_F(AircraftPhysicsTests, WhenChangingFixedWingAircraftToEMB14_ExpectCorrectAircraftType)
{
    FixedWing *fixedWingPtr = dynamic_cast<FixedWing *>(get_aircraft_ptr());
    change_fixed_wing(FixedWing::EMB314);

    EXPECT_EQ(fixedWingPtr->fixedWingType, FixedWing::EMB314);
}

TEST_F(AircraftPhysicsTests, WhenChangingFixedWingAircraftToF16_ExpectCorrectAircraftType)
{
    FixedWing *fixedWingPtr = dynamic_cast<FixedWing *>(get_aircraft_ptr());
    change_fixed_wing(FixedWing::F16D);

    EXPECT_EQ(fixedWingPtr->fixedWingType, FixedWing::F16D);
}

TEST_F(AircraftPhysicsTests, WhenChangingFixedWingAircraftToMQ9_ExpectCorrectAircraftType)
{
    FixedWing *fixedWingPtr = dynamic_cast<FixedWing *>(get_aircraft_ptr());
    change_fixed_wing(FixedWing::MQ9);

    EXPECT_EQ(fixedWingPtr->fixedWingType, FixedWing::MQ9);
}

TEST_F(AircraftPhysicsTests, WhenTogglingWindFalse_ExpectCorrectBoolean)
{
    toggle_wind(false);

    EXPECT_EQ(windActive, false);
}

TEST_F(AircraftPhysicsTests, WhenTogglingWindTrue_ExpectCorrectBoolean)
{
    toggle_wind(true);

    EXPECT_EQ(windActive, true);
}

TEST_F(AircraftPhysicsTests, WhenTogglingWindToTrueAndCheckingIfWindIsActive_ExpectCorrectBoolean)
{
    toggle_wind(true);

    EXPECT_EQ(isWindActive(), true);
}


