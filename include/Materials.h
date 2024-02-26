//
// Created by vladimir on 26.02.24.
//

#ifndef RAYTRACING_HW_MATERIALS_H
#define RAYTRACING_HW_MATERIALS_H

enum MaterialType {
    UnknownMaterial,
    MetallicType,
    DielectricType,
    DiffuseType,
};

class Material {
public:
    double ior;
    MaterialType type = DiffuseType;
};


#endif //RAYTRACING_HW_MATERIALS_H
