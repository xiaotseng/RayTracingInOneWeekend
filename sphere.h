#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "hitable.h"
class Material;
class Shphere : public Hitable
{
public:
  Material *mat_ptr;
  Vec3 center;
  float radius;
  Shphere(){};
  Shphere(Vec3 cen, float r, Material *mat) : center(cen), radius(r),mat_ptr(mat){};
  virtual bool hit(const Ray &r, float t_min, float t_max, Hit_record &rec) const;
};
bool Shphere::hit(const Ray &r, float t_min, float t_max, Hit_record &rec) const
{
  Vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = dot(r.direction(), oc);
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - a * c;
  if (discriminant > 0)
  {
    float temp = (-b - sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr=mat_ptr;
      return true;
    }
    temp = (-b + sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr=mat_ptr;
      return true;
    }
  }
  return false;
}
#endif