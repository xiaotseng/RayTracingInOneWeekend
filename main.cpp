#include <iostream>
#include "float.h"
#include <fstream>
#include "vec3.h"
#include "hitableList.h"
#include "shape/sphere.h"
#include "geometry.h"
//#include "Lib/add.h"
using namespace std;
vec3 color(const Ray &r,hitable* wrold)
{ //根据射线求颜色
	hit_record rec;
	if (wrold->hit(r,0.0,FLT_MAX,rec))
	{
		vec3 N = rec.normal; //求法线向量
		return N * 0.5f + 0.5;									//从-1~1映射到0~1
	}
	//背景绘制，用方向混合颜色朝上:t=1，朝下:t=0
	float t = 0.5 * (r.direction()[1] + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main()
{
	int nx = 512; //图片宽度
	int ny = 512; //图片高度
	hitable *List[2];
	List[0] = new shphere(vec3(0, 0, -1), 0.5);
	List[1] = new shphere(vec3(0, -100, 1), 100);
	hitableList *world = new hitableList(List, 2);
	std::ofstream file("exsample.ppm");
	file << "P3\n" //一定要大写的P
		 << nx << " " << ny << "\n255\n";

	for (int i = ny - 1; i >= 0; i--)
	{

		for (int j = 0; j < nx; j++)
		{
			//像素计算为uv坐标
			float u = float(j) / float(nx - 1);
			float v = float(i) / float(ny - 1);
			//uv坐标计算为NDC空间坐标
			u = u * 2 - 1;
			v = v * 2 - 1;
			//NDC坐标计算为射线
			Ray r(vec3(), NDC2ViewDir(160, float(nx) / float(ny), u, v)); //构建一个方向
			//方向y分量计算浮点颜色
			vec3 col = color(r,world);

			//浮点颜色到整型颜色
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
	system("pause");
	return 0;
}