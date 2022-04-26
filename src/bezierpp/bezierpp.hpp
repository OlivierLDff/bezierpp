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

#ifndef __BEZIERPP_HPP__
#define __BEZIERPP_HPP__

#include <utility>
#include <limits>

namespace bezierpp {

template<typename Scalar>
Scalar invLerp(Scalar a, Scalar b, Scalar v)
{
    if(b == a)
        return {};

    return (v - a) / (b - a);
}

template<typename Scalar, typename ScalarT>
Scalar lerp(const Scalar& a, const Scalar& b, ScalarT t)
{
    return a + t * (b - a);
}

template<typename T, typename Scalar>
Scalar getNorm(const T& value)
{
    return value.norm();
}

// \brief Get optimal bezier control points, for smooth bezier curve around p2, with a curve starting at p1 and ending at p3
// More info http://scaledinnovation.com/analytics/splines/aboutSplines.html
// \tparam T Vector data holder that must support  + - * operator
// \tparam Scalar scalar type (float or double)
// \param p1 first point where spline starts
// \param p2 middle point where spline should go
// \param p1 last point where spline ends
// \param tension Control how smooth spline is.
// 0 is linear interpolation between points
// 0.5 is the smoothest as possible
// 1 act like a "radius"
// \return Bezier control points that should be used around p2
template<typename T, typename Scalar>
std::pair<T, T> getBezierControlPoints(const T& p1, const T& p2, const T& p3, float tension = 0.5)
{
    const auto d12 = getNorm<T, Scalar>(p1 - p2);
    const auto d23 = getNorm<T, Scalar>(p2 - p3);
    const auto d13 = d12 + d23;

    if(d13 >= -std::numeric_limits<Scalar>::epsilon() && d13 <= std::numeric_limits<Scalar>::epsilon())
        return {p2, p2};

    const auto fa = tension * d12 / d13;
    const auto fb = tension * d23 / d13;

    const auto p31 = p3 - p1;
    const auto pc1 = p2 - fa * p31;
    const auto pc2 = p2 + fb * p31;

    return {pc1, pc2};
}

// \brief Give position on 3D linear bezier curve following equation:
// P = P1+t(P2-P1)
// See more about bezier curve on wikipedia : https://en.wikipedia.org/wiki/Bézier_curve#Constructing_Bézier_curves
// \tparam T Vector data holder that must support  + - * operator
// \tparam Scalar scalar type (float or double)
// \param p1 is origin point
// \param p2 is destination point
// \param t is expected to be between 0 and 1
// \return Position on point at t
template<typename T, typename Scalar>
T linearBezierCurve(const T& p1, const T& p2, Scalar t)
{
    return lerp<T, Scalar>(p1, p2, t);
}

// \brief Give position on 3D quadratic bezier curve following equation:
// P = (1−t)²P1 + 2(1−t)tP2 + t²P3
// See more about bezier curve on wikipedia : https://en.wikipedia.org/wiki/Bézier_curve#Constructing_Bézier_curves
// \tparam T Vector data holder that must support  + - * operator
// \tparam Scalar scalar type (float or double)
// \param p1 is origin point
// \param p2 is control point
// \param p3 is destination point
// \param t is expected to be between 0 and 1
// \return Position on point at t
template<typename T, typename Scalar>
T quadraticBezierCurve(const T& p1, const T& p2, const T& p3, Scalar t)
{
    // P = (1−t)²P1 + 2(1−t)tP2 + t²P3
    // p =    a     +     b     +  c

    const auto reverseT = (1 - t);

    const auto a = p1 * reverseT * reverseT;
    const auto b = 2 * reverseT * t * p2;
    const auto c = t * t * p3;

    return a + b + c;
}

// \brief Give position on 3D cubic bezier curve following equation:
// P = (1−t)³P1 + 3(1−t)²tP2 + 3(1−t)t²P3 + t³P4
// See more about bezier curve on wikipedia : https://en.wikipedia.org/wiki/Bézier_curve#Constructing_Bézier_curves
// \tparam T Vector data holder that must support  + - * operator
// \tparam Scalar scalar type (float or double)
// \param p1 is origin point
// \param p2 is first control point
// \param p3 is second control point
// \param p4 is destination point
// \param t is expected to be between 0 and 1
// \return Position on point at t
template<typename T, typename Scalar>
T cubicBezierCurve(const T& p1, const T& p2, const T& p3, const T& p4, Scalar t)
{
    // P = (1−t)³P1 + 3(1−t)²tP2 + 3(1−t)t²P3 + t³P4
    // p =     a    +      b     +      c     +   d

    const auto reverseT = (1 - t);

    const auto a = reverseT * reverseT * reverseT * p1;
    const auto b = 3 * reverseT * reverseT * t * p2;
    const auto c = 3 * reverseT * t * t * p3;
    const auto d = t * t * t * p4;

    return a + b + c + d;
}

}

#endif
