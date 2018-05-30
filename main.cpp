#include <iostream>
#include <fstream>
#include "vec3.h"
#include "Ray.h"
#include "geometry.h"
using namespace std;
vec3 color(const Ray &r)
{ //用方向混合颜色朝上:t=1，朝下:t=0
	float t = 0.5 * (r.direction()[1] + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main()
{
	int nx = 1024; //图片宽度
	int ny = 512;  //图片高度
	std::ofstream file("exsample.ppm");
	file << "P3\n"//一定要大写的P
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

			Ray r(vec3(), NDC2ViewDir(160, 1.2, u, v));
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
	Ray *feef = new Ray(vec3(), vec3(0, 1, 0));
	vec3::forward();
	cout << feef->point_at_parameter(10);
	file.close();
	return 0;
}