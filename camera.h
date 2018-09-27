#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Ray.h"
#define PI 3.14159265
#define TO_Radian(X) (PI / 180.0f) * X
class Camera
{
  public:
    float FOV;  //视角
    float rate; //高宽比
    Camera(float inFOV, float inrate)
    {
        FOV = inFOV;
        rate = inrate;
    }
    void updateRay(float u, float v, Ray &r)
    { //通过uv计算射线
        u = u * 2 - 1;
        v = v * 2 - 1;
        u *= rate;
        r.A = Vec3();
        r.B = Vec3(u, v, -1 / tanf(TO_Radian(FOV) / 2.0f)).make_unit_vector();
    }
};

#endif