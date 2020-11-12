#ifndef FIXED_WING_PARAMETERS_HPP
#define FIXED_WING_PARAMETERS_HPP


struct FixedWingCoefficient
{
    float O;
    float alpha;
    float beta;
    float p;
    float q;
    float r;
    float deltaA;
    float deltaE;
    float deltaR;
};

struct FixedWingParameters
{
    float mass;
    float Jx;
    float Jy;
    float Jz;
    float Jxz;
    float rho;

    float wingS;
    float wingB;
    float wingC;
    float wingM;
    float wingEpsilon;
    float wingAlpha0;

    float kMotor;
    float kTP;
    float kOmega;

    float propE;
    float propS;
    float propC;

    FixedWingCoefficient cL;
    FixedWingCoefficient cD;
    FixedWingCoefficient cY;
    FixedWingCoefficient cell;
    FixedWingCoefficient cm;
    FixedWingCoefficient cn;

    float phi0;
    float theta0;
    float psi0;
    float Va0;
    float deltaE0;
    float deltaT0;

};

#endif
