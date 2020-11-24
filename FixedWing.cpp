#include "FixedWing.hpp"
#include <iostream>

FixedWing::FixedWing(FixedWingType type)
{
    fixedWingType = type;
    state.setZero(12);
    switch(type)
    {
        case FixedWingType::EMB312:
            parameters = FixedWingEMBParameters();
            break;
        case FixedWingType::EMB314:
            parameters = FixedWingEMBParameters();
            break;
        case FixedWingType::F16D:
            parameters = FixedWingF16Parameters();
            break;
        case FixedWingType::MQ9:
            parameters = FixedWingMQ9Parameters();
            break;
        default:
            parameters = FixedWingEMBParameters();
            break;
    }
    controlThresholds(0, 0) = math_tools::degrees_to_radians(-25);
    controlThresholds(1, 0) = math_tools::degrees_to_radians(25);
    controlThresholds(0, 1) = math_tools::degrees_to_radians(-25);
    controlThresholds(1, 1) = math_tools::degrees_to_radians(25);
    controlThresholds(0, 2) = math_tools::degrees_to_radians(-25);
    controlThresholds(1, 2) = math_tools::degrees_to_radians(25);
    controlThresholds(0, 3) = 0.0;
    controlThresholds(1, 3) = 1.0;

    float gamma{parameters.Jx*parameters.Jz - powf(parameters.Jxz, 2)};
    gamma1 = parameters.Jxz*(parameters.Jx - parameters.Jy + parameters.Jz)/gamma;
    gamma2 = (parameters.Jz*(parameters.Jz - parameters.Jy) + pow(parameters.Jxz, 2))/gamma;
    gamma3 = parameters.Jz/gamma;
    gamma4 = parameters.Jxz/gamma;
    gamma5 = (parameters.Jz - parameters.Jx)/parameters.Jy;
    gamma6 = parameters.Jxz/parameters.Jy;
    gamma7 = ((parameters.Jx - parameters.Jy)*parameters.Jx + pow(parameters.Jxz, 2))/gamma;
    gamma8 = parameters.Jx/gamma;

    set_initial_velocity(parameters.Va0);
    set_control(Eigen::Vector4f{parameters.deltaA0, parameters.deltaE0, parameters.deltaR0, parameters.deltaT0});
}

void FixedWing::update(float deltaTime)
{
    calculate_velocities();
    calculate_forces_and_moments();
    propogate_states(state, forces, moments, deltaTime);
}

void FixedWing::propogate_states(Eigen::VectorXf &state, const Eigen::Vector3f &forces, const Eigen::Vector3f &moments, float deltaTime)
{
    Eigen::VectorXf k1{get_derivatives(state, forces, moments)};
    Eigen::VectorXf k2{get_derivatives(state + deltaTime/2.0*k1, forces, moments)};
    Eigen::VectorXf k3{get_derivatives(state + deltaTime/2.0*k2, forces, moments)};
    Eigen::VectorXf k4{get_derivatives(state + deltaTime*k3, forces, moments)};

    state += deltaTime/6.0*(k1 + 2*k2 + 2*k3 + k4);
}

Eigen::VectorXf FixedWing::get_derivatives(const Eigen::VectorXf &state, const Eigen::Vector3f &forces, const Eigen::Vector3f &moments) const
{
    Eigen::VectorXf stateDot{Eigen::VectorXf(12)};
    Eigen::Vector3f bodyVelocity{state[3], state[4], state[5]};
    Eigen::Vector3f positionDot{math_tools::rotation_body_to_inertial(state[6], state[7], state[8])*bodyVelocity};

    Eigen::Vector3f coriolisForces{(state[11]*state[4] - state[10]*state[5]), (state[9]*state[5] - state[11]*state[3]), (state[10]*state[3] - state[9]*state[4])};
    Eigen::Vector3f bodyVelocityDot{coriolisForces + 1/parameters.mass*forces};

    Eigen::Vector3f angularVelocities{state[9], state[10], state[11]};
    Eigen::Matrix3f rotationBodyToEulerFrame;
    rotationBodyToEulerFrame(0, 0) = 1;
    rotationBodyToEulerFrame(0, 1) = sin(state[6])*tan(state[7]);
    rotationBodyToEulerFrame(0, 2) = cos(state[6])*tan(state[7]);
    rotationBodyToEulerFrame(1, 0) = 0;
    rotationBodyToEulerFrame(1, 1) = cos(state[6]);
    rotationBodyToEulerFrame(1, 2) = -sin(state[6]);
    rotationBodyToEulerFrame(2, 0) = 0;
    rotationBodyToEulerFrame(2, 1) = sin(state[6])/cos(state[7]);
    rotationBodyToEulerFrame(2, 2) = cos(state[6])/cos(state[7]);
    Eigen::Vector3f orientationDot{rotationBodyToEulerFrame*angularVelocities};

    Eigen::Vector3f angularVelocityDot;
    angularVelocityDot[0] = gamma1*state[9]*state[10] - gamma2*state[10]*state[11] + gamma3*moments[0] + gamma4*moments[2];
    angularVelocityDot[1] = gamma5*state[9]*state[11] - gamma6*(pow(state[9], 2) - pow(state[11], 2)) + 1/parameters.Jy*moments[1];
    angularVelocityDot[2] = gamma7*state[9]*state[10] - gamma1*state[10]*state[11] + gamma4*moments[0] + gamma8*moments[2];

    stateDot << positionDot, bodyVelocityDot, orientationDot, angularVelocityDot;

    return stateDot;
}

void FixedWing::calculate_forces_and_moments()
{
    forces = math_tools::rotation_inertial_to_body(state[6], state[7], state[8])*Eigen::Vector3f{0.0, 0.0, -parameters.mass*gravity};
    moments *= 0;
    calculate_propulsion_forces_and_moments();
    calculate_aerodynamic_forces_and_moments();
}

void FixedWing::calculate_velocities()
{
    Eigen::Vector3f bodyVelocity{state[3], state[4], state[5]};
    Eigen::Vector3f bodyWind{math_tools::rotation_inertial_to_body(state[6], state[7], state[8]) * wind};
    relativeBodyAirspeedVelocity = bodyVelocity - bodyWind;
    Va = relativeBodyAirspeedVelocity.norm();
}

void FixedWing::calculate_propulsion_forces_and_moments()
{
    float forcePropulsion{0.5f*parameters.propS*parameters.propC*(powf((parameters.kMotor*control[3]), 2) - powf(Va, 2))};
    forces[0] += forcePropulsion;

    float momentPropulsion{-parameters.kTP*powf(parameters.kOmega*control[3], 2)};
    moments[0] += momentPropulsion;
}

void FixedWing::calculate_aerodynamic_forces_and_moments()
{
    if(Va != 0)
    {
        float alpha{atan(relativeBodyAirspeedVelocity[2]/relativeBodyAirspeedVelocity[0])};
        float beta{asin(relativeBodyAirspeedVelocity[1]/Va)};

        float cL{parameters.cL.O + parameters.cL.alpha*alpha};
        float cD{parameters.cD.O + parameters.cD.alpha*alpha};

        float aerodynamicCoefficient{0.5f*parameters.rho*powf(Va, 2)*parameters.wingS};

        float forceLift{aerodynamicCoefficient*(cL + parameters.cL.q*parameters.wingC/(2.0f*Va)*state[10] + parameters.cL.deltaE*control[1])};
        float forceDrag{aerodynamicCoefficient*(cD + parameters.cD.q*parameters.wingC/(2.0f*Va)*state[10] + parameters.cD.deltaE*control[1])};

        Eigen::Vector3f aerodynamicForces;
        aerodynamicForces[0] = -forceDrag*cos(alpha) + forceLift*sin(alpha);
        aerodynamicForces[1] = aerodynamicCoefficient*(parameters.cY.O + parameters.cY.beta*beta + parameters.cY.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cY.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cY.deltaA*control[0] + parameters.cY.deltaR*control[2]);
        aerodynamicForces[2] = -forceDrag*sin(alpha) - forceLift*cos(alpha);

        forces += aerodynamicForces;

        Eigen::Vector3f aerodynamicMoments;
        aerodynamicMoments[0] = aerodynamicCoefficient*parameters.wingB*(parameters.cell.O + parameters.cell.beta*beta + parameters.cell.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cell.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cell.deltaA*control[0] + parameters.cell.deltaR*control[2]);
        aerodynamicMoments[1] = aerodynamicCoefficient*parameters.wingC*(parameters.cm.O + parameters.cm.alpha*alpha + parameters.cm.q*parameters.wingC/(2.0*Va)*state[10] + parameters.cm.deltaE*control[1]);
        aerodynamicMoments[2] = aerodynamicCoefficient*parameters.wingB*(parameters.cn.O + parameters.cn.beta*beta + parameters.cn.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cn.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cn.deltaA*control[0] + parameters.cn.deltaR*control[2]);
        moments += aerodynamicMoments;
    }
    else
    {
    }
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

Eigen::Vector3f FixedWing::get_velocity() const
{
    return Eigen::Vector3f{state[3], state[4], state[5]};
}

Eigen::VectorXf FixedWing::get_state() const
{
    return state;
}

FixedWingParameters FixedWing::get_parameters() const
{
    return parameters;
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
