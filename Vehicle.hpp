#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <eigen3/Eigen/Dense>


struct Vehicle
{
    Vehicle();
    Vehicle(Eigen::Vector3f positionInit, Eigen::Vector3f velocityInit, Eigen::Vector3f orientationInit, Eigen::Vector3f angularVelocityInit, Eigen::Vector4f controlInputsInit);
    Eigen::Vector3f position;
    Eigen::Vector3f velocity;
    Eigen::Vector3f orientation;
    Eigen::Vector3f angularVelocity;
    Eigen::Vector4f controlInputs;
};

#endif
