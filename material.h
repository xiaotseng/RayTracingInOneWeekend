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
class Metal : public Material
{
public:
  Vec3 albedo;
  float fuzz; //粗糙度
  Metal(const Vec3 &a) : albedo(a), fuzz(0.f){};
  Metal(const Vec3 &a, float f) : albedo(a) { fuzz = abs(f) < 1 ? f : 1; };
  virtual bool scatter(const Ray &r_in, const Hit_record &rec, Vec3 &attenuation, Ray &scattered) const
  {
    Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    reflected += fuzz * random_in_unit_sphere();
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(reflected, rec.normal) > 0);
  }
};
class Dielectric : public Material
{
private:
  float schlick(float cosine, float ref_idx) const
  {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 *= r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
  }

public:
  float ref_idx;
  Dielectric(float idx) : ref_idx(idx){};
  virtual bool scatter(const Ray &r_in, const Hit_record &rec, Vec3 &attenuation, Ray &scattered) const
  {
    Vec3 outward_normal;
    Vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ni_over_nt;                  //入射与出射比例
    attenuation = Vec3(1.0, 1.0, 1.0); //吸光
    Vec3 refracted;
    float reflect_prob; //反色概率
    float cosine;
    //确定光线就进还是出？
    if (dot(r_in.direction(), rec.normal) > 0) //从内部离开材质
    {
      outward_normal = -rec.normal; //反转方向
      ni_over_nt = ref_idx;         //折射率比ref_idx/1
      cosine = -ref_idx * dot(outward_normal, r_in.direction());
    }
    else
    {
      outward_normal = rec.normal;
      ni_over_nt = 1 / ref_idx; //折射率比1/ref_idx
      cosine = -dot(outward_normal, r_in.direction());
    }
    //确定反射概率
    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
      reflect_prob = schlick(cosine, ref_idx);
      //reflect_prob=0;
    }
    else
    {
      reflect_prob = 1.0;
    }
    //
    if (reflect_prob > drand48())
    {
      scattered =Ray(rec.p,reflected) ; //
    }
    else
    {
      scattered =Ray(rec.p,refracted);
   
    }

    return true;
  }
};
#define _MATERIAL_H_
#endif