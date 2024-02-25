//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_PRIMITIVES_H
#define RAYTRACING_HW_PRIMITIVES_H

#include "Position.h"
#include "Ray.h"
#include "Color.h"


class Primitive {
    Position position = {0, 0, 0};
    Rotation rotation = {1, 0, 0, 0};
    Color color = {0, 0, 0};

public:
    Primitive() = default;

    Position get_position() const {
        return position;
    }
    void set_position(Position position0) {
        position = position0;
    }

    Rotation get_rotation() const {
        return rotation;
    }
    void set_rotation(Rotation rotation0) {
        rotation = rotation0;
    }

    void set_color(Color color0) {
        color = color0;
    }
    Color get_color() const {
        return color;
    }

    Ray move(Ray ray) const {
        return (ray - position).rotate(rotation);
    }

    virtual double intersection(Ray ray) const {
        return -1;
    }
};

class Plane : public Primitive {
public:
    Position normal = {0, 1, 0};
    Plane() = default;
    explicit Plane(Position normal0) : normal(normal0) {}
    double intersection(Ray ray) const override;
};

class Box : public Primitive {
public:
    Position size = {1, 1, 1};
    Box() = default;
    explicit Box(Position size0) : size(size0) {}
    double intersection(Ray ray) const override;
};

class Ellipsoid : public Primitive {
public:
    Position size = {1, 1, 1};
    Ellipsoid() = default;
    explicit Ellipsoid(Position size0) : size(size0) {}
    double intersection(Ray ray) const override;
};


#endif //RAYTRACING_HW_PRIMITIVES_H
