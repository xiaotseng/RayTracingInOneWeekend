#include <iostream>
#include <fstream>
#include "drand48.h"
#include "vec3.h"
#include "hitableList.h"
#include "shape/sphere.h"
#include "camera.h"
#include "geometry.h"
using namespace std;

vec3 color(const Ray &r, hitable *wrold)
{ //根据射线求颜色
	hit_record rec;
	if (wrold->hit(r, 0.001, rec.t, rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere(); //假设目标点上方有个球与该点相切，取球体内随机取一点
		vec3 direction = (target - rec.p).make_unit_vector();		//再次追踪的方向
		return 0.5 * color(Ray(rec.p, direction), wrold);			//0.5是衰减
	}
	//背景绘制，用方向混合颜色朝上:t=1，朝下:t=0
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction[1] + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main()
{
	int nx = 1024; //图片宽度
	int ny = 512;  //图片高度
	int ns = 8;	//采样数
	hitable *List[2];
	List[0] = new shphere(vec3(0, 0, -1), 0.5);
	List[1] = new shphere(vec3(0, -100.5, -1), 100);
	hitableList *world = new hitableList(List, 2);
	Camera *camera = new Camera(90, float(nx) / float(ny)); //相机
	Ray r;													//射线
	//文件对象
	std::ofstream file("exsample.ppm");
	file << "P3\n" //一定要大写的P
		 << nx << " " << ny << "\n255\n";

	for (int i = ny - 1; i >= 0; i--)
	{

		for (int j = 0; j < nx; j++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) //多次采样
			{
				//像素计算为uv坐标
				float u = (float(j) + drand48()) / float(nx); //像素内随机u
				float v = (float(i) + drand48()) / float(ny); //像素内随机v
				camera->updateRay(u, v, r);					  //uv求射线
				col += color(r, world);						  //着色累加
			}
			col /= float(ns); //平均颜色

			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); //浮点gama矫正

			//浮点颜色到整型颜色
			int ir = int(255.f * col[0]);
			int ig = int(255.f * col[1]);
			int ib = int(255.f * col[2]);

			//写入文件
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
	system("pause");
	return 0;
}