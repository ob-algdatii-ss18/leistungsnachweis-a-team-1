#include "MathUtils.h"

float Distance(const Vector2f& a, const Vector2f& b) {
    float x = b.x - a.x;
    float y = b.y - a.y;
    return sqrtf(x * x + y * y);
}
