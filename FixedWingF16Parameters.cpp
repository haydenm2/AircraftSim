#include "FixedWingF16Parameters.hpp"


FixedWingF16Parameters::FixedWingF16Parameters()
{
    mass = 9298;
    Jx = 12875;
    Jy = 75673.62;
    Jz = 85552.11;
    Jxz = 1331.41;
    rho = 1.2682;
    wingS = 4.68;
    wingB = 18.0;
    wingC = 2.6;
    wingM = 100;
    wingEpsilon = 0.1592;
    wingAlpha0 = 0.3040363557;

    kMotor = 200.0;
    kTP = 0.0;
    kOmega = 0.0;

    propE = 0.8;
    propS = 0.0314;
    propC = 1.0;

    cL.O = 1.9;
    cL.alpha = 0.0489;
    cL.beta = 0.0;
    cL.p = 0.0;
    cL.q = 1.7102;
    cL.r = 0.0;
    cL.deltaA = 0.0;
    cL.deltaE = 0.5202;
    cL.deltaR = 0.0;

    cD.O = 0.0175;
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
    cm.alpha = -0.284;
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
    theta0 = 0.087;
    psi0 = 0;
    Va0 = 250;
    deltaA0 = 0.0;
    deltaE0 = 0.02967;
    deltaR0 = 0.0;
    deltaT0 = 0.4;
}
