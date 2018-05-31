#include <iostream>
#include <fstream>
#include "vec3.h"
#include "Ray.h"
#include "geometry.h"
using namespace std;
float hit_sphere(const vec3 &center, float radius, const Ray &r)
{ //假设射线上有一个点P(t),满足(P(t)-center)和模平方为radius的平方。求射线方向上是否有解
	//dot(P(t)-center,P(t)-center)=radius*radius
	const vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2 * dot(r.direction(), oc);
	float c = dot(oc, oc);
	float rr = radius * radius;
	c = c - rr;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0)
	{ //判定一元二次方程有没有解b*b-4a*c
		return -1.0;
	}
	else
	{
		return (-b - sqrtf(discriminant)) / (2.0 * a);
	}
}
vec3 color(const Ray &r)
{ //根据射线求颜色
	vec3 center = vec3(0, 0, -1);
	float t = hit_sphere(center, 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.point_at_parameter(t) - center); //求法线向量
		return N * 0.5f + 0.5;									//从-1~1映射到0~1
	}
	//背景绘制，用方向混合颜色朝上:t=1，朝下:t=0
	t = 0.5 * (r.direction()[1] + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main()
{
	int nx = 512; //图片宽度
	int ny = 512; //图片高度
	std::ofstream file("exsample.ppm");
	file << "P3\n" //一定要大写的P
		 << nx << " " << ny << "\n255\n";

	for (int i = ny - 1; i >= 0; i--)
	{

		for (int j = 0; j < nx; j++)
		{
			float u = float(j) / float(nx - 1);
			float v = float(i) / float(ny - 1);
			//NDC空间坐标
			u = u * 2 - 1;
			v = v * 2 - 1;

			Ray r(vec3(), NDC2ViewDir(160, float(nx) / float(ny), u, v));
			//浮点颜色
			vec3 col = color(r);

			//整型颜色
			int ir = int(255.f * col[0]);
			int ig = int(255.f * col[1]);
			int ib = int(255.f * col[2]);

			file << ir << " " << ig << " " << ib;
			if (j == nx - 1)
			{
				file << "\n";
			}
			else
			{
				file << " ";
			}
		}
	}
	file.close();
	return 0;
}