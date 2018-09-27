#pragma once
#ifndef _RAY_H_
#include "vec3.h"
class Ray
{
public:
  Vec3 A, B;//原点和方向
  //类内部定义的函数都会被当做内联函数，不会计入符号表
  Ray(){Vec3(),Vec3();};
  Ray(const Vec3 &o, const Vec3 &d) : A(o), B(d){};
  const Vec3 &origin() const { return A; }
  const Vec3 &direction() const { return B; }
  Vec3 point_at_parameter(float t) const { return A + B * t; }
};
#define _RAY_H_
#endif