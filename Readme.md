# Bezierpp

Header only library to create bezier curve, in 2D or 3D.

## Usage

> Examples can be found in `examples` folder. Integration usage is shown with [Eigen](https://eigen.tuxfamily.org) and [Qt](https://www.qt.io/).

### Lerp & InvLerp

The library provide convenient lerp and invLerp functions.

```cpp
bezierpp::lerp( a, b, t ) = value
bezierpp::invLerp( a, b, value ) = t
```

![](https://uploads.gamedev.net/monthly_2019_10/1.gif.4cd2689cefca32175d9b58fca4f45fe7.gif)

### Linear Curve

```cpp
#include <bezierpp/bezierpp.hpp>
#include <Eigen/Core>
#include <iostream>

constexpr int segmentCount = 10;
const Eigen::Vector2d p1(1, 0);
const Eigen::Vector2d p2(0, 1);

for(int i = 0; i < segmentCount; ++i)
{
  const auto t = bezierpp::invLerp<float>(0.f, float(segmentCount - 1), float(i));
  const auto p = bezierpp::linearBezierCurve(p1, p2, t);
  std::cout << p << std::endl;
}
```

![Animation of a linear Bézier curve, *t* in [0,1]](https://upload.wikimedia.org/wikipedia/commons/thumb/0/00/B%C3%A9zier_1_big.gif/240px-B%C3%A9zier_1_big.gif)

### Quadratic Curve

```cpp
#include <bezierpp/bezierpp.hpp>
#include <Eigen/Core>
#include <iostream>

constexpr int segmentCount = 10;
const Eigen::Vector2d p1(0, 0);
const Eigen::Vector2d p2(0.4, 1);
const Eigen::Vector2d p3(1, 0);
for(int i = 0; i < segmentCount; ++i)
{
    const auto t = bezierpp::invLerp<float>(0.f, float(segmentCount - 1), float(i));
    const auto p = bezierpp::quadraticBezierCurve(p1, p2, p3, t);
    std::cout << i << " : " << p.format(CleanFmt) << std::endl;
}
```



![Animation of a quadratic Bézier curve, *t* in [0,1]](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3d/B%C3%A9zier_2_big.gif/240px-B%C3%A9zier_2_big.gif)

### Cubic Curve

```cpp
#include <bezierpp/bezierpp.hpp>
#include <Eigen/Core>
#include <iostream>

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
```



![Animation of a cubic Bézier curve, *t* in [0,1]](https://upload.wikimedia.org/wikipedia/commons/thumb/d/db/B%C3%A9zier_3_big.gif/240px-B%C3%A9zier_3_big.gif)

### Smooth Spline

If you want to draw smooth spline as describe in the [article](http://scaledinnovation.com/analytics/splines/aboutSplines.html), a convenient `getBezierControlPoints` is provided by the library.

![](http://scaledinnovation.com/analytics/splines/splineDefault.png)

The `getBezierControlPoints` require the norm of the vector, so `getNorm` should be specialized if using type different than Eigen. For example with Qt QVector3D:

```cpp
#include <QtGui/QVector3D>

namespace bezierpp{
template<>
float getNorm<QVector3D, float>(const QVector3D& value)
{
    return value.length();
}
}
```

For convenience, specialization is already provided for qt in `bezierpp/qt.hpp`

### Examples

Eigen example output:

```
Linear Curve :
0 : 1, 0
1 : 0.888889, 0.111111
2 : 0.777778, 0.222222
3 : 0.666667, 0.333333
4 : 0.555556, 0.444444
5 : 0.444444, 0.555556
6 : 0.333333, 0.666667
7 : 0.222222, 0.777778
8 : 0.111111, 0.888889
9 : 0, 1

Quadratic Curve :
0 : 0, 0
1 : 0.091358, 0.197531
2 : 0.187654, 0.345679
3 : 0.288889, 0.444444
4 : 0.395062, 0.493827
5 : 0.506173, 0.493827
6 : 0.622222, 0.444444
7 :  0.74321, 0.345679
8 : 0.869136, 0.197531
9 : 1, 0

Cubic Curve :
0 : 0, 0
1 : 0.00137174, 0.296296
2 : 0.0628258, 0.518519
3 : 0.17037, 0.666667
4 : 0.310014, 0.740741
5 : 0.467764, 0.740741
6 : 0.62963, 0.666667
7 : 0.781619, 0.518519
8 : 0.909739, 0.296296
9 : 1, 0
```

Qt example output:

```
Linear Curve :
0  :  QVector2D(1, 0)
1  :  QVector2D(0.888889, 0.111111)
2  :  QVector2D(0.777778, 0.222222)
3  :  QVector2D(0.666667, 0.333333)
4  :  QVector2D(0.555556, 0.444444)
5  :  QVector2D(0.444444, 0.555556)
6  :  QVector2D(0.333333, 0.666667)
7  :  QVector2D(0.222222, 0.777778)
8  :  QVector2D(0.111111, 0.888889)
9  :  QVector2D(0, 1)

Quadratic Curve :
0  :  QVector2D(0, 0)
1  :  QVector2D(0.091358, 0.197531)
2  :  QVector2D(0.187654, 0.345679)
3  :  QVector2D(0.288889, 0.444444)
4  :  QVector2D(0.395062, 0.493827)
5  :  QVector2D(0.506173, 0.493827)
6  :  QVector2D(0.622222, 0.444444)
7  :  QVector2D(0.74321, 0.345679)
8  :  QVector2D(0.869136, 0.197531)
9  :  QVector2D(1, 0)

Cubic Curve :
0  :  QVector2D(0, 0)
1  :  QVector2D(0.00137174, 0.296296)
2  :  QVector2D(0.0628258, 0.518519)
3  :  QVector2D(0.17037, 0.666667)
4  :  QVector2D(0.310014, 0.740741)
5  :  QVector2D(0.467764, 0.740741)
6  :  QVector2D(0.62963, 0.666667)
7  :  QVector2D(0.781619, 0.518519)
8  :  QVector2D(0.909739, 0.296296)
9  :  QVector2D(1, 0)
```



## 🔨 How to use

### CPM

The library support [CPM](https://github.com/cpm-cmake/CPM.cmake).

```cmake
include(CPM.cmake)
CPMAddPackage(
  GIT_REPOSITORY https://github.com/OlivierLDff/bezierpp
  GIT_TAG main
)
```

### Header only

Just copy header located in `src` in your project include directory.

### Installation

```bash
git clone https://github.com/OlivierLDff/bezierpp
cmake -E make_directory bezierpp/build
cmake -DCMAKE_PREFIX_PATH=install  \
      -DBEZIERPP_ENABLE_INSTALL=ON \
      -B bezierpp/build -S bezierpp
```

This will create under `install` folder following hierarchy:

```
include
 └─bezierpp
    └─bezierpp.hpp
lib
 └─cmake
    └─bezierpp-version
       ├─bezierppConfig.cmake
       ├─bezierppConfigVersion.cmake
       └─bezierppTargets.cmake
```

## Bibliography

* [Bezier Curve on Wikipedia](https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Constructing_B%C3%A9zier_curves)
* [About Splines](http://scaledinnovation.com/analytics/splines/aboutSplines.html)

## 👥 Author

* [Olivier Le Doeuff](olivier.ldff@gmail.com)