//
// Created by vladimir on 17.02.24.
//

#include "Color.h"
#include <glm/vec3.hpp>

Color operator*(double d, Color other) {
    return {d * other.r, d * other.g, d * other.b};
}

double aces_tonemap(double x)
{
    const double a = 2.51f;
    const double b = 0.03f;
    const double c = 2.43f;
    const double d = 0.59f;
    const double e = 0.14f;
    return (x*(a*x+b))/(x*(c*x+d)+e);
}

u_int8_t b2f(double c) {
    c = aces_tonemap(c);
    c = pow(c, 1 / 2.2);
    return fmax(fmin(round(c * 255), 255.0), 0.0);
}
