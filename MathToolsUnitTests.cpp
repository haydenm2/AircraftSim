#include "gtest/gtest.h"
#include "MathTools.hpp"
#include "UnitTestUtils.hpp"


TEST(MathToolsTests, WhenConvertingToDegrees_ExpectCorrectValue)
{
    float inputRadians{1.0};
    float expectedDegrees{inputRadians*180.0f/M_PI};

    EXPECT_EQ(math_tools::radians_to_degrees(inputRadians), expectedDegrees);
}

TEST(MathToolsTests, WhenConvertingToRadians_ExpectCorrectValue)
{
    float inputDegrees{10.0};
    float expectedRadians{inputDegrees*M_PI/180.0f};

    EXPECT_EQ(math_tools::degrees_to_radians(inputDegrees), expectedRadians);
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

    Eigen::Matrix3f R{math_tools::rotation_inertial_to_body(math_tools::degrees_to_radians(90), 0.0, 0.0)};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorPitch90DegreesToBody_ExpectZUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{0.0, 0.0, 1.0};

    Eigen::Matrix3f R{math_tools::rotation_inertial_to_body(0.0, math_tools::degrees_to_radians(90), 0.0)};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorYaw90DegreesToBody_ExpectYUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{0.0, -1.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotation_inertial_to_body(0.0, 0.0, math_tools::degrees_to_radians(90))};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorRoll90DegreesToBodyAndBack_ExpectXUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{1.0, 0.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotation_inertial_to_body(math_tools::degrees_to_radians(90), 0.0, 0.0) * math_tools::rotation_body_to_inertial(math_tools::degrees_to_radians(90), 0.0, 0.0)};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorPitch90DegreesToBodyAndBack_ExpectXUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{1.0, 0.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotation_inertial_to_body(0.0, math_tools::degrees_to_radians(90), 0.0) * math_tools::rotation_body_to_inertial(0.0, math_tools::degrees_to_radians(90), 0.0)};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenRotatingXUnitVectorYaw90DegreesToBodyAndBack_ExpectXUnitVector)
{
    Eigen::Vector3f input{1.0, 0.0, 0.0};
    Eigen::Vector3f outputExpected{1.0, 0.0, 0.0};

    Eigen::Matrix3f R{math_tools::rotation_inertial_to_body(0.0, 0.0, math_tools::degrees_to_radians(90)) * math_tools::rotation_body_to_inertial(0.0, 0.0, math_tools::degrees_to_radians(90))};
    Eigen::Vector3f output{R*input};

    EXPECT_VECTOR3_FLOAT_NEAR(output, outputExpected, 1e-5);
}

TEST(MathToolsTests, WhenDefiningQuaternionBetweenSameVectors_ExpectNoRotation)
{
    Eigen::Vector3f inputVector1{1.0, 0.0, 0.0};
    Eigen::Vector3f inputVector2{1.0, 0.0, 0.0};

    Eigen::Quaternion<float> rotation{math_tools::get_quaternion_between_vectors(inputVector1, inputVector2)};

    EXPECT_NEAR(rotation.x(), 0.0, 1e-5);
    EXPECT_NEAR(rotation.y(), 0.0, 1e-5);
    EXPECT_NEAR(rotation.z(), 0.0, 1e-5);
    EXPECT_NEAR(rotation.w(), 1.0, 1e-5);
}

TEST(MathToolsTests, WhenDefiningQuaternionBetweenOppositeParallelVectors_Expect180DegreeRotation)
{
    Eigen::Vector3f inputVector1{1.0, 0.0, 0.0};
    Eigen::Vector3f inputVector2{-1.0, 0.0, 0.0};

    Eigen::Quaternion<float> rotation{math_tools::get_quaternion_between_vectors(inputVector1, inputVector2)};

    EXPECT_NEAR(rotation.x(), 0.0, 1e-5);
    EXPECT_NEAR(rotation.y(), 0.0, 1e-5);
    EXPECT_NEAR(rotation.z(), 1.0, 1e-5);
    EXPECT_NEAR(rotation.w(), 0.0, 1e-5);
}

TEST(MathToolsTests, WhenDefiningQuaternionBetweenRandomUnitVectorsAndApplyingRotationToOriginalVector_ExpectCorrectVectorResult)
{
    Eigen::Vector3f inputVector1{1.0, 0.0, 0.0};
    Eigen::Vector3f inputVector2{0.0, 1.0, 0.0};

    Eigen::Quaternion<float> rotation{math_tools::get_quaternion_between_vectors(inputVector1, inputVector2)};

    Eigen::Vector3f rotatedNormalizedResultVector{(rotation*inputVector1).normalized()};
    EXPECT_VECTOR3_FLOAT_NEAR(rotatedNormalizedResultVector, inputVector2.normalized(), 1e-5);
}

TEST(MathToolsTests, WhenDefiningQuaternionBetweenRandomNonUnitVectorsAndApplyingRotationToOriginalVector_ExpectCorrectVectorResult)
{
    Eigen::Vector3f inputVector1{1.0, 0.0, 0.0};
    Eigen::Vector3f inputVector2{-20.0, 1.0, 10.0};

    Eigen::Quaternion<float> rotation{math_tools::get_quaternion_between_vectors(inputVector1, inputVector2)};

    Eigen::Vector3f rotatedNormalizedResultVector{(rotation*inputVector1).normalized()};
    EXPECT_VECTOR3_FLOAT_NEAR(rotatedNormalizedResultVector, inputVector2.normalized(), 1e-5);
}

