//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_ROTATION_H
#define RAYTRACING_HW_ROTATION_H

#include <glm/gtc/quaternion.hpp>

typedef glm::dquat Rotation;

#include "Position.h"

Position rotate(Position pos, Rotation rot);


#endif //RAYTRACING_HW_ROTATION_H
