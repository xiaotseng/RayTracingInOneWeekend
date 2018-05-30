#pragma once
#include "vec3.h"
class Ray
{
  public:
    vec3 A, B;
    Ray(const vec3 &o, const vec3 &d) : A(o), B(d){};
    const vec3 &origin() const { return A; }
    const vec3 &direction() const { return B; }
    vec3 point_at_parameter(float t) { return A + B * t; }
};
