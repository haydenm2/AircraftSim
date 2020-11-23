#ifndef MATH_TOOLS_HPP
#define MATH_TOOLS_HPP

#include <math.h>

#include <Eigen/Dense>
#include <Eigen/Geometry>


namespace math_tools
{

float radians_to_degrees(float radianInput);
float degrees_to_radians(float degreeInput);
float saturate(float input, float minimum, float maximum);
Eigen::Matrix3f rotation_body_to_inertial(float roll, float pitch, float yaw);
Eigen::Matrix3f rotation_inertial_to_body(float roll, float pitch, float yaw);
Eigen::Quaternion<float> get_quaternion_between_vectors(Eigen::Vector3f originalVector, Eigen::Vector3f desiredVector);

}

#endif
