#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "FixedWing.hpp"


class FixedWingTests : public ::testing::Test
{
protected:
    FixedWing fixedWing;
    Eigen::Vector3f zeros{0.0, 0.0, 0.0};
    Eigen::Vector3f ones{1.0, 1.0, 1.0};
};

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultPosition_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_position()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultVelocity_ExpectCorrectValues)
{
     EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_velocity()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAcceleration_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_acceleration()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultOrientation_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_orientation()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAngularVelocity_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_angular_velocity()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAngularAcceleration_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_angular_acceleration()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultWind_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_wind()), zeros);
}

TEST_F(FixedWingTests, WhenSettingFixedWingPosition_ExpectCorrectValues)
{
    fixedWing.set_position(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_position()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingVelocity_ExpectCorrectValues)
{
    fixedWing.set_velocity(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_velocity()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingAcceleration_ExpectCorrectValues)
{
    fixedWing.set_acceleration(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_acceleration()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingOrientation_ExpectCorrectValues)
{
    fixedWing.set_orientation(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_orientation()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingAngularVelocity_ExpectCorrectValues)
{
    fixedWing.set_angular_velocity(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_angular_velocity()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingAngularAcceleration_ExpectCorrectValues)
{
    fixedWing.set_angular_acceleration(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_angular_acceleration()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingWind_ExpectCorrectValues)
{
    fixedWing.set_wind(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.get_wind()), ones);
}

