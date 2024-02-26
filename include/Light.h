//
// Created by vladimir on 26.02.24.
//

#ifndef RAYTRACING_HW_LIGHT_H
#define RAYTRACING_HW_LIGHT_H

#include "Color.h"
#include "Position.h"
#include <glm/glm.hpp>

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

    double getCoefficient(Position point) const {
        if (type == DirectionalLight) return 1.0;
        double r = glm::distance(position, point);
        return 1.0 / (attenuation.x + attenuation.y * r + attenuation.z * r * r);
    }

    Position getDirection(Position point) const {
        if (type == DirectionalLight) return direction;
        return - glm::normalize(point - position);
    }
};


#endif //RAYTRACING_HW_LIGHT_H
