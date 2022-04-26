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
#include <bezierpp/qt.hpp>
#include <QtCore/QDebug>

int main(int argc, char* argv[])
{
    constexpr int segmentCount = 10;

    // Linear Curve
    {
        qDebug() << "Linear Curve :";

        const QVector2D p1(1, 0);
        const QVector2D p2(0, 1);

        for(int i = 0; i < segmentCount; ++i)
        {
            const auto t = bezierpp::invLerp<float>(0.f, float(segmentCount - 1), float(i));
            const auto p = bezierpp::linearBezierCurve(p1, p2, t);

            qDebug() << i << " : " << p;
        }
    }

    qDebug() << "";

    // Quadratic Curve
    {
        qDebug() << "Quadratic Curve :";

        const QVector2D p1(0, 0);
        const QVector2D p2(0.4, 1);
        const QVector2D p3(1, 0);

        for(int i = 0; i < segmentCount; ++i)
        {
            const auto t = bezierpp::invLerp<float>(0.f, float(segmentCount - 1), float(i));
            const auto p = bezierpp::quadraticBezierCurve(p1, p2, p3, t);

            qDebug() << i << " : " << p;
        }
    }

    qDebug() << "";

    // Cubic Curve
    {
        qDebug() << "Cubic Curve :";

        const QVector2D p1(0, 0);
        const QVector2D p2(-0.1, 1);
        const QVector2D p3(0.8, 1);
        const QVector2D p4(1, 0);

        for(int i = 0; i < segmentCount; ++i)
        {
            const auto t = bezierpp::invLerp<float>(0.f, float(segmentCount - 1), float(i));
            const auto p = bezierpp::cubicBezierCurve(p1, p2, p3, p4, t);

            qDebug() << i << " : " << p;
        }
    }
}