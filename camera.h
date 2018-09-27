#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Ray.h"
#define PI 3.14159265
#define TO_Radian(X) (PI / 180.0f) * X
class Camera
{
  public:
    float FOV;
    float rate;
    Camera(float inFOV, float inrate)
    {
        FOV = inFOV;
        rate = inrate;
    }
    void updateRay(float u, float v, Ray &r)
    {
        u = u * 2 - 1;
        v = v * 2 - 1;
        u *= rate;
        r.A = vec3();
        r.B = vec3(u, v, -1 / tanf(TO_Radian(FOV) / 2.0f)).make_unit_vector();
    }
};

#endif