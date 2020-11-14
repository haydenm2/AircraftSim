#include "gtest/gtest.h"
#include "MathTools.hpp"
#include "UnitTestUtils.hpp"


TEST(MathToolsTests, WhenConvertingToDegrees_ExpectCorrectValue)
{
    float inputRadians{1.0};
    float expectedDegrees{inputRadians*180.0f/M_PI};

    EXPECT_EQ(math_tools::radians2Degrees(inputRadians), expectedDegrees);
}

TEST(MathToolsTests, WhenConvertingToRadians_ExpectCorrectValue)
{
    float inputDegrees{10.0};
    float expectedRadians{inputDegrees*M_PI/180.0f};

    EXPECT_EQ(math_tools::degrees2Radians(inputDegrees), expectedRadians);
}

TEST(MathToolsTests, WhenSaturatingValueInRange_ExpectSameValue)
{
    float input{5.0};
    float minimum{-10.0};
    float maximum{10.0};

    float output{math_tools::saturate(input, minimum, maximum)};

    EXPECT_EQ(output, input);
}

TEST(MathToolsTests, WhenSaturatingValueAboveRange_ExpectMaximum)
{
    float input{15.0};
    float minimum{-10.0};
    float maximum{10.0};

    float output{math_tools::saturate(input, minimum, maximum)};

    EXPECT_EQ(output, maximum);
}

TEST(MathToolsTests, WhenSaturatingValueBelowRange_ExpectMinimum)
{
    float input{-15.0};
    float minimum{-10.0};
    float maximum{10.0};

    float output{math_tools::saturate(input, minimum, maximum)};

    EXPECT_EQ(output, minimum);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorRoll90DegreesToBody_ExpectXUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{1.0, 0.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotationInertial2Body(math_tools::degrees2Radians(90), 0.0, 0.0)};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorPitch90DegreesToBody_ExpectZUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{0.0, 0.0, 1.0};

    Eigen::Matrix3f R{math_tools::rotationInertial2Body(0.0, math_tools::degrees2Radians(90), 0.0)};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorYaw90DegreesToBody_ExpectYUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{0.0, -1.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotationInertial2Body(0.0, 0.0, math_tools::degrees2Radians(90))};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorRoll90DegreesToBodyAndBack_ExpectXUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{1.0, 0.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotationInertial2Body(math_tools::degrees2Radians(90), 0.0, 0.0) * math_tools::rotationBody2Inertial(math_tools::degrees2Radians(90), 0.0, 0.0)};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorPitch90DegreesToBodyAndBack_ExpectXUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{1.0, 0.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotationInertial2Body(0.0, math_tools::degrees2Radians(90), 0.0) * math_tools::rotationBody2Inertial(0.0, math_tools::degrees2Radians(90), 0.0)};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorYaw90DegreesToBodyAndBack_ExpectXUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{1.0, 0.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotationInertial2Body(0.0, 0.0, math_tools::degrees2Radians(90)) * math_tools::rotationBody2Inertial(0.0, 0.0, math_tools::degrees2Radians(90))};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}
