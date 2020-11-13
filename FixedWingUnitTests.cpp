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

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultVelocity_ExpectCorrectValues)
{
     EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_velocity(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAcceleration_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_acceleration(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultOrientation_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_orientation(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAngularVelocity_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_angular_velocity(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultAngularAcceleration_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_angular_acceleration(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultWind_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_wind(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingInputs_ExpectCorrectValues)
{
    EXPECT_VECTOR4_FLOAT_EQ(fixedWing.get_inputs(), Eigen::Vector4f{0.0, 0.0, 0.0, 0.0});
}

TEST_F(FixedWingTests, WhenSettingFixedWingWind_ExpectCorrectValues)
{
    fixedWing.set_wind(ones);

    EXPECT_VECTOR3_FLOAT_EQ(fixedWing.get_wind(), ones);
}

TEST_F(FixedWingTests, WhenSettingFixedWingInputs_ExpectCorrectValues)
{
    Eigen::Vector4f inputsExpected{1.0, 1.0, 1.0, 1.0};

    fixedWing.set_inputs(inputsExpected);

    EXPECT_VECTOR4_FLOAT_EQ(fixedWing.get_inputs(), inputsExpected);
}

