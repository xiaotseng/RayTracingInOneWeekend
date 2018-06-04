#pragma once
#ifndef _HITABLE_H_
#define _HITABLE_H_
#include "Ray.h"
struct hit_record
{ //射线检测记录
    float t;
    vec3 p;
    vec3 normal;
};
class hitable
{ //抽象类
  public:
    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const = 0; //纯虚函数
};
#endif