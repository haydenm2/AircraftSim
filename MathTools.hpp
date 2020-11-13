#ifndef MATH_TOOLS_HPP
#define MATH_TOOLS_HPP

#include <math.h>

namespace math_tools
{

float radians2Degrees(float radianInput);
float degrees2Radians(float degreeInput);
float saturate(float input, float minimum, float maximum);

}

#endif
