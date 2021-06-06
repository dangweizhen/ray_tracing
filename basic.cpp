#include "basic.h"
#include <cmath>



Vec3d Vec3d::operator+(const Vec3d &v) const
{
	return Vec3d(x_v + v.x_v, y_v + v.y_v, z_v + v.z_v);
}


Vec3d Vec3d::operator-(const Vec3d &v) const
{
	return Vec3d(x_v - v.x_v, y_v - v.y_v, z_v - v.z_v);
}

Vec3d Vec3d::operator*(const double d) const
{
	return Vec3d(x_v * d, y_v * d, z_v * d);
}
void Vec3d::norm()
{
	double m = x_v * x_v + y_v * y_v + z_v * z_v;
	if(m != 0)
	{
		x_v /= sqrt(m);
		y_v /= sqrt(m);
		z_v /= sqrt(m);
	}
}


double dot(Vec3d v1, Vec3d v2)
{
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

Color::Color(double r_val, double g_val, double b_val)
{
	r_v = r_val;
	g_v = g_val;
	b_v = b_val;
	//check();
}

Color Color::operator+(const Color &c) const
{
	return Color(r_v + c.r_v, g_v + c.g_v, b_v + c.b_v);
}

Color Color::operator*(const Color &c) const
{
	return Color(r_v * c.r_v, g_v * c.g_v, b_v * c.b_v);
}

Color Color::operator*(const double d) const
{
	return Color(r_v * d, g_v * d, b_v * d);
}

void Color::check()
{
	if(r_v < 0) r_v = 0;
	if(r_v > 255) r_v = 255;
	if(g_v < 0) g_v = 0;
	if(g_v > 255) g_v = 255;
	if(b_v < 0) b_v = 0;
	if(b_v > 255) b_v = 255;
}