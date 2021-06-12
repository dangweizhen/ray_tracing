#include "camera.h"
#include <cstdlib>

Ray Camera::get_ray(int i, int j)
{
	double delta_x = (rand() - RAND_MAX / 2.0) / double(RAND_MAX);
	double delta_y = (rand() - RAND_MAX / 2.0) / double(RAND_MAX);
	Ray r(origin, Vec3d(i-y_size/2.0+delta_y, x_size/2.0-j+delta_x, origin.z() + length) - origin);
	return r;
}