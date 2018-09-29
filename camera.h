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
    //本地到世界
    Vec3 localToWorld(Vec3 &v)
    {
        up.make_unit_vector();                              //v
        forward.make_unit_vector();                         //-w
        Vec3 right = cross(forward, up).make_unit_vector(); //u
        return v[0] * right + v[1] * up - v[2] * forward;
    }

  public:
    float FOV;  //视角
    float rate; //高宽比
    Camera(float inFOV, float inrate) : FOV(inFOV), rate(inrate)
    {
        origin = Vec3(0, 0, 0);
        up = Vec3(0, 1, 0);
        forward = Vec3(0, 0, -1);
    }
    void lookat(Vec3 &from, Vec3 &to, Vec3 &up)
    {
        origin = from;
        forward = (to - from).make_unit_vector();
        
    }
    void updateRay(float u, float v, Ray &r)
    { //通过uv计算射线
        u = u * 2 - 1;
        v = v * 2 - 1;
        u *= rate;
        Vec3 localDir = Vec3(u, v, -1 / tanf(TO_Radian(FOV) / 2.0f));
        r = Ray(origin, localToWorld(localDir));
    }
};

#endif