#include "FixedWingAerosondeParameters.hpp"


FixedWingAerosondeParameters::FixedWingAerosondeParameters()
{
    mass = 13.5;
    Jx = 0.8244;
    Jy = 1.135;
    Jz = 1.759;
    Jxz = 0.1204;
    rho = 1.2682;
    wingS = 0.55;
    wingB = 2.8956;
    wingC = 0.18994;
    wingM = 50;
    wingEpsilon = 0.1592;
    wingAlpha0 = 0.4712;
    kMotor = 80.0;
    kTP = 0.0;
    kOmega = 0.0;
    propE = 0.9;
    propS = 0.55;
    propC = 1.0;

    cL.O = 0.28;
    cL.alpha = 3.45;
    cL.beta = 0.0;
    cL.p = 0.0;
    cL.q = 0.0;
    cL.r = 0.0;
    cL.deltaA = 0.0;
    cL.deltaE = -0.36;
    cL.deltaR = 0.0;

    cD.O = 0.28;
    cD.alpha = 0.3;
    cD.beta = 0.0;
    cD.p = 0.0437;
    cD.q = 0.0;
    cD.r = 0.0;
    cD.deltaA = 0.0;
    cD.deltaE = 0.0;
    cD.deltaR = 0.0;

    cY.O = 0.0;
    cY.alpha = 0.0;
    cY.beta = -0.98;
    cY.p = 0.0;
    cY.q = 0.0;
    cY.r = 0.0;
    cY.deltaA = 0.0;
    cY.deltaE = 0.0;
    cY.deltaR = -0.17;

    cell.O = 0.0;
    cell.alpha = 0.0;
    cell.beta = -0.12;
    cell.p = -0.26;
    cell.q = 0.0;
    cell.r = 0.14;
    cell.deltaA = 0.08;
    cell.deltaE = 0.0;
    cell.deltaR = 0.105;

    cm.O = -0.02338;
    cm.alpha = -0.38;
    cm.beta = 0.0;
    cm.p = 0.0;
    cm.q = -3.6;
    cm.r = 0.0;
    cm.deltaA = 0.0;
    cm.deltaE = -0.5;
    cm.deltaR = 0.0;

    cn.O = 0.0;
    cn.alpha = 0.0;
    cn.beta = 0.25;
    cn.p = 0.022;
    cn.q = 0.0;
    cn.r = -0.35;
    cn.deltaA = 0.06;
    cn.deltaE = 0.0;
    cn.deltaR = -0.032;

    phi0 = 0.0;
    theta0 = 0.0349;
    psi0 = 0;
    Va0 = 250;
    deltaE0 = 0.02967;
    deltaT0 = 0.4;
}
