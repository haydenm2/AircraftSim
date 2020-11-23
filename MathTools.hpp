#ifndef MATH_TOOLS_HPP
#define MATH_TOOLS_HPP

#include <math.h>

#include <Eigen/Dense>
#include <Eigen/Geometry>


namespace math_tools
{

// TODO: Correct function names to snake case
float radians2Degrees(float radianInput);
float degrees2Radians(float degreeInput);
float saturate(float input, float minimum, float maximum);
Eigen::Matrix3f rotationBody2Inertial(float roll, float pitch, float yaw);
Eigen::Matrix3f rotationInertial2Body(float roll, float pitch, float yaw);
Eigen::Quaternion<float> get_quaternion_between_vectors(Eigen::Vector3f originalVector, Eigen::Vector3f desiredVector);

}

#endif
