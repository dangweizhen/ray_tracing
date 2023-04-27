#include "hitbox.h"

bool Hitbox::collide(Ray& r)
{
	
	double x_min = x1 - r.point().x();
	double x_max = x2 - r.point().x();
	double y_min = y1 - r.point().y();
	double y_max = y2 - r.point().y();
	double z_min = z1 - r.point().z();
	double z_max = z2 - r.point().z();
	if(abs(r.direction().x()) > EPS)
	{
		double x_1 = x_min / r.direction().x();
		double x_2 = x_max / r.direction().x();
		x_min = min(x_1, x_2);
		x_max = max(x_1, x_2);
	}
	else
	{
		if((x1 - r.point().x()) * (x2 - r.point().x()) >= 0) return false;
		x_min = MIN_VALUE;
		x_max = MAX_VALUE;
	}

	if(abs(r.direction().y()) > EPS)
	{
		double y_1 = y_min / r.direction().y();
		double y_2 = y_max / r.direction().y();
		y_min = min(y_1, y_2);
		y_max = max(y_1, y_2);
	}
	else
	{
		if((y1 - r.point().y()) * (y2 - r.point().y()) >= 0) return false;
		y_min = MIN_VALUE;
		y_max = MAX_VALUE;
	}

	if(abs(r.direction().z()) > EPS)
	{
		double z_1 = z_min / r.direction().z();
		double z_2 = z_max / r.direction().z();
		z_min = min(z_1, z_2);
		z_max = max(z_1, z_2);
	}
	else
	{
		if((z1 - r.point().z()) * (z2 - r.point().z()) >= 0) return false;
		z_min = MIN_VALUE;
		z_max = MAX_VALUE;
	}
	return max(x_min, max(y_min, z_min)) < min(x_max, min(y_max, z_max));
}

void Hitbox::set_bond(Vec3d v1, Vec3d v2)
{
	x1 = v1.x();
	x2 = v2.x();
	y1 = v1.y();
	y2 = v2.y();
	z1 = v1.z();
	z2 = v2.z();
}