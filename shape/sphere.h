#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "../hitable.h"
class shphere : public hitable
{
public:
  vec3 center;
  float radius;
  shphere(){};
  shphere(vec3 cen, float r) : center(cen), radius(r){};
  virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const;
};
bool shphere::hit(const Ray &r, float t_min, float t_max, hit_record &rec) const
{
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = dot(r.direction(), oc);
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;
  if (discriminant > 0)
  {
    float temp = (-b - sqrt(discriminant)) / (2.0 * a);
    if (temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
    temp = (-b + sqrt(discriminant)) / (2.0 * a);
    if (temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
  }
  return false;
}
#endif