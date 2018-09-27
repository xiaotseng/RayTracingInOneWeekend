#pragma once
#ifndef _GEOMETRY_H_
#include "vec3.h"
#include "drand48.h"
#define PI 3.14159265
#define TO_Radian(X) (PI / 180.0f) * X
//通过NDC坐标计算射线方向
inline vec3 NDC2ViewDir(float FOV, float rate, float u, float v)
{
	return vec3(rate * u, v, -1 / tanf(TO_Radian(FOV) / 2)).make_unit_vector(); //z为负方向
}

#define _GEOMETRY_H_
#endif