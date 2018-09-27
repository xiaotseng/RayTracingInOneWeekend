#ifndef _MATERIAL_H_
#include "ray.h"
#include "hitable.h"
#include "vec3.h"
class Material
{ /*
材质抽象类
*/
  public:
    //进入射线，检测结果，光线衰减，发出射线
    virtual bool scatter(const Ray &r_in, const Hit_record &rec, Vec3 &attenuation, Ray &scattered) const = 0;
};
class Lambertian : public Material
{
  public:
    Vec3 albedo;
    Lambertian(const Vec3 &a) : albedo(a) {}
    virtual bool scatter(const Ray &r_in, const Hit_record &rec, Vec3 &attenuation, Ray &scattered) const
    {
        Vec3 target = rec.p + rec.normal + random_in_unit_sphere(); //假设目标点上方有个球与该点相切，取球体内随机取一点
        scattered = Ray(rec.p, target - rec.p);                     //再次追踪的方向
        attenuation = albedo;                                       //衰减
        return true;
    }
};
#define _MATERIAL_H_
#endif