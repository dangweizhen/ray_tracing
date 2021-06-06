#include "ray.h"
#include "basic.h"
#include <cmath>

Ray::Ray(Vec3d point, Vec3d direction)
{
	p = point;
	dir = direction;
	dir.norm();
}

bool Ray::is_ray()
{
	if(abs(dir.x()) < EPS && abs(dir.y()) < EPS && dir.z() < EPS) return false;
	return true;
}