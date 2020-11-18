#include "FixedWingMyTwinDreamsParameters.hpp"


FixedWingMyTwinDreamsParameters::FixedWingMyTwinDreamsParameters()
{
    mass = 3.92;
    Jx = 0.213;
    Jy = 0.171;
    Jz = 0.350;
    Jxz = 0.04;
    rho = 1.2682;
    wingS = 0.468;
    wingB = 1.8;
    wingC = 0.26;
    wingM = 50;
    wingEpsilon = 0.1592;
    wingAlpha0 = 0.3040363557;

    kMotor = 50.0;
    kTP = 0.0;
    kOmega = 0.0;

    propE = 0.8;
    propS = 0.0314;
    propC = 1.0;

    cL.O = 0.2869;
    cL.alpha = 5.1378;
    cL.beta = 0.0;
    cL.p = 0.0;
    cL.q = 1.7102;
    cL.r = 0.0;
    cL.deltaA = 0.0;
    cL.deltaE = 0.5202;
    cL.deltaR = 0.0;

    cD.O = 0.03087;
    cD.alpha = 0.0043021;
    cD.beta = 0.0;
    cD.p = 0.02815;
    cD.q = 0.2514;
    cD.r = 0.0;
    cD.deltaA = 0.0;
    cD.deltaE = 0.01879;
    cD.deltaR = 0.0;

    cY.O = 0.0;
    cY.alpha = 0.0;
    cY.beta = -0.2471;
    cY.p = -0.07278;
    cY.q = 0.0;
    cY.r = 0.1849;
    cY.deltaA = -0.02344;
    cY.deltaE = 0.0;
    cY.deltaR = 0.1591;

    cell.O = 0.0;
    cell.alpha = 0.0;
    cell.beta = 0.0193;
    cell.p = -0.5406;
    cell.q = 0.0;
    cell.r = 0.1929;
    cell.deltaA = 0.2818;
    cell.deltaE = 0.0;
    cell.deltaR = 0.00096;

    cm.O = 0.0362;
    cm.alpha = -0.2627;
    cm.beta = 0.0;
    cm.p = 0.0;
    cm.q = -9.7213;
    cm.r = 0.0;
    cm.deltaA = 0.0;
    cm.deltaE = -1.2392;
    cm.deltaR = 0.0;

    cn.O = 0.0;
    cn.alpha = 0.0;
    cn.beta = 0.08557;
    cn.p = -0.0498;
    cn.q = 0.0;
    cn.r = -0.0572;
    cn.deltaA = 0.0095;
    cn.deltaE = 0.0;
    cn.deltaR = -0.06;

    phi0 = 0.0;
    theta0 = 0.0349;
    psi0 = 0;
    Va0 = 17;
    deltaA0 = 0.0;
    deltaE0 = 0.05967;
    deltaR0 = 0.0;
    deltaT0 = 0.4;
}
