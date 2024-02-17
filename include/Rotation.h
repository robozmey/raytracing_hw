//
// Created by vladimir on 17.02.24.
//

#ifndef RAYTRACING_HW_ROTATION_H
#define RAYTRACING_HW_ROTATION_H


class Rotation {
public:
    double x, y, z, w;

    Rotation(double x0, double y0, double z0, double w0) : x(x0), y(y0), z(z0), w(w0) {}

    void set(double x0, double y0, double z0, double w0);

    Rotation operator*(Rotation other) const;

    Rotation inv() const;
};


#endif //RAYTRACING_HW_ROTATION_H
