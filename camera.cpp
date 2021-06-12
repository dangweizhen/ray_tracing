#include "camera.h"
#include "basic.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

Ray Camera::get_ray(int i, int j)
{

	Vec3d x_d;
	Vec3d y_d;
	if(abs(dir.x()) <= EPS)
		x_d = Vec3d(1, 0, 0);
	else
		x_d = Vec3d(dir.z() / dir.x(), 0, 1);
	if(abs(dir.y()) <= EPS)
		y_d = Vec3d(0, 1, 0);
	else
		y_d = Vec3d(0, dir.z() / dir.y(), 1);
	x_d.norm();
	y_d.norm();
	double delta_x = (rand() - RAND_MAX / 2.0) / double(RAND_MAX);
	double delta_y = (rand() - RAND_MAX / 2.0) / double(RAND_MAX);
	double a = (rand() - RAND_MAX / 2.0) / double(RAND_MAX);
	double b = (rand() - RAND_MAX / 2.0) / double(RAND_MAX);
	Vec3d foucus = x_d * a + y_d * b;
	foucus.norm();
	double f = double(RAND_MAX - rand()) / double(RAND_MAX);
	foucus = foucus * (f * lens);
	//foucus.print();
	Vec3d center = origin + dir * length;
	Vec3d up_left = center - x_d * (x_size / 2.0) - y_d * (y_size / 2.0);
	Ray r(origin + foucus, up_left + x_d * (i + delta_x) + y_d * (j + delta_y) - (origin+foucus));
	return r;
}