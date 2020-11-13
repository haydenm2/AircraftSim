#include "gtest/gtest.h"
#include "MathTools.hpp"


TEST(MathToolsTests, WhenConvertingToDegrees_ExpectCorrectValue)
{
    float inputRadians{1.0};
    float expectedDegrees{inputRadians*180.0f/M_PI};

    EXPECT_EQ(math_tools::radians2Degrees(inputRadians), expectedDegrees);
}

TEST(MathToolsTests, WhenConvertingToRadians_ExpectCorrectValue)
{
    float inputDegrees{10.0};
    float expectedRadians{inputDegrees*M_PI/180.0f};

    EXPECT_EQ(math_tools::degrees2Radians(inputDegrees), expectedRadians);
}

TEST(MathToolsTests, WhenSaturatingValueInRange_ExpectSameValue)
{
    float input{5.0};
    float minimum{-10.0};
    float maximum{10.0};

    float output{math_tools::saturate(input, minimum, maximum)};

    EXPECT_EQ(output, input);
}

TEST(MathToolsTests, WhenSaturatingValueAboveRange_ExpectMaximum)
{
    float input{15.0};
    float minimum{-10.0};
    float maximum{10.0};

    float output{math_tools::saturate(input, minimum, maximum)};

    EXPECT_EQ(output, maximum);
}

TEST(MathToolsTests, WhenSaturatingValueBelowRange_ExpectMinimum)
{
    float input{-15.0};
    float minimum{-10.0};
    float maximum{10.0};

    float output{math_tools::saturate(input, minimum, maximum)};

    EXPECT_EQ(output, minimum);
}
