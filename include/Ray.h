//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_RAY_H
#define RAYTRACING_HW_RAY_H

#include "Position.h"

class Ray {
public:
    Position origin = {0, 0, 0};
    Position direction = {0, 0, 1};
    Ray() = default;
};


#endif //RAYTRACING_HW_RAY_H
