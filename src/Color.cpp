//
// Created by vladimir on 17.02.24.
//

#include "Color.h"

Color operator*(double d, Color other) {
    return {d * other.r, d * other.g, d * other.b};
}

u_int8_t b2f(double c) {
    return fmin(round(c * 255), 255.0);
}
