#ifndef _SPHERE_H_
#define _SPHERE_H_
#include <hitable.h>
class shphere : public hitable
{
  public:
    vec3 center;
    float radius;
    shphere(){};
    shphere(vec3 cen, float r) : center(cen), radius(r){};
    
};
#endif