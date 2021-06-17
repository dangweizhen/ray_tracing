#include "primitives.h"
#include "basic.h"
#include <cmath>
#include <cstdlib>


double Sphere::collide(Ray r)
{
	//At^2+Bt+C = 0
	double A = dot(r.direction(), r.direction());
	double B = 2 * dot(r.direction(), r.point() - o);
	double C = dot(r.point() - o, r.point() - o) - d * d;
	double delta = B * B - 4 * A * C;
	if(delta < -1 * EPS) return delta;
	if(delta > EPS) 
	{
		double t1 = (-1 * B + sqrt(delta)) / (2 * A);
		double t2 = (-1 * B - sqrt(delta)) / (2 * A);
		if(t2 < EPS) return t1;
		else return t2;
	}
	return (-1 * B) / (2 * A);
}

Vec3d Sphere::getNorm(Vec3d p)
{
	Vec3d res(p - o);
	res.norm();
	return res;
}

Ray Sphere::nextRay(Ray r, Vec3d collide_point)
{
	Vec3d normal = getNorm(collide_point);
	return m->process_ray(r, collide_point, normal);
}
