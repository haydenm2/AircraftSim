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
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getPosition()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultVelocity_ExpectCorrectValues)
{
     EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getVelocity()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAcceleration_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAcceleration()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultOrientation_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getOrientation()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAngularVelocity_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAngularVelocity()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAngularAcceleration_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAngularAcceleration()), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultWind_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getWind()), zeros);
}

TEST_F(FixedWingTests, WhenSettingFixedWingPosition_ExpectCorrectValues)
{
    fixedWing.setPosition(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getPosition()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingVelocity_ExpectCorrectValues)
{
    fixedWing.setVelocity(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getVelocity()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingAcceleration_ExpectCorrectValues)
{
    fixedWing.setAcceleration(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAcceleration()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingOrientation_ExpectCorrectValues)
{
    fixedWing.setOrientation(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getOrientation()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingAngularVelocity_ExpectCorrectValues)
{
    fixedWing.setAngularVelocity(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAngularVelocity()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingAngularAcceleration_ExpectCorrectValues)
{
    fixedWing.setAngularAcceleration(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAngularAcceleration()), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingWind_ExpectCorrectValues)
{
    fixedWing.setWind(ones);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getWind()), ones);
}

