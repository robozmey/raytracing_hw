//
// Created by vladimir on 26.02.24.
//

#ifndef RAYTRACING_HW_LIGHT_H
#define RAYTRACING_HW_LIGHT_H

#include "Color.h"
#include "Position.h"

enum LightType {
    DirectionalLight,
    PositionalLight
};

class Light {
public:
    Color intensity;
    Position position;
    Position attenuation;
    Position direction;

    LightType type;
};


#endif //RAYTRACING_HW_LIGHT_H
