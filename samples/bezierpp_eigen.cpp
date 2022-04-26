// Copyright 2021 Olivier Le Doeuff
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
// (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <bezierpp/bezierpp.hpp>
#include <Eigen/Core>
#include <iostream>

const Eigen::IOFormat CleanFmt(Eigen::StreamPrecision, 0, ", ", ", ", "", "");

int main(int argc, char* argv[])
{
    constexpr int segmentCount = 10;

    // Linear Curve
    {
        std::cout << "Linear Curve :" << std::endl;

        const Eigen::Vector2d p1(1, 0);
        const Eigen::Vector2d p2(0, 1);

        for(int i = 0; i < segmentCount; ++i)
        {
            const auto t = bezierpp::invLerp<float>(0.f, float(segmentCount - 1), float(i));
            const auto p = bezierpp::linearBezierCurve(p1, p2, t);

            std::cout << i << " : " << p.format(CleanFmt) << std::endl;
        }
    }

    std::cout << std::endl;

    // Quadratic Curve
    {
        std::cout << "Quadratic Curve :" << std::endl;

        const Eigen::Vector2d p1(0, 0);
        const Eigen::Vector2d p2(0.4, 1);
        const Eigen::Vector2d p3(1, 0);

        for(int i = 0; i < segmentCount; ++i)
        {
            const auto t = bezierpp::invLerp<float>(0.f, float(segmentCount - 1), float(i));
            const auto p = bezierpp::quadraticBezierCurve(p1, p2, p3, t);

            std::cout << i << " : " << p.format(CleanFmt) << std::endl;
        }
    }

    std::cout << std::endl;

    // Cubic Curve
    {
        std::cout << "Cubic Curve :" << std::endl;

        const Eigen::Vector2d p1(0, 0);
        const Eigen::Vector2d p2(-0.1, 1);
        const Eigen::Vector2d p3(0.8, 1);
        const Eigen::Vector2d p4(1, 0);

        for(int i = 0; i < segmentCount; ++i)
        {
            const auto t = bezierpp::invLerp<float>(0.f, float(segmentCount - 1), float(i));
            const auto p = bezierpp::cubicBezierCurve(p1, p2, p3, p4, t);

            std::cout << i << " : " << p.format(CleanFmt) << std::endl;
        }
    }
}