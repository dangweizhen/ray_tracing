#ifndef PRIMITIVE
#define PRIMITIVE
#include "basic.h"
#include "ray.h"
#include "material.h"
#include "hitbox.h"
class Primitive
{
public:
	Primitive(){}
	virtual double collide(Ray) = 0;
	virtual Ray nextRay(Ray, Vec3d) = 0;
	virtual Vec3d getNorm(Vec3d) = 0;
	virtual double get_max_x() = 0;
	virtual double get_max_y() = 0;
	virtual double get_max_z() = 0;
	virtual double get_min_x() = 0;
	virtual double get_min_y() = 0;
	virtual double get_min_z() = 0;
	Color absorb(Color c, Vec3d collide_point){return m->absorb(c, collide_point);}
	void setMaterial(Material* ma){m = ma;}
protected:
	Material* m;
	Hitbox hb;
};



class Sphere:public Primitive
{
public:
	virtual double collide(Ray);
	virtual Ray nextRay(Ray, Vec3d);
	virtual Vec3d getNorm(Vec3d);
	virtual double get_max_x(){return hb.get_max_x();}
	virtual double get_max_y(){return hb.get_max_y();}
	virtual double get_max_z(){return hb.get_max_z();}
	virtual double get_min_x(){return hb.get_min_x();}
	virtual double get_min_y(){return hb.get_min_y();}
	virtual double get_min_z(){return hb.get_min_z();}
	//virtual Color absorb(Color, Vec3d);
	Sphere(Vec3d v, double radius):o(v), d(radius)
	{
		hb.set_bond(v + Vec3d(radius, radius, radius), v - Vec3d(radius, radius, radius));
	}
private:
	Vec3d o;
	double d;
};




#endif