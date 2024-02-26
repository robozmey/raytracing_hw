//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_COLOR_H
#define RAYTRACING_HW_COLOR_H

#include <cmath>

class Color {
public:
    double r, g, b;
    void set(double r0, double g0, double b0) {
        r = r0;
        g = g0;
        b = b0;
    }

    Color operator+(Color other) const {
        return {r + other.r, g + other.g, b + other.b};
    }
    Color operator+=(Color other) {
        r += other.r;
        b += other.b;
        g += other.g;
        return {r, g, b};
    }
    Color operator-(Color other) const {
        return {r - other.r, g - other.g, b - other.b};
    }
    Color operator*(Color other) const {
        return {r * other.r, g * other.g, b * other.b};
    }
    Color operator*(double other) const {
        return {r * other, g * other, b * other};
    }
};

Color operator*(double d, Color other);


u_int8_t b2f(double c);


#endif //RAYTRACING_HW_COLOR_H
