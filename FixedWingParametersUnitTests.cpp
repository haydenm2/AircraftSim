#include "gtest/gtest.h"
#include "UnitTestUtils.hpp"
#include "FixedWingEMBParameters.hpp"
#include "FixedWingF16Parameters.hpp"
#include "FixedWingMQ9Parameters.hpp"


TEST(FixedWingParameterTests, WhenInitializingEMBParameterSet_ExpectCorrectValues)
{
    FixedWingEMBParameters parameters;

    EXPECT_EQ(parameters.mass, 13.5f);
    EXPECT_EQ(parameters.Jx, 0.8244f);
    EXPECT_EQ(parameters.Jy, 1.135f);
    EXPECT_EQ(parameters.Jz, 1.759f);
    EXPECT_EQ(parameters.Jxz, 0.1204f);
    EXPECT_EQ(parameters.rho, 1.2682f);
    EXPECT_EQ(parameters.wingS, 0.55f);
    EXPECT_EQ(parameters.wingB, 2.8956f);
    EXPECT_EQ(parameters.wingC, 0.18994f);
    EXPECT_EQ(parameters.wingM, 50.0f);
    EXPECT_EQ(parameters.wingEpsilon, 0.1592f);
    EXPECT_EQ(parameters.wingAlpha0, 0.4712f);

    EXPECT_EQ(parameters.kMotor, 80.0f);
    EXPECT_EQ(parameters.kTP, 0.0f);
    EXPECT_EQ(parameters.kOmega, 0.0f);

    EXPECT_EQ(parameters.propE, 0.9f);
    EXPECT_EQ(parameters.propS, 0.2027f);
    EXPECT_EQ(parameters.propC, 1.0f);

    EXPECT_EQ(parameters.cL.O, 0.28f);
    EXPECT_EQ(parameters.cL.alpha, 3.45f);
    EXPECT_EQ(parameters.cL.beta, 0.0f);
    EXPECT_EQ(parameters.cL.p, 0.0f);
    EXPECT_EQ(parameters.cL.q, 0.0f);
    EXPECT_EQ(parameters.cL.r, 0.0f);
    EXPECT_EQ(parameters.cL.deltaA, 0.0f);
    EXPECT_EQ(parameters.cL.deltaE, -0.36f);
    EXPECT_EQ(parameters.cL.deltaR, 0.0f);

    EXPECT_EQ(parameters.cD.O, 0.03f);
    EXPECT_EQ(parameters.cD.alpha, 0.3f);
    EXPECT_EQ(parameters.cD.beta, 0.0f);
    EXPECT_EQ(parameters.cD.p, 0.0437f);
    EXPECT_EQ(parameters.cD.q, 0.0f);
    EXPECT_EQ(parameters.cD.r, 0.0f);
    EXPECT_EQ(parameters.cD.deltaA, 0.0f);
    EXPECT_EQ(parameters.cD.deltaE, 0.0f);
    EXPECT_EQ(parameters.cD.deltaR, 0.0f);

    EXPECT_EQ(parameters.cell.O, 0.0f);
    EXPECT_EQ(parameters.cell.alpha, 0.0f);
    EXPECT_EQ(parameters.cell.beta, -0.12f);
    EXPECT_EQ(parameters.cell.p, -0.26f);
    EXPECT_EQ(parameters.cell.q, 0.0f);
    EXPECT_EQ(parameters.cell.r, 0.14f);
    EXPECT_EQ(parameters.cell.deltaA, 0.08f);
    EXPECT_EQ(parameters.cell.deltaE, 0.0f);
    EXPECT_EQ(parameters.cell.deltaR, 0.105f);

    EXPECT_EQ(parameters.cm.O, -0.02338f);
    EXPECT_EQ(parameters.cm.alpha, -0.38f);
    EXPECT_EQ(parameters.cm.beta, 0.0f);
    EXPECT_EQ(parameters.cm.p, 0.0f);
    EXPECT_EQ(parameters.cm.q, -3.6f);
    EXPECT_EQ(parameters.cm.r, 0.0f);
    EXPECT_EQ(parameters.cm.deltaA, 0.0f);
    EXPECT_EQ(parameters.cm.deltaE, -0.5f);
    EXPECT_EQ(parameters.cm.deltaR, 0.0f);

    EXPECT_EQ(parameters.cn.O, 0.0f);
    EXPECT_EQ(parameters.cn.alpha, 0.0f);
    EXPECT_EQ(parameters.cn.beta, 0.25f);
    EXPECT_EQ(parameters.cn.p, 0.022f);
    EXPECT_EQ(parameters.cn.q, 0.0f);
    EXPECT_EQ(parameters.cn.r, -0.35f);
    EXPECT_EQ(parameters.cn.deltaA, 0.06f);
    EXPECT_EQ(parameters.cn.deltaE, 0.0f);
    EXPECT_EQ(parameters.cn.deltaR, -0.032f);

    EXPECT_EQ(parameters.cY.O, 0.0f);
    EXPECT_EQ(parameters.cY.alpha, 0.0f);
    EXPECT_EQ(parameters.cY.beta, -0.98f);
    EXPECT_EQ(parameters.cY.p, 0.0f);
    EXPECT_EQ(parameters.cY.q, 0.0f);
    EXPECT_EQ(parameters.cY.r, 0.0f);
    EXPECT_EQ(parameters.cY.deltaA, 0.0f);
    EXPECT_EQ(parameters.cY.deltaE, 0.0f);
    EXPECT_EQ(parameters.cY.deltaR, -0.17f);

    EXPECT_EQ(parameters.phi0, 0.0f);
    EXPECT_EQ(parameters.theta0, 0.0349f);
    EXPECT_EQ(parameters.psi0, 0.0f);
    EXPECT_EQ(parameters.Va0, 35.0f);
    EXPECT_EQ(parameters.deltaA0, 0.0f);
    EXPECT_EQ(parameters.deltaE0, 0.052f);
    EXPECT_EQ(parameters.deltaR0, 0.0f);
    EXPECT_EQ(parameters.deltaT0, 0.78144714f);
}

TEST(FixedWingParameterTests, WhenInitializingF16ParameterSet_ExpectCorrectValues)
{
    FixedWingF16Parameters parameters;

    EXPECT_EQ(parameters.mass, 190.5f);
    EXPECT_EQ(parameters.Jx, 980.0f);
    EXPECT_EQ(parameters.Jy, 910.0f);
    EXPECT_EQ(parameters.Jz, 1115.0f);
    EXPECT_EQ(parameters.Jxz, -66.0f);
    EXPECT_EQ(parameters.rho, 1.2682f);
    EXPECT_EQ(parameters.wingS, 2.8261105f);
    EXPECT_EQ(parameters.wingB, 5.15112f);
    EXPECT_EQ(parameters.wingC, 0.54864f);
    EXPECT_EQ(parameters.wingM, 50);
    EXPECT_EQ(parameters.wingEpsilon, 0.0f);
    EXPECT_EQ(parameters.wingAlpha0, 0.3040363557f);

    EXPECT_EQ(parameters.kMotor, 1025.0f);
    EXPECT_EQ(parameters.kTP, 0.0f);
    EXPECT_EQ(parameters.kOmega, 0.0f);

    EXPECT_EQ(parameters.propE, 0.8f);
    EXPECT_EQ(parameters.propS, 0.314f);
    EXPECT_EQ(parameters.propC, 1.0f);

    EXPECT_EQ(parameters.cL.O, 0.385f);
    EXPECT_EQ(parameters.cL.alpha, 4.78f);
    EXPECT_EQ(parameters.cL.beta, 0.0f);
    EXPECT_EQ(parameters.cL.p, 0.0f);
    EXPECT_EQ(parameters.cL.q, 8.05f);
    EXPECT_EQ(parameters.cL.r, 0.0f);
    EXPECT_EQ(parameters.cL.deltaA, 0.0f);
    EXPECT_EQ(parameters.cL.deltaE, 0.401f);
    EXPECT_EQ(parameters.cL.deltaR, 0.0f);

    EXPECT_EQ(parameters.cD.O, 0.060f);
    EXPECT_EQ(parameters.cD.alpha, 0.430f);
    EXPECT_EQ(parameters.cD.beta, 0.0f);
    EXPECT_EQ(parameters.cD.p, 0.0f);
    EXPECT_EQ(parameters.cD.q, 0.0f);
    EXPECT_EQ(parameters.cD.r, 0.0f);
    EXPECT_EQ(parameters.cD.deltaA, 0.0f);
    EXPECT_EQ(parameters.cD.deltaE, 0.0180f);
    EXPECT_EQ(parameters.cD.deltaR, 0.0f);

    EXPECT_EQ(parameters.cell.O, 0.0f);
    EXPECT_EQ(parameters.cell.alpha, 0.0f);
    EXPECT_EQ(parameters.cell.beta, -0.023f);
    EXPECT_EQ(parameters.cell.p, -0.450f);
    EXPECT_EQ(parameters.cell.q, 0.0f);
    EXPECT_EQ(parameters.cell.r, 0.265f);
    EXPECT_EQ(parameters.cell.deltaA, 0.161f);
    EXPECT_EQ(parameters.cell.deltaE, 0.0f);
    EXPECT_EQ(parameters.cell.deltaR, -0.00229f);

    EXPECT_EQ(parameters.cm.O, 0.194f);
    EXPECT_EQ(parameters.cm.alpha, -2.12f);
    EXPECT_EQ(parameters.cm.beta, 0.0f);
    EXPECT_EQ(parameters.cm.p, 0.0f);
    EXPECT_EQ(parameters.cm.q, -36.6f);
    EXPECT_EQ(parameters.cm.r, 0.0f);
    EXPECT_EQ(parameters.cm.deltaA, 0.0f);
    EXPECT_EQ(parameters.cm.deltaE, -1.76f);
    EXPECT_EQ(parameters.cm.deltaR, 0.0f);

    EXPECT_EQ(parameters.cn.O, 0.0f);
    EXPECT_EQ(parameters.cn.alpha, 0.0f);
    EXPECT_EQ(parameters.cn.beta, 0.109f);
    EXPECT_EQ(parameters.cn.p, -0.110f);
    EXPECT_EQ(parameters.cn.q, 0.0f);
    EXPECT_EQ(parameters.cn.r, -0.200f);
    EXPECT_EQ(parameters.cn.deltaA, -0.0200f);
    EXPECT_EQ(parameters.cn.deltaE, 0.0f);
    EXPECT_EQ(parameters.cn.deltaR, -0.0917f);

    EXPECT_EQ(parameters.cY.O, 0.0f);
    EXPECT_EQ(parameters.cY.alpha, 0.0f);
    EXPECT_EQ(parameters.cY.beta, -0.819f);
    EXPECT_EQ(parameters.cY.p, 0.0f);
    EXPECT_EQ(parameters.cY.q, 0.0f);
    EXPECT_EQ(parameters.cY.r, 0.0f);
    EXPECT_EQ(parameters.cY.deltaA, 0.0f);
    EXPECT_EQ(parameters.cY.deltaE, 0.0f);
    EXPECT_EQ(parameters.cY.deltaR, 0.191f);

    EXPECT_EQ(parameters.phi0, 0.0f);
    EXPECT_EQ(parameters.theta0, 0.0f);
    EXPECT_EQ(parameters.psi0, 0.0f);
    EXPECT_EQ(parameters.Va0, 252.0f);
    EXPECT_EQ(parameters.deltaA0, 0.0f);
    EXPECT_EQ(parameters.deltaE0, 0.26f);
    EXPECT_EQ(parameters.deltaR0, 0.0f);
    EXPECT_EQ(parameters.deltaT0, 0.4f);
}

TEST(FixedWingParameterTests, WhenInitializingMQ9ParameterSet_ExpectCorrectValues)
{
    FixedWingMQ9Parameters parameters;

    EXPECT_EQ(parameters.mass, 190.509f);
    EXPECT_EQ(parameters.Jx, 47.2258508334f);
    EXPECT_EQ(parameters.Jy, 90.948268086f);
    EXPECT_EQ(parameters.Jz, 111.475351849f);
    EXPECT_EQ(parameters.Jxz, -6.6462195909f);
    EXPECT_EQ(parameters.rho, 1.2682f);
    EXPECT_EQ(parameters.wingS, 2.8261105f);
    EXPECT_EQ(parameters.wingB, 5.15112f);
    EXPECT_EQ(parameters.wingC, 0.54864f);
    EXPECT_EQ(parameters.wingM, 50);
    EXPECT_EQ(parameters.wingEpsilon, 0.0f);
    EXPECT_EQ(parameters.wingAlpha0, 0.3040363557f);

    EXPECT_EQ(parameters.kMotor, 225.0f);
    EXPECT_EQ(parameters.kTP, 0.0f);
    EXPECT_EQ(parameters.kOmega, 0.0f);

    EXPECT_EQ(parameters.propE, 0.8f);
    EXPECT_EQ(parameters.propS, 0.314f);
    EXPECT_EQ(parameters.propC, 1.0f);

    EXPECT_EQ(parameters.cL.O, 0.385f);
    EXPECT_EQ(parameters.cL.alpha, 4.78f);
    EXPECT_EQ(parameters.cL.beta, 0.0f);
    EXPECT_EQ(parameters.cL.p, 0.0f);
    EXPECT_EQ(parameters.cL.q, 8.05f);
    EXPECT_EQ(parameters.cL.r, 0.0f);
    EXPECT_EQ(parameters.cL.deltaA, 0.0f);
    EXPECT_EQ(parameters.cL.deltaE, 0.401f);
    EXPECT_EQ(parameters.cL.deltaR, 0.0f);

    EXPECT_EQ(parameters.cD.O, 0.060f);
    EXPECT_EQ(parameters.cD.alpha, 0.430f);
    EXPECT_EQ(parameters.cD.beta, 0.0f);
    EXPECT_EQ(parameters.cD.p, 0.0f);
    EXPECT_EQ(parameters.cD.q, 0.0f);
    EXPECT_EQ(parameters.cD.r, 0.0f);
    EXPECT_EQ(parameters.cD.deltaA, 0.0f);
    EXPECT_EQ(parameters.cD.deltaE, 0.0180f);
    EXPECT_EQ(parameters.cD.deltaR, 0.0f);

    EXPECT_EQ(parameters.cell.O, 0.0f);
    EXPECT_EQ(parameters.cell.alpha, 0.0f);
    EXPECT_EQ(parameters.cell.beta, -0.023f);
    EXPECT_EQ(parameters.cell.p, -0.450f);
    EXPECT_EQ(parameters.cell.q, 0.0f);
    EXPECT_EQ(parameters.cell.r, 0.265f);
    EXPECT_EQ(parameters.cell.deltaA, 0.161f);
    EXPECT_EQ(parameters.cell.deltaE, 0.0f);
    EXPECT_EQ(parameters.cell.deltaR, -0.00229f);

    EXPECT_EQ(parameters.cm.O, 0.194f);
    EXPECT_EQ(parameters.cm.alpha, -2.12f);
    EXPECT_EQ(parameters.cm.beta, 0.0f);
    EXPECT_EQ(parameters.cm.p, 0.0f);
    EXPECT_EQ(parameters.cm.q, -36.6f);
    EXPECT_EQ(parameters.cm.r, 0.0f);
    EXPECT_EQ(parameters.cm.deltaA, 0.0f);
    EXPECT_EQ(parameters.cm.deltaE, -1.76f);
    EXPECT_EQ(parameters.cm.deltaR, 0.0f);

    EXPECT_EQ(parameters.cn.O, 0.0f);
    EXPECT_EQ(parameters.cn.alpha, 0.0f);
    EXPECT_EQ(parameters.cn.beta, 0.109f);
    EXPECT_EQ(parameters.cn.p, -0.110f);
    EXPECT_EQ(parameters.cn.q, 0.0f);
    EXPECT_EQ(parameters.cn.r, -0.200f);
    EXPECT_EQ(parameters.cn.deltaA, -0.0200f);
    EXPECT_EQ(parameters.cn.deltaE, 0.0f);
    EXPECT_EQ(parameters.cn.deltaR, -0.0917f);

    EXPECT_EQ(parameters.cY.O, 0.0f);
    EXPECT_EQ(parameters.cY.alpha, 0.0f);
    EXPECT_EQ(parameters.cY.beta, -0.819f);
    EXPECT_EQ(parameters.cY.p, 0.0f);
    EXPECT_EQ(parameters.cY.q, 0.0f);
    EXPECT_EQ(parameters.cY.r, 0.0f);
    EXPECT_EQ(parameters.cY.deltaA, 0.0f);
    EXPECT_EQ(parameters.cY.deltaE, 0.0f);
    EXPECT_EQ(parameters.cY.deltaR, 0.191f);

    EXPECT_EQ(parameters.phi0, 0.0f);
    EXPECT_EQ(parameters.theta0, 0.0f);
    EXPECT_EQ(parameters.psi0, 0.0f);
    EXPECT_EQ(parameters.Va0, 152.0f);
    EXPECT_EQ(parameters.deltaA0, 0.0f);
    EXPECT_EQ(parameters.deltaE0, 0.26f);
    EXPECT_EQ(parameters.deltaR0, 0.0f);
    EXPECT_EQ(parameters.deltaT0, 0.4f);
}
