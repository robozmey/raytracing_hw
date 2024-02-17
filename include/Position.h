//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_POSITION_H
#define RAYTRACING_HW_POSITION_H


#include "Rotation.h"

class Position {
public:
    double x, y, z;
    Position() = default;
    Position(double x0, double y0, double z0) : x(x0), y(y0), z(z0) {}
    void set(double x0, double y0, double z0);

    Position operator+(Position other) const;
    Position operator-(Position other) const;
    Position operator*(Position other) const;
    Position operator/(Position other) const;
    double operator^(Position other) const;

    Position operator*(double c) const;

    Position normalize() const;
    Position rotate(Rotation rotation) const;
};

Position operator*(double c, const Position& other);


#endif //RAYTRACING_HW_POSITION_H
