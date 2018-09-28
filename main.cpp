#include <iostream>
#include <fstream>
#include "drand48.h"
#include "vec3.h"
#include "hitableList.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"
using namespace std;
typedef Vec3 (*colorFunction)(const Ray &r, Hitable *wrold, int depth);
Vec3 color(const Ray &r, Hitable *wrold, int depth)
{										  //根据射线着色
	Hit_record rec;						  //每一次追踪都有一个存放结果的地方
	if (wrold->hit(r, 0.001, rec.t, rec)) //追踪场景
	{
		Ray outRay; //反射
		Vec3 attenration;
		//射线的结果传递给材质处理												 //吸光
		if (depth < 16 && rec.mat_ptr->scatter(r, rec, attenration, outRay)) //是否要继续追踪，材质定义了吸光与光的传递
		{
			return attenration * color(outRay, wrold, depth + 1); //递归着色
		}
		else
		{
			return Vec3(0, 0, 0); //不继续追踪
		}
	}
	else
	{
		//没有追踪到对象，渲染背景
		Vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction[1] + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}
static colorFunction shader = color; //着色函数
int main()
{
	int nx = 1024; //图片宽度
	int ny = 512;  //图片高度
	int ns = 8;	//采样数
	Hitable *List[4];
	List[0] = new Shphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));
	List[1] = new Shphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0)));
	List[2] = new Shphere(Vec3(-1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.5));
	List[3] = new Shphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.8, 0.6)));
	HitableList *world = new HitableList(List, 4);
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
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) //多次采样
			{
				//像素计算为uv坐标
				float u = (float(j) + drand48()) / float(nx); //像素内随机u
				float v = (float(i) + drand48()) / float(ny); //像素内随机v
				camera->updateRay(u, v, r);					  //uv求射线
				col += shader(r, world, 0);					  //着色累加
			}
			col /= float(ns); //平均颜色

			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); //浮点gama矫正

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