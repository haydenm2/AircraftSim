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
    Eigen::Vector4f controlInput{math_tools::degrees2Radians(-90), math_tools::degrees2Radians(-90), math_tools::degrees2Radians(-90), -10.0};
    Eigen::Vector4f controlExpected{math_tools::degrees2Radians(-25), math_tools::degrees2Radians(-25), math_tools::degrees2Radians(-25), 0.0};

    set_control(controlInput);

    EXPECT_VECTOR4_FLOAT_EQ(get_control(), controlExpected);
}

TEST_F(FixedWingTests, WhenSettingFixedWingControlAboveSaturation_ExpectMaximumValues)
{
    Eigen::Vector4f controlInput{math_tools::degrees2Radians(90), math_tools::degrees2Radians(90), math_tools::degrees2Radians(90), 10.0};
    Eigen::Vector4f controlExpected{math_tools::degrees2Radians(25), math_tools::degrees2Radians(25), math_tools::degrees2Radians(25), 1.0};

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
