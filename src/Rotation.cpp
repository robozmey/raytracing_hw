//
// Created by vladimir on 17.02.24.
//

#include "Rotation.h"
#include "Position.h"

void Rotation::set(double x0, double y0, double z0, double w0) {
    x = x0;
    y = y0;
    z = z0;
    w = w0;
}
Rotation Rotation::operator*(Rotation other) const {
    Position v1 = Position(x, y, z);
    Position v2 = Position(other.x, other.y, other.z);
    Position v = v2 * w + v1 * other.w + v1 * v2;
    return {v.x, v.y, v.z, w * other.w - (v1 ^ v2)};
}

Rotation Rotation::inv() const {
    return {-x, -y, -z, w};
}