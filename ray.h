#ifndef RAY
#define RAY
#include "basic.h"
class Ray
{
public:
	Ray(){};
	Ray(Vec3d point, Vec3d direction);
	Vec3d direction() const {return dir;}
	Vec3d point() const {return p;}
	Vec3d p_at_t(double t) {return p + dir * t;}
	bool is_ray();
private:
	Vec3d p;
	Vec3d dir;
};

#endif