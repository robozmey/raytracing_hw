//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_ROTATION_H
#define RAYTRACING_HW_ROTATION_H

#include "Position.h"

class Rotation {
public:
    Position v;
    double w;

    Rotation(Position v0, double w0) : v(v0), w(w0) {}

    void set(Position v0, double w0);

    Rotation operator*(Rotation other) const;

    Rotation inv() const;
};


#endif //RAYTRACING_HW_ROTATION_H
