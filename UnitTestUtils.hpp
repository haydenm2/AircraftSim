#ifndef UNIT_TEST_UTILS_HPP
#define UNIT_TEST_UTILS_HPP

#include "gtest/gtest.h"
#include <eigen3/Eigen/Dense>

void EXPECT_VECTOR3_FLOAT_EQ(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector);
void EXPECT_VECTOR4_FLOAT_EQ(Eigen::Vector4f inputVector, Eigen::Vector4f truthVector);

#endif
