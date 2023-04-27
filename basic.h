#ifndef BASIC
#define BASIC

#include <iostream>

using namespace std;

const double EPS = 0.000001;
const double MAX_VALUE = 9999999999;
const double MIN_VALUE = -9999999999;

class Vec3d
{
public:
	double x(){return x_v;}
	double y(){return y_v;}
	double z(){return z_v;}
	void x(double x_val){x_v = x_val;}
	void y(double y_val){y_v = y_val;}
	void z(double z_val){z_v = z_val;}
	Vec3d():x_v(0),y_v(0),z_v(0){}
	Vec3d(double x_val, double y_val, double z_val):x_v(x_val),y_v(y_val),z_v(z_val){}
	Vec3d(const Vec3d &v)
	{
		x_v = v.x_v;
		y_v = v.y_v;
		z_v = v.z_v;
	}
	void print() const
	{
		cout << "(" << x_v << "," << y_v << "," << z_v << ")" << endl;
	}
	Vec3d operator+(const Vec3d &v) const;
	Vec3d operator-(const Vec3d &v) const;
	Vec3d operator*(const double d) const;
	void norm();
	~Vec3d(){}
private:
	double x_v;
	double y_v;
	double z_v;
};

double dot(Vec3d v1, Vec3d v2);

class Color
{
public:
	double r(){return r_v;}
	double g(){return g_v;}
	double b(){return b_v;}
	void r(double r_val){r_v = r_val;}
	void g(double g_val){g_v = g_val;}
	void b(double b_val){b_v = b_val;}
	Color():r_v(0),g_v(0),b_v(0){}
	Color(double r_val, double g_val, double b_val);
	void check();
	void print() const
	{
		cout << "(" << r_v << "," << g_v << "," << b_v << ")" << endl;
	}
	Color operator+(const Color &c) const;
	Color operator*(const Color &c) const;
	Color operator*(const double d) const;
private:
	double r_v;
	double g_v;
	double b_v;
};

#endif