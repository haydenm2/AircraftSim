#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "FixedWing.hpp"


class FixedWingTests : public ::testing::Test, public FixedWing::FixedWing
{
protected:
    Eigen::Vector3f zeros{0.0, 0.0, 0.0};
    Eigen::Vector3f ones{1.0, 1.0, 1.0};
};

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultPosition_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(get_position(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultOrientation_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(get_orientation(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultWind_ExpectCorrectValues)
{
    EXPECT_VECTOR3_FLOAT_EQ(get_wind(), zeros);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultControl_ExpectCorrectValues)
{
    EXPECT_VECTOR4_FLOAT_EQ(get_control(), Eigen::Vector4f{0.0, 0.032, 0.0, 0.78144714});
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultGravity_ExpectCorrectValue)
{
    EXPECT_EQ(get_gravity(), 9.81f);
}

TEST_F(FixedWingTests, WhenSettingFixedWingWind_ExpectCorrectValues)
{
    set_wind(ones);

    EXPECT_VECTOR3_FLOAT_EQ(get_wind(), ones);
}

TEST_F(FixedWingTests, WhenGettingFixedWingGravity_ExpectCorrectValue)
{
    float gravityExpected{20.0};

    set_gravity(gravityExpected);

    EXPECT_EQ(get_gravity(), gravityExpected);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultVelocity_ExpectCorrectValues)
{
    Eigen::Vector3f velocityExpected{25.0, 0.0, 0.0};
    EXPECT_VECTOR3_FLOAT_EQ(get_velocity(), velocityExpected);
}

TEST_F(FixedWingTests, WhenGettingFixedWingDefaultState_ExpectCorrectValues)
{
    Eigen::VectorXf stateExpected{Eigen::VectorXf(12)};
    stateExpected.setZero(12);
    stateExpected[3] = 25.0;
    EXPECT_VECTORX_FLOAT_EQ(get_state(), stateExpected, 12);
}

TEST_F(FixedWingTests, WhenSettingFixedWingInitialVelocity_ExpectCorrectValues)
{
    float initialVelocity{150.0};
    Eigen::Vector3f velocityExpected{initialVelocity, 0.0, 0.0};

    set_initial_velocity(initialVelocity);

    EXPECT_VECTOR3_FLOAT_EQ(get_velocity(), velocityExpected);
}

TEST_F(FixedWingTests, WhenSettingFixedWingControlWithinSaturation_ExpectOriginalValues)
{
    Eigen::Vector4f controlExpected{0.15, 0.15, 0.15, 0.15};

    set_control(controlExpected);

    EXPECT_VECTOR4_FLOAT_EQ(get_control(), controlExpected);
}

TEST_F(FixedWingTests, WhenSettingFixedWingControlBelowSaturation_ExpectMaximumValues)
{
    Eigen::Vector4f controlInput{math_tools::degrees_to_radians(-90), math_tools::degrees_to_radians(-90), math_tools::degrees_to_radians(-90), -10.0};
    Eigen::Vector4f controlExpected{math_tools::degrees_to_radians(-25), math_tools::degrees_to_radians(-25), math_tools::degrees_to_radians(-25), 0.0};

    set_control(controlInput);

    EXPECT_VECTOR4_FLOAT_EQ(get_control(), controlExpected);
}

TEST_F(FixedWingTests, WhenSettingFixedWingControlAboveSaturation_ExpectMaximumValues)
{
    Eigen::Vector4f controlInput{math_tools::degrees_to_radians(90), math_tools::degrees_to_radians(90), math_tools::degrees_to_radians(90), 10.0};
    Eigen::Vector4f controlExpected{math_tools::degrees_to_radians(25), math_tools::degrees_to_radians(25), math_tools::degrees_to_radians(25), 1.0};

    set_control(controlInput);

    EXPECT_VECTOR4_FLOAT_EQ(get_control(), controlExpected);
}

TEST_F(FixedWingTests, WhenCalculatingVelocitiesWithNoWind_ExpectCorrectValues)
{
    Eigen::VectorXf state{get_state()};
    Eigen::Vector3f bodyVelocity{state[3], state[4], state[5]};
    float VaExpected = bodyVelocity.norm();

    calculate_velocities();

    EXPECT_EQ(Va, VaExpected);
    EXPECT_VECTOR3_FLOAT_EQ(relativeBodyAirspeedVelocity, bodyVelocity);
}

TEST_F(FixedWingTests, WhenCalculatingVelocitiesWithWind_ExpectCorrectValues)
{
    Eigen::Vector3f windInput{1.0, 1.0, 1.0};
    set_wind(windInput);
    Eigen::VectorXf state{get_state()};
    Eigen::Vector3f bodyVelocity{state[3], state[4], state[5]};
    Eigen::Vector3f relativeBodyVelocityExpected{bodyVelocity - windInput};
    float VaExpected = relativeBodyVelocityExpected.norm();

    calculate_velocities();

    EXPECT_EQ(Va, VaExpected);
    EXPECT_VECTOR3_FLOAT_EQ(relativeBodyAirspeedVelocity, relativeBodyVelocityExpected);
}

TEST_F(FixedWingTests, WhenCalculatingPropulsionForcesAndMoments_ExpectCorrectValues)
{
    Eigen::Vector4f control{Eigen::Vector4f{0.0, 0.0, 0.0, 1.0}};
    set_control(control);
    calculate_velocities();
    Eigen::Vector3f forcePropExpected{0.5*parameters.propS*parameters.propC*(pow((parameters.kMotor*control[3]), 2) - pow(Va, 2)), 0.0, 0.0};
    Eigen::Vector3f momentPropExpected{-parameters.kTP*pow(parameters.kOmega*control[3], 2), 0.0, 0.0};

    calculate_propulsion_forces_and_moments();

    EXPECT_VECTOR3_FLOAT_EQ(forces, forcePropExpected);
    EXPECT_VECTOR3_FLOAT_EQ(moments, momentPropExpected);
}

TEST_F(FixedWingTests, WhenCalculatingAerodynamicForcesAndMomentsWithNoVelocity_ExpectNoForcesOrMoments)
{
    set_initial_velocity(0.0);
    calculate_velocities();
    Eigen::Vector3f aerodynamicForcesExpected{0.0, 0.0, 0.0};
    Eigen::Vector3f aerodynamicMomentsExpected{0.0, 0.0, 0.0};

    calculate_aerodynamic_forces_and_moments();

    EXPECT_VECTOR3_FLOAT_EQ(forces, aerodynamicForcesExpected);
    EXPECT_VECTOR3_FLOAT_EQ(moments, aerodynamicMomentsExpected);
}

TEST_F(FixedWingTests, WhenCalculatingAerodynamicForcesAndMoments_ExpectCorrectValues)
{
    Eigen::VectorXf state{get_state()};
    Eigen::Vector4f control{Eigen::Vector4f{0.2, 0.2, 0.2, 0.5}};
    set_control(control);

    calculate_velocities();

    float alpha{atan(relativeBodyAirspeedVelocity[2]/relativeBodyAirspeedVelocity[0])};
    float beta{asin(relativeBodyAirspeedVelocity[1]/Va)};
    float aerodynamicCoefficient{0.5*parameters.rho*pow(Va, 2)*parameters.wingS};
    float forceLift{aerodynamicCoefficient*(parameters.cL.O + parameters.cL.alpha*alpha + parameters.cL.q*parameters.wingC/(2.0*Va)*state[10] + parameters.cL.deltaE*control[1])};
    float forceDrag{aerodynamicCoefficient*(parameters.cD.O + parameters.cD.alpha*alpha + parameters.cD.q*parameters.wingC/(2.0*Va)*state[10] + parameters.cD.deltaE*control[1])};

    Eigen::Vector3f aerodynamicForcesExpected;
    aerodynamicForcesExpected[0] = -forceDrag*cos(alpha) + forceLift*sin(alpha);
    aerodynamicForcesExpected[1] = aerodynamicCoefficient*(parameters.cY.O + parameters.cY.beta*beta + parameters.cY.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cY.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cY.deltaA*control[0] + parameters.cY.deltaR*control[2]);
    aerodynamicForcesExpected[2] = -forceDrag*sin(alpha) - forceLift*cos(alpha);

    Eigen::Vector3f aerodynamicMomentsExpected;
    aerodynamicMomentsExpected[0] = aerodynamicCoefficient*parameters.wingB*(parameters.cell.O + parameters.cell.beta*beta + parameters.cell.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cell.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cell.deltaA*control[0] + parameters.cell.deltaR*control[2]);
    aerodynamicMomentsExpected[1] = aerodynamicCoefficient*parameters.wingC*(parameters.cm.O + parameters.cm.alpha*alpha + parameters.cm.q*parameters.wingC/(2.0*Va)*state[10] + parameters.cm.deltaE*control[1]);
    aerodynamicMomentsExpected[2] = aerodynamicCoefficient*parameters.wingB*(parameters.cn.O + parameters.cn.beta*beta + parameters.cn.p*parameters.wingB/(2.0*Va)*state[9] + parameters.cn.r*parameters.wingB/(2.0*Va)*state[11] + parameters.cn.deltaA*control[0] + parameters.cn.deltaR*control[2]);

    calculate_aerodynamic_forces_and_moments();

    EXPECT_VECTOR3_FLOAT_EQ(forces, aerodynamicForcesExpected);
    EXPECT_VECTOR3_FLOAT_EQ(moments, aerodynamicMomentsExpected);
}

TEST_F(FixedWingTests, WhenCalculatingDerivatives_ExpectCorrectValues)
{
    calculate_velocities();
    Eigen::VectorXf state{get_state()};
    Eigen::VectorXf derivativeExpected{Eigen::VectorXf(12)};
    derivativeExpected[0] = state[3];
    derivativeExpected[1] = state[4];
    derivativeExpected[2] = state[5];

    Eigen::Vector3f coriolisForces{(state[11]*state[4] - state[10]*state[5]), (state[9]*state[5] - state[11]*state[3]), (state[10]*state[3] - state[9]*state[4])};
    Eigen::Vector3f bodyVelocityDot{coriolisForces + 1/parameters.mass*forces};
    derivativeExpected[3] = bodyVelocityDot[0];
    derivativeExpected[4] = bodyVelocityDot[1];
    derivativeExpected[5] = bodyVelocityDot[2];

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
    derivativeExpected[6] = orientationDot[0];
    derivativeExpected[7] = orientationDot[1];
    derivativeExpected[8] = orientationDot[2];

    float gamma{parameters.Jx*parameters.Jz - pow(parameters.Jxz, 2)};
    float gamma1{parameters.Jxz*(parameters.Jx - parameters.Jy + parameters.Jz)/gamma};
    float gamma2{(parameters.Jz*(parameters.Jz - parameters.Jy) + pow(parameters.Jxz, 2))/gamma};
    float gamma3{parameters.Jz/gamma};
    float gamma4{parameters.Jxz/gamma};
    float gamma5{(parameters.Jz - parameters.Jx)/parameters.Jy};
    float gamma6{parameters.Jxz/parameters.Jy};
    float gamma7{((parameters.Jx - parameters.Jy)*parameters.Jx + pow(parameters.Jxz, 2))/gamma};
    float gamma8{parameters.Jx/gamma};

    derivativeExpected[9] = gamma1*state[9]*state[10] - gamma2*state[10]*state[11] + gamma3*moments[0] + gamma4*moments[2];
    derivativeExpected[10] = gamma5*state[9]*state[11] - gamma6*(pow(state[9], 2) - pow(state[11], 2)) + 1/parameters.Jy*moments[1];
    derivativeExpected[11] = gamma7*state[9]*state[10] - gamma1*state[10]*state[11] + gamma4*moments[0] + gamma8*moments[2];

    EXPECT_VECTORX_FLOAT_EQ(get_derivatives(get_state(), forces, moments), derivativeExpected, 12);
}

TEST_F(FixedWingTests, WhenPropogatingFixedWingStatesWithDerivativeDynamics_ExpectCorrectStateValues)
{
    float deltaTime(10.0);
    Eigen::VectorXf stateExpected{get_state()};
    calculate_forces_and_moments();
    Eigen::VectorXf k1{get_derivatives(stateExpected, forces, moments)};
    Eigen::VectorXf k2{get_derivatives(stateExpected + deltaTime/2.0*k1, forces, moments)};
    Eigen::VectorXf k3{get_derivatives(stateExpected + deltaTime/2.0*k2, forces, moments)};
    Eigen::VectorXf k4{get_derivatives(stateExpected + deltaTime*k3, forces, moments)};
    stateExpected += deltaTime/6.0*(k1 + 2*k2 + 2*k3 + k4);

    Eigen::VectorXf stateOutput{get_state()};
    propogate_states(stateOutput, forces, moments, deltaTime);

    EXPECT_VECTORX_FLOAT_EQ(stateOutput, stateExpected, 12);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingDefault_ExpectCorrectType)
{
    EXPECT_EQ(fixedWingType, EMB314);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingAsEMB12_ExpectCorrectType)
{
    FixedWing newFixedWing(EMB312);
    EXPECT_EQ(newFixedWing.fixedWingType, EMB312);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingAsEMB14_ExpectCorrectType)
{
    FixedWing newFixedWing(EMB314);
    EXPECT_EQ(newFixedWing.fixedWingType, EMB314);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingAsF16D_ExpectCorrectType)
{
    FixedWing newFixedWing(F16D);
    EXPECT_EQ(newFixedWing.fixedWingType, F16D);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingAsMQ9_ExpectCorrectType)
{
    FixedWing newFixedWing(MQ9);
    EXPECT_EQ(newFixedWing.fixedWingType, MQ9);
}

TEST_F(FixedWingTests, WhenGettingFixedWingParameters_ExpectEMB314ParameterMass)
{
    FixedWingEMBParameters expectedParameters;
    EXPECT_EQ(get_parameters().mass, expectedParameters.mass);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingAsEMB12_ExpectCorrectMassParameter)
{
    FixedWing newFixedWing(EMB312);
    FixedWingEMBParameters expectedParameters;
    EXPECT_EQ(newFixedWing.get_parameters().mass, expectedParameters.mass);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingAsEMB14_ExpectCorrectMassParameter)
{
    FixedWing newFixedWing(EMB314);
    FixedWingEMBParameters expectedParameters;
    EXPECT_EQ(newFixedWing.get_parameters().mass, expectedParameters.mass);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingAsF16_ExpectCorrectMassParameter)
{
    FixedWing newFixedWing(F16D);
    FixedWingF16Parameters expectedParameters;
    EXPECT_EQ(newFixedWing.get_parameters().mass, expectedParameters.mass);
}

TEST_F(FixedWingTests, WhenInitializingFixedWingAsMQ9_ExpectCorrectMassParameter)
{
    FixedWing newFixedWing(MQ9);
    FixedWingMQ9Parameters expectedParameters;
    EXPECT_EQ(newFixedWing.get_parameters().mass, expectedParameters.mass);
}
