#include "MathTools.hpp"
#include <iostream>

namespace math_tools
{

float radians2Degrees(float radianInput)
{
    return radianInput*180.0/M_PI;
}

float degrees2Radians(float degreeInput)
{
    return degreeInput*M_PI/180.0;
}

float saturate(float input, float minimum, float maximum)
{
    float output{input};
    if(input < minimum)
    {
        output = minimum;
    }
    else if(input > maximum)
    {
        output = maximum;
    }
    return output;
}

}
