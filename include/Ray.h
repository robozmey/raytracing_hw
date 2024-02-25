//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_RAY_H
#define RAYTRACING_HW_RAY_H

#include "Position.h"
#include "Rotation.h"

class Ray {
public:
    Position origin = {0, 0, 0};
    Position direction = {0, 0, 1};
    Ray() = default;

    Ray operator+(Position d) {
        return {origin + d, direction};
    }

    Ray operator-(Position d) {
        return {origin - d, direction};
    }

    Ray rotate(Rotation rotation) {
        return {::rotate(origin, rotation), ::rotate(direction, rotation)};
    }
};


#endif //RAYTRACING_HW_RAY_H
