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
