#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Ray.h"
#define PI 3.14159265
#define TO_Radian(X) (PI / 180.0f) * X
class Camera
{
  private:
    Vec3 forward;
    Vec3 up;
    Vec3 origin;
    float FOV;            //视角
    float rate;           //宽高比
    float defocus;        //对焦平面距离
    float aperture = 0.2; //光圈

    //本地到世界
    Vec3 localToWorld(const Vec3 &v)
    {
        up.make_unit_vector();                              //v
        forward.make_unit_vector();                         //-w
        Vec3 right = cross(forward, up).make_unit_vector(); //u
        return v[0] * right + v[1] * up - v[2] * forward;
    }

  public:
    Camera(float inFOV, float inrate) : FOV(inFOV), rate(inrate)
    {
        origin = Vec3(0, 0, 0);
        up = Vec3(0, 1, 0);
        forward = Vec3(0, 0, -1);
    }
    void lookat(const Vec3 &from, const Vec3 &to, const Vec3 &upDir)
    {
        origin = from;
        forward = (to - from);
        defocus = forward.length();
        forward.make_unit_vector();
        Vec3 right = cross(forward, upDir);
        up = cross(right, forward).make_unit_vector();
    }
    void updateRay(float u, float v, Ray &r)
    { //通过uv计算射线
        float halfTanf = tanf(TO_Radian(FOV) / 2.0f);
        Vec3 rd = random_in_unit_disk() * aperture; //射线起点
        u = u * 2 - 1;
        u *= halfTanf * rate;
        v = v * 2 - 1;
        v *= halfTanf;
        Vec3 localDir = Vec3(u, v, -1) * defocus - rd; //对焦平面
        r = Ray(origin + localToWorld(rd), localToWorld(localDir).make_unit_vector());
    }
};

#endif