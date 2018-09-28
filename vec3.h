#ifndef _MATH_H_
#define _MATH_H_
#include <math.h>
#include <stdlib.h>
#include <iostream>
class Vec3
{
  public:
    static Vec3 forward() { return Vec3(1, 0, 0); }
    float e[3];
    Vec3() { e[0] = e[1] = e[2] = 0.f; };
    Vec3(float e0, float e1, float e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const Vec3 &operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }

    inline Vec3 &operator+=(const Vec3 &v2);
    inline Vec3 &operator-=(const Vec3 &v2);
    inline Vec3 &operator*=(const Vec3 &v2);
    inline Vec3 &operator/=(const Vec3 &v2);
    inline Vec3 &operator*=(const float t);
    inline Vec3 &operator/=(const float t);

    inline float length() const
    {
        return sqrt(sqaured_length());
    }
    inline float sqaured_length() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    inline Vec3 &make_unit_vector();
};
inline std::istream &operator>>(std::istream &is, Vec3 &t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}
inline std::ostream &operator<<(std::ostream &os, const Vec3 &t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}
inline Vec3 &Vec3::make_unit_vector()
{
    //规格化向量
    const float k = 1 / length();
    *this *= k;
    return *this;
}
//加法
inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
inline Vec3 operator+(const Vec3 &v, const float &t)
{
    return Vec3(v.e[0] + t, v.e[1] + t, v.e[2] + t);
}
inline Vec3 operator+(const float &t, const Vec3 &v)
{
    return Vec3(v.e[0] + t, v.e[1] + t, v.e[2] + t);
}
//减法
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
inline Vec3 operator-(const Vec3 &v, const float &t)
{
    return Vec3(v.e[0] - t, v.e[1] - t, v.e[2] - t);
}
//乘法
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
inline Vec3 operator*(const float &t, const Vec3 &v)
{
    return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}
inline Vec3 operator*(const Vec3 &v, const float &t)
{
    return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}
//除法
inline Vec3 operator/(const Vec3 &v, const float &t)
{
    return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}
//点积
inline float dot(const Vec3 &v1, const Vec3 &v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}
//差积
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(
        v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
        v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
        v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}
//原位加法
inline Vec3 &Vec3::operator+=(const Vec3 &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}
inline Vec3 &Vec3::operator-=(const Vec3 &v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}
inline Vec3 &Vec3::operator*=(const Vec3 &v)
{
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}
inline Vec3 &Vec3::operator/=(const Vec3 &v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}
inline Vec3 &Vec3::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}
inline Vec3 &Vec3::operator/=(const float t)
{
    float k = 1.f / t;
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}
inline Vec3 unit_vector(const Vec3 &v)
{
    return v / v.length();
}

inline Vec3 random_in_unit_sphere()
{ //单位球体里随机取一点
    Vec3 p;
    do
    {
        p = Vec3(drand48(), drand48(), drand48()) * 2.0 - Vec3(1, 1, 1);
    } while (p.sqaured_length() >= 1.0);
    return p;
}
//计算反射向量
inline Vec3 reflect(const Vec3 &v, const Vec3 &n)
{
    return v - dot(v, n) * 2 * n;
}
//计算折射向量
inline bool refract(const Vec3 &v, const Vec3 &n, float ni_over_nt, Vec3 &refracted)
{
    float dt = dot(v, n);
    float discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt); //入射介质的折射率大于出射介质的折射率，同时入射夹角大到一个值时该值为负。
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (v - dt * n) - n * sqrt(discriminant);
        return true;
    }
    else
    {
        return false;
    }
}
#endif