//
// Created by vladimir on 17.02.24.
//

#include "Position.h"

#include <cmath>

void Position::set(double x0, double y0, double z0) {
    x = x0;
    y = y0;
    z = z0;
}

Position Position::operator+(Position other) const {
    return {x + other.x, y + other.y,  z + other.z};
}
Position Position::operator-(Position other) const {
    return {x - other.x, y - other.y,  z - other.z};
}
Position Position::operator*(Position other) const {
    return {x * other.x, y * other.y,  z * other.z};
}
Position Position::operator/(Position other) const {
    return {x / other.x, y / other.y,  z / other.z};
}
double Position::operator^(Position other) const {
    return x * other.x + y * other.y + z * other.z;
}

Position Position::operator*(double c) const {
    return {x * c, y * c, z * c};
}

Position Position::normalize() const {
    double norm = sqrt(x * x + y * y + z * z);
    return {x / norm, y / norm, z / norm};
}

Position Position::rotate(Rotation rotation) const {

    Rotation res = rotation * Rotation({x, y, z}, 0.0) * rotation.inv();

    return res.v;
}

Position operator*(double c, const Position &other) {
    return {other.x * c, other.y * c, other.z * c};
}
