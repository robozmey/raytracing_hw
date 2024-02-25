//
// Created by vladimir on 17.02.24.
//

#include "Rotation.h"

Position rotate(Position pos, Rotation rot) {
    Rotation res = (rot * Rotation(0, pos) * glm::inverse(rot));

    return {res.x, res.y, res.z};
}