#include "FixedWingPioneerParameters.hpp"


FixedWingPioneerParameters::FixedWingPioneerParameters()
{
    mass = 190.509;
    Jx = 47.2258508334;
    Jy = 90.948268086;
    Jz = 111.475351849;
    Jxz = -6.6462195909;
    rho = 1.2682;
    wingS = 2.8261105;
    wingB = 5.15112;
    wingC = 0.54864;
    wingM = 50;
    wingEpsilon = 0.0;
    wingAlpha0 = 0.3040363557;

    kMotor = 125.0;
    kTP = 0.0;
    kOmega = 0.0;

    propE = 0.8;
    propS = 0.314;
    propC = 1.0;

    cL.O = 0.385;
    cL.alpha = 4.78;
    cL.beta = 0.0;
    cL.p = 0.0;
    cL.q = 8.05;
    cL.r = 0.0;
    cL.deltaA = 0.0;
    cL.deltaE = 0.401;
    cL.deltaR = 0.0;

    cD.O = 0.060;
    cD.alpha = 0.430;
    cD.beta = 0.0;
    cD.p = 0.0;
    cD.q = 0.0;
    cD.r = 0.0;
    cD.deltaA = 0.0;
    cD.deltaE = 0.0180;
    cD.deltaR = 0.0;

    cY.O = 0.0;
    cY.alpha = 0.0;
    cY.beta = -0.819;
    cY.p = 0.0;
    cY.q = 0.0;
    cY.r = 0.0;
    cY.deltaA = 0.0;
    cY.deltaE = 0.0;
    cY.deltaR = 0.191;

    cell.O = 0.0;
    cell.alpha = 0.0;
    cell.beta = -0.023;
    cell.p = -0.450;
    cell.q = 0.0;
    cell.r = 0.265;
    cell.deltaA = 0.161;
    cell.deltaE = 0.0;
    cell.deltaR = -0.00229;

    cm.O = 0.194;
    cm.alpha = -2.12;
    cm.beta = 0.0;
    cm.p = 0.0;
    cm.q = -36.6;
    cm.r = 0.0;
    cm.deltaA = 0.0;
    cm.deltaE = -1.76;
    cm.deltaR = 0.0;

    cn.O = 0.0;
    cn.alpha = 0.0;
    cn.beta = 0.109;
    cn.p = -0.110;
    cn.q = 0.0;
    cn.r = -0.200;
    cn.deltaA = -0.0200;
    cn.deltaE = 0.0;
    cn.deltaR = -0.0917;

    phi0 = 0.0;
    theta0 = 0.0;
    psi0 = 0.0;
    Va0 = 52.0;
    deltaA0 = 0.0;
    deltaE0 = 0.32;
    deltaR0 = 0.0;
    deltaT0 = 0.7;
}
