//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_RAY_H
#define RAYTRACING_HW_RAY_H

#include "Position.h"
#include "Rotation.h"

struct Intersection {
    Position position = {0, 0, 0};
    Position normal = {0, 0, 0};
};

class Ray {
public:
    Position origin = {0, 0, 0};
    Position direction = {0, 0, 1};
    int depth = 5;
    bool is_inside_ray = false;
    Ray() = default;

    Ray operator+(Position d) {
        return {origin + d, direction, depth, is_inside_ray};
    }

    Ray operator-(Position d) {
        return {origin - d, direction, depth, is_inside_ray};
    }

    Position getPoint(double t) {
        return origin + direction * t;
    }

    Ray rotate(Rotation rotation) {
        return {::rotate(origin, rotation), ::rotate(direction, rotation), depth, is_inside_ray};
    }
};


#endif //RAYTRACING_HW_RAY_H
