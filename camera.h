#ifndef CAMERA
#define CAMERA

#include "basic.h"
#include "ray.h"


class Camera
{
public:
	Camera(int x, int y, int z, Vec3d o, Vec3d d = Vec3d(0,0,-1), int len = 0):x_size(x), y_size(y), length(z), origin(o), dir(d), lens(len){dir.norm();}
	Ray get_ray(int i, int j);
private:
	Vec3d origin;
	Vec3d dir;
	int x_size;
	int y_size;
	int lens;
	double length;
};

#endif