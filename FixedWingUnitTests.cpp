#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "FixedWing.hpp"


TEST(FixedWingTests, WhenGettingFixedWingDefaultPosition_ExpectCorrectValues)
{
    Eigen::Vector3f positionExpected{0.0, 0.0, 0.0};

    FixedWing fixedWing;

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getPosition()), positionExpected);
}

TEST(FixedWingTests, WhenGettingFixedWingDefaultVelocity_ExpectCorrectValues)
{
    Eigen::Vector3f velocityExpected{0.0, 0.0, 0.0};

    FixedWing fixedWing;

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getVelocity()), velocityExpected);
}

TEST(FixedWingTests, WhenGettingFixedWingDefaultAcceleration_ExpectCorrectValues)
{
    Eigen::Vector3f accelerationExpected{0.0, 0.0, 0.0};

    FixedWing fixedWing;

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAcceleration()), accelerationExpected);
}

TEST(FixedWingTests, WhenGettingFixedWingDefaultOrientation_ExpectCorrectValues)
{
    Eigen::Vector3f orientationExpected{0.0, 0.0, 0.0};

    FixedWing fixedWing;

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getOrientation()), orientationExpected);
}

TEST(FixedWingTests, WhenGettingFixedWingDefaultAngularVelocity_ExpectCorrectValues)
{
    Eigen::Vector3f angularVeclocityExpected{0.0, 0.0, 0.0};

    FixedWing fixedWing;

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAngularVelocity()), angularVeclocityExpected);
}

TEST(FixedWingTests, WhenGettingFixedWingDefaultAngularAcceleration_ExpectCorrectValues)
{
    Eigen::Vector3f angularAccelerationExpected{0.0, 0.0, 0.0};

    FixedWing fixedWing;

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAngularAcceleration()), angularAccelerationExpected);
}

TEST(FixedWingTests, WhenGettingFixedWingDefaultWind_ExpectCorrectValues)
{
    Eigen::Vector3f windExpected{0.0, 0.0, 0.0};

    FixedWing fixedWing;

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getWind()), windExpected);
}

TEST(FixedWingTests, WhenSettingFixedWingPosition_ExpectCorrectValues)
{
    Eigen::Vector3f positionExpected{1.0, 1.0, 1.0};

    FixedWing fixedWing;
    fixedWing.setPosition(positionExpected);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getPosition()), positionExpected);
}

TEST(FixedWingTests, WhenSettingFixedWingVelocity_ExpectCorrectValues)
{
    Eigen::Vector3f velocityExpected{1.0, 1.0, 1.0};

    FixedWing fixedWing;
    fixedWing.setVelocity(velocityExpected);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getVelocity()), velocityExpected);
}

TEST(FixedWingTests, WhenSettingFixedWingAcceleration_ExpectCorrectValues)
{
    Eigen::Vector3f accelerationExpected{1.0, 1.0, 1.0};

    FixedWing fixedWing;
    fixedWing.setAcceleration(accelerationExpected);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAcceleration()), accelerationExpected);
}

TEST(FixedWingTests, WhenSettingFixedWingOrientation_ExpectCorrectValues)
{
    Eigen::Vector3f orientationExpected{1.0, 1.0, 1.0};

    FixedWing fixedWing;
    fixedWing.setOrientation(orientationExpected);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getOrientation()), orientationExpected);
}

TEST(FixedWingTests, WhenSettingFixedWingAngularVelocity_ExpectCorrectValues)
{
    Eigen::Vector3f angularVeclocityExpected{1.0, 1.0, 1.0};

    FixedWing fixedWing;
    fixedWing.setAngularVelocity(angularVeclocityExpected);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAngularVelocity()), angularVeclocityExpected);
}

TEST(FixedWingTests, WhenSettingFixedWingAngularAcceleration_ExpectCorrectValues)
{
    Eigen::Vector3f angularAccelerationExpected{1.0, 1.0, 1.0};

    FixedWing fixedWing;
    fixedWing.setAngularAcceleration(angularAccelerationExpected);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getAngularAcceleration()), angularAccelerationExpected);
}

TEST(FixedWingTests, WhenSettingFixedWingWind_ExpectCorrectValues)
{
    Eigen::Vector3f windExpected{1.0, 1.0, 1.0};

    FixedWing fixedWing;
    fixedWing.setWind(windExpected);

    EXPECT_VECTOR3_FLOAT_EQ(*(fixedWing.getWind()), windExpected);
}

