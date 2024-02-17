//
// Created by vladimir on 17.02.24.
//

#include "Rotation.h"
#include "Position.h"

void Rotation::set(Position v0, double w0) {
    v = v0;
    w = w0;
}
Rotation Rotation::operator*(Rotation other) const {
    Position v12 = other.v * w + v * other.w + v * other.v;
    return {v12, w * other.w - (v ^ other.v)};
}

Rotation Rotation::inv() const {
    return {-1 * v, w};
}