#include "UnitTestUtils.hpp"

void EXPECT_VECTOR3_FLOAT_EQ(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector)
{
    for(float index = 0; index < 3; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}

void EXPECT_VECTOR4_FLOAT_EQ(Eigen::Vector4f inputVector, Eigen::Vector4f truthVector)
{
    for(float index = 0; index < 4; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}

void EXPECT_VECTORX_FLOAT_EQ(Eigen::VectorXf inputVector, Eigen::VectorXf truthVector, int indices)
{
    for(float index = 0; index < indices; index++)
    {
        EXPECT_EQ(inputVector[index], truthVector[index]);
    }
}

void EXPECT_VECTOR3_FLOAT_NEAR(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector, float threshold)
{
    for(float index = 0; index < 3; index++)
    {
        EXPECT_NEAR(inputVector[index], truthVector[index], threshold);
    }
}

void EXPECT_VECTOR4_FLOAT_NEAR(Eigen::Vector4f inputVector, Eigen::Vector4f truthVector, float threshold)
{
    for(float index = 0; index < 4; index++)
    {
        EXPECT_NEAR(inputVector[index], truthVector[index], threshold);
    }
}
