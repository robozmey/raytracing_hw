//
// Created by vladimir on 17.02.24.
//

#include "Rotation.h"

Position rotate(Position pos, Rotation rot) {
    Rotation res = (rot * Rotation(0, pos.x, pos.y, pos.z) * glm::conjugate(rot));

    return {res.x, res.y, res.z};
}