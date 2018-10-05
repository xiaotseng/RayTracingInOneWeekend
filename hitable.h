#pragma once
#ifndef _HITABLE_H_
#define _HITABLE_H_
#include <float.h>
#include "ray.h"
class Material;
struct Hit_record
{ //射线检测记录
    double t=DBL_MAX;
    Vec3 p;
    Vec3 normal;
    Material *mat_ptr;
};
class Hitable
{ //可追踪对象抽象类
  public:
    virtual bool hit(const Ray &r, float t_min, float t_max, Hit_record &rec) const = 0; //纯虚函数
};
#endif