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
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_position(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultOrientation_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_orientation(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultWind_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_wind(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultControl_ExpectCorrectValues)
{
    EXPECT_VECTOR4_FLOAT_EQ(fixedWing.get_control(), Eigen::Vector4f{0.0, 0.032, 0.0, 0.78144714});
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultGravity_ExpectCorrectValue)
{
    EXPECT_EQ(fixedWing.get_gravity(), 9.81f);
}

TEST_F(FixedWingTests, WhenSettingFixedWingWind_ExpectCorrectValues)
{
    fixedWing.set_wind(ones);

    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_wind(), ones);
}

TEST_F(FixedWingTests, WhenGettingFixedWingGravity_ExpectCorrectValue)
{
    float gravityExpected{20.0};

    fixedWing.set_gravity(gravityExpected);

    EXPECT_EQ(fixedWing.get_gravity(), gravityExpected);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultVelocity_ExpectCorrectValues)
{
    Eigen::Vector3f velocityExpected{25.0, 0.0, 0.0};
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_velocity(), velocityExpected);
}

TEST_F(FixedWingTests, WhenSettingFixedWingInitialVelocity_ExpectCorrectValues)
{
    float initialVelocity{150.0};
    Eigen::Vector3f velocityExpected{initialVelocity, 0.0, 0.0};

    fixedWing.set_initial_velocity(initialVelocity);

    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_velocity(), velocityExpected);
}

TEST_F(FixedWingTests, WhenSettingFixedWingControlWithinSaturation_ExpectOriginalValues)
{
    Eigen::Vector4f controlExpected{0.15, 0.15, 0.15, 0.15};

    fixedWing.set_control(controlExpected);

    EXPECT_VECTOR4_FLOAT_EQ(fixedWing.get_control(), controlExpected);
}

TEST_F(FixedWingTests, WhenSettingFixedWingControlBelowSaturation_ExpectMaximumValues)
{
    Eigen::Vector4f controlInput{math_tools::degrees2Radians(-90), math_tools::degrees2Radians(-90), math_tools::degrees2Radians(-90), -10.0};
    Eigen::Vector4f controlExpected{math_tools::degrees2Radians(-25), math_tools::degrees2Radians(-25), math_tools::degrees2Radians(-25), 0.0};

    fixedWing.set_control(controlInput);

    EXPECT_VECTOR4_FLOAT_EQ(fixedWing.get_control(), controlExpected);
}

TEST_F(FixedWingTests, WhenSettingFixedWingControlAboveSaturation_ExpectMaximumValues)
{
    Eigen::Vector4f controlInput{math_tools::degrees2Radians(90), math_tools::degrees2Radians(90), math_tools::degrees2Radians(90), 10.0};
    Eigen::Vector4f controlExpected{math_tools::degrees2Radians(25), math_tools::degrees2Radians(25), math_tools::degrees2Radians(25), 1.0};

    fixedWing.set_control(controlInput);

    EXPECT_VECTOR4_FLOAT_EQ(fixedWing.get_control(), controlExpected);
}
