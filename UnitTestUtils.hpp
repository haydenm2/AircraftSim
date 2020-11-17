#ifndef UNIT_TEST_UTILS_HPP
#define UNIT_TEST_UTILS_HPP

#include "gtest/gtest.h"
#include <eigen3/Eigen/Dense>

void EXPECT_VECTOR3_FLOAT_EQ(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector);
void EXPECT_VECTOR4_FLOAT_EQ(Eigen::Vector4f inputVector, Eigen::Vector4f truthVector);
void EXPECT_VECTORX_FLOAT_EQ(Eigen::VectorXf inputVector, Eigen::VectorXf truthVector, int indices);
void EXPECT_VECTOR3_FLOAT_NEAR(Eigen::Vector3f inputVector, Eigen::Vector3f truthVector, float threshold);
void EXPECT_VECTOR4_FLOAT_NEAR(Eigen::Vector4f inputVector, Eigen::Vector4f truthVector, float threshold);

#endif
