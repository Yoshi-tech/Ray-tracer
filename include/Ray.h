#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include <cmath>
#include <iostream>


class Ray {
public:
    Ray() {}

    Ray(const Vec3& org, const Vec3& dir) : og(org), dr(dir) {}

    Vec3 org() const { return og; }
    Vec3 dir() const { return dr; }

    Vec3 at(double par) const {
        // compute and return a point on the ray according to a given parameter
        return og + (dr * par);
    }

        Vec3 getDirection() const {
        return dr.getVec();
    }

private:
    Vec3 og; // Origin of the ray
    Vec3 dr; // Direction of the ray
};

#endif
