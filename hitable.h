#ifndef _HITABLE_H_
#define _HITABLE_H_
#include <float.h>
#include "Ray.h"
struct hit_record
{ //射线检测记录
    double t=DBL_MAX;
    vec3 p;
    vec3 normal;
};
class hitable
{ //抽象类
  public:
    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const = 0; //纯虚函数
};
#endif