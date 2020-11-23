#include "MathTools.hpp"
#include <iostream>

namespace math_tools
{

float radians2Degrees(float radianInput)
{
    return radianInput*180.0/M_PI;
}

float degrees2Radians(float degreeInput)
{
    return degreeInput*M_PI/180.0;
}

float saturate(float input, float minimum, float maximum)
{
    float output{input};
    if(input < minimum)
    {
        output = minimum;
    }
    else if(input > maximum)
    {
        output = maximum;
    }
    return output;
}

Eigen::Matrix3f rotationInertial2Body(float phi, float theta, float psi)
{
    Eigen::Matrix3f R;
    R(0, 0) = cos(theta)*cos(psi);
    R(0, 1) = cos(theta)*sin(psi);
    R(0, 2) = -sin(theta);
    R(1, 0) = sin(phi)*sin(theta)*cos(psi) - cos(phi)*sin(psi);
    R(1, 1) = sin(phi)*sin(theta)*sin(psi) + cos(phi)*cos(psi);
    R(1, 2) = sin(phi)*cos(theta);
    R(2, 0) = cos(phi)*sin(theta)*cos(psi) + sin(phi)*sin(psi);
    R(2, 1) = cos(phi)*sin(theta)*sin(psi) - sin(phi)*cos(psi);
    R(2, 2) = cos(phi)*cos(theta);
    return R;
}

Eigen::Matrix3f rotationBody2Inertial(float phi, float theta, float psi)
{
    Eigen::Matrix3f Rb2i = rotationInertial2Body(phi, theta, psi);
    return Rb2i.transpose();
}

Eigen::Quaternion<float> get_quaternion_between_vectors(Eigen::Vector3f originalVector, Eigen::Vector3f desiredVector)
{
    originalVector.normalize();
    desiredVector.normalize();

    Eigen::Quaternion<float> attitude;
    if(originalVector.dot(desiredVector) == -1)
    {
        attitude.x() = 0.0;
        attitude.y() = 0.0;
        attitude.z() = 1.0;
        attitude.w() = 0.0;
    }
    else if(originalVector.dot(desiredVector) == 1)
    {
        attitude.x() = 0.0;
        attitude.y() = 0.0;
        attitude.z() = 0.0;
        attitude.w() = 1.0;
    }
    else
    {
        Eigen::Vector3f quatVectorComponent = originalVector.cross(desiredVector);
        attitude.x() = quatVectorComponent[0];
        attitude.y() = quatVectorComponent[1];
        attitude.z() = quatVectorComponent[2];
        attitude.w() = 1.0 + originalVector.dot(desiredVector);
    }
    return attitude.normalized();
}

}
