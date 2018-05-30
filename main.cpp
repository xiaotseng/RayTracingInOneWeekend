#include <iostream>
#include <fstream>
#include "vec3.h"
#include"Ray.h"
using namespace std;
int main() {
	int nx = 200;
	int ny = 100;
	std::ofstream file("exsample.txt");
	file << "p3\n" << nx << " " << ny <<"\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);//左下角
	vec3 horizontal(4.0, 0, 0);
	vec3 vertical(0, 2.0, 0);
	vec3 origin(0, 0, 0);
	for ( int i = ny-1; i >=0;i--)
	{
		for (int j =0; j<nx; j++)
		{
			float u = float(j) /float( nx - 1);
			float v = float(i) / float(ny - 1);
			vec3 col(float(j) / float(nx - 1), float(i) / float(ny - 1),0.2f);
			int ir = int(255.f*col[0]);
			int ig = int(255.f*col[1]);
			int ib = int(255.f*col[2]);
			u = u * 2 - 1;
			v = v * 2 - 1;
			file << u << " " << v <<" "<< "\n"; 
		}
	}
	Ray* feef = new Ray(vec3(), vec3(0, 1, 0));
	vec3::forward();
	cout << feef->point_at_parameter(10);
	file.close();
    return 0;


}