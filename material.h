#ifndef MATERIAL
#define MATERIAL

#include "ray.h"
#include "basic.h"

class Material
{
public:
	virtual Ray process_ray(Ray, Vec3d, Vec3d) = 0;
	virtual Color absorb(Color) = 0;
	bool can_through() {return through;}
	void set_through(bool b){through = b;}
private:
	bool through;
};

class Diffuse: public Material
{
public:
	Diffuse(Color c):orgin_color(c){set_through(false);}
	virtual Ray process_ray(Ray, Vec3d, Vec3d);
	virtual Color absorb(Color);
private:
	Color orgin_color;
};

class Reflect: public Material
{
public:
	Reflect(Color c, double d = -1):orgin_color(c), diffuse(d){set_through(false);}
	virtual Ray process_ray(Ray, Vec3d, Vec3d);
	virtual Color absorb(Color);
private:
	double diffuse;
	Color orgin_color;
};


class Refract: public Material
{
public:
	Refract(Color c, double i = 1, double p = 1):orgin_color(c), ind(i), pos(p){set_through(true);}
	virtual Ray process_ray(Ray, Vec3d, Vec3d);
	virtual Color absorb(Color);
private:
	double ind; //refractive indices
	double pos; //possibility of refraction
	Color orgin_color;
};

#endif