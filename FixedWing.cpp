#include "FixedWing.hpp"
#include <iostream>

FixedWing::FixedWing(int type)
{
    state.setZero(12);
    switch(type)
    {
        case 0:
            parameters = FixedWingAerosondeParameters();
            break;
        default:
            parameters = FixedWingAerosondeParameters();
            break;
    }
    controlThresholds(0, 0) = math_tools::degrees2Radians(-25);
    controlThresholds(1, 0) = math_tools::degrees2Radians(25);
    controlThresholds(0, 1) = math_tools::degrees2Radians(-25);
    controlThresholds(1, 1) = math_tools::degrees2Radians(25);
    controlThresholds(0, 2) = math_tools::degrees2Radians(-25);
    controlThresholds(1, 2) = math_tools::degrees2Radians(25);
    controlThresholds(0, 3) = 0.0;
    controlThresholds(1, 3) = 1.0;
}

void FixedWing::update(float deltaTime)
{
    calculate_forces_and_moments();

    state[0] = position[0];
    state[1] = position[1];
    state[2] = position[2];

}

Eigen::VectorXf get_derivatives(Eigen::VectorXf state, Eigen::Vector3f forces, Eigen::Vector3f moments)
{
    ;
}

void FixedWing::calculate_forces_and_moments()
{
    forces = math_tools::rotationInertial2Body(state[6], state[7], state[8])*Eigen::Vector3f{0.0, 0.0, -parameters.mass*gravity};
    moments *= 0;
    calculate_propulsion_forces_and_moments();
//    calculate_aerodynamic_forces_and_moments();
}

void FixedWing::calculate_propulsion_forces_and_moments()
{
    Eigen::Vector3f bodyVelocity{state[0], state[1], state[2]};
    Eigen::Vector3f bodyWind{math_tools::rotationInertial2Body(state[6], state[7], state[8]) * wind};
    float Va{(bodyVelocity - bodyWind).norm()};
    float forcePropulsion{0.5*parameters.propS*parameters.propC*(pow((parameters.kMotor*control[3]), 2) - pow(Va, 2))};

    forces[0] += forcePropulsion;

    float momentPropulsion{-parameters.kTP*pow(parameters.kOmega*control[3], 2)};
    moments[0] = momentPropulsion;
}

void FixedWing::calculate_aerodynamic_forces_and_moments()
{
//    Eigen::Vector3f bodyVelocity{state[0], state[1], state[2]};
//    Eigen::Vector3f bodyWind{math_tools::rotationInertial2Body(state[6], state[7], state[8]) * wind};
//    Eigen::Vector3f relativeBodyAirspeedVelocity{bodyVelocity - bodyWind};
//    float Va{relativeBodyAirspeedVelocity.norm()};

//    float alpha{atan(relativeBodyAirspeedVelocity[2]/relativeBodyAirspeedVelocity[0])};
//    float beta{asin(relativeBodyAirspeedVelocity[1]/Va)};

//    float cL{parameters.cL.O + parameters.cL.alpha*alpha};
//    float cD{parameters.cD.O + parameters.cD.alpha*alpha};

//    float aerodynamicCoefficient{0.5*parameters.rho*pow(Va, 2)*parameters.wingS};

//    float forceLift{aerodynamicCoefficient*(cL + parameters.cL.q*parameters.wingC/(2.0*Va)*state[10] + parameters.cL.deltaE*control[1])};
//    float forceDrag{aerodynamicCoefficient*(cD + parameters.cD.q*parameters.wingC/(2.0*Va)*state[10] + parameters.cD.deltaE*control[1])};

//    Eigen::Vector3f aerodynamicForces;
//    aerodynamicForces[0] = -forceDrag*cos(alpha) + forceLift*sin(alpha);
//    aerodynamicForces[2] = -forceDrag*sin(alpha) - forceLift*cos(alpha);
//    aerodynamicForces[1] = forceCoefficient*(parameters.cY.O + parameters.cY.beta*beta + parameters.cY.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cY.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cY.deltaA*control[0] + parameters.cY.deltaR*control[2]);

//    forces[0] += aerodynamicForces;

//    Eigen::Vector3f aerodynamicMoments;
//    aerodynamicMoments[0] = aerodynamicCoefficient*parameters.wingB*(parameters.cell.O + parameters.cell.beta*beta + parameters.cell.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cell.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cell.deltaA*control[0] + parameters.cell.deltaR*control[2]);
//    aerodynamicMoments[2] = aerodynamicCoefficient*parameters.wingB*(parameters.cn.O + parameters.cn.beta*beta + parameters.cn.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cn.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cn.deltaA*control[0] + parameters.cn.deltaR*control[2]);
//    aerodynamicMoments[1] = aerodynamicCoefficient*parameters.wingC(parameters.cm.O + parameters.cm.alpha*alpha + parameters.cm.q*parameters.wingC/(2.0*Va)*state[10] + parameters.cm.deltaE*control[1]);
}

Eigen::Vector3f FixedWing::get_position() const
{
    return Eigen::Vector3f{state[0], state[1], state[2]};
}

Eigen::Vector3f FixedWing::get_orientation() const
{
    return Eigen::Vector3f{state[6], state[7], state[8]};
}

Eigen::Vector4f FixedWing::get_control() const
{
    return control;
}

Eigen::Vector3f FixedWing::get_wind() const
{
    return wind;
}

float FixedWing::get_gravity() const
{
    return gravity;
}

void FixedWing::set_control(Eigen::Vector4f controlInput)
{
    Eigen::Vector4f saturatedControl;
    for(int index{0}; index < 4; index++)
    {
        saturatedControl[index] = math_tools::saturate(controlInput[index], controlThresholds(0, index), controlThresholds(1, index));
    }
    control = saturatedControl;
}

void FixedWing::set_wind(Eigen::Vector3f windInput)
{
    wind = windInput;
}

void FixedWing::set_gravity(float gravityInput)
{
    gravity = gravityInput;
}

void FixedWing::set_initial_velocity(float inertialVelocityInput)
{
    state[3] = inertialVelocityInput;
}
