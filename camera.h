#ifndef CAMERA
#define CAMERA

#include "basic.h"
#include "ray.h"


class Camera
{
public:
	Camera(int x, int y, int z, Vec3d o):x_size(x), y_size(y), length(z), origin(o){}
	Ray get_ray(int i, int j);
private:
	Vec3d origin;
	int x_size;
	int y_size;
	int length;
};

#endif