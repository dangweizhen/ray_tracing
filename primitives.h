#ifndef PRIMITIVE
#define PRIMITIVE
#include "basic.h"
#include "ray.h"
#include "material.h"
class Primitive
{
public:
	Primitive(){}
	virtual double collide(Ray) = 0;
	virtual Ray nextRay(Ray, Vec3d) = 0;
	virtual Vec3d getNorm(Vec3d) = 0;
	virtual Color absorb(Color) = 0;
	void setMaterial(Material* ma){m = ma;}
protected:
	Material* m;
};

class Sphere:public Primitive
{
public:
	virtual double collide(Ray);
	virtual Ray nextRay(Ray, Vec3d);
	virtual Vec3d getNorm(Vec3d);
	virtual Color absorb(Color);
	Sphere(Vec3d v, double radius):o(v), d(radius){}
private:
	Vec3d o;
	double d;
};

#endif