#ifndef ALOGDAT_LABYRINTH_MATHUTILS_H
#define ALOGDAT_LABYRINTH_MATHUTILS_H

#include <cmath>

template<typename T>
struct Vector2 {
    T x, y;

    Vector2() : x(), y() { }
    Vector2(T X, T Y) : x(X), y(Y) { }
};

using Vector2f = Vector2<float>;

float Distance(const Vector2f& a, const Vector2f& b);
#endif //ALOGDAT_LABYRINTH_MATHUTILS_H
