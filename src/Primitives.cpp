//
// Created by vladimir on 17.02.24.
//

#include "Primitives.h"

double Plane::intersection(Ray ray) const {
    double on = ray.origin ^ normal;
    double dn = ray.direction ^ normal;
    if (dn == 0) return -1;
    return - on / dn;
}

double Box::intersection(Ray ray) const  {
    auto t1 = (size - ray.origin) / (ray.direction);
    auto t2 = (size * (-1) - ray.origin) / (ray.direction);
    if (t1.x > t2.x) std::swap(t1.x, t2.x);
    if (t1.y > t2.y) std::swap(t1.y, t2.y);
    if (t1.z > t2.z) std::swap(t1.z, t2.z);
    double t1_ = std::max(t1.x, std::max(t1.y, t1.z));
    double t2_ = std::min(t2.x, std::min(t2.y, t2.z));

    if (t1_ > t2_) return -1;
    if (t1_ > 0) return t1_;
    return t2_;
}

double Ellipsoid::intersection(Ray ray) const  {
    double a = (ray.direction / size) ^ (ray.direction / size);
    double b = (ray.origin    / size) ^ (ray.direction / size) * 2;
    double c =((ray.origin    / size) ^ (ray.origin    / size)) -1;
    double d = b*b - 4*a*c;
    if (d < 0) return -1;
    double t1 = (-b + sqrt(d)) / (2 * a);
    double t2 = (-b - sqrt(d)) / (2 * a);
    if (t1 < t2 && t1 > 0)
    return t1;
    else
    return t2;
}
