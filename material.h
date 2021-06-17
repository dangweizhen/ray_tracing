#ifndef MATERIAL
#define MATERIAL

#include "ray.h"
#include "basic.h"
#include "texture.h"

class Material
{
public:
	Material():texture(NULL){}
	Material(Texture* t):texture(t){}
	virtual Ray process_ray(Ray, Vec3d, Vec3d) = 0;
	Color absorb(Color, Vec3d);
	bool can_through() {return through;}
	bool is_light() {return light;}
	void set_through(bool b){through = b;}
	void set_light(bool b){light = b;}
	Texture* get_texture(){return texture;}
private:
	Texture* texture;
	bool through;
	bool light;
};

class Diffuse: public Material
{
public:
	Diffuse(Texture* t):Material(t){set_through(false);set_light(false);}
	virtual Ray process_ray(Ray, Vec3d, Vec3d);
	//virtual Color absorb(Color);
private:
	//Color orgin_color;
};

class Reflect: public Material
{
public:
	Reflect(Texture* t, double d = -1):Material(t), diffuse(d){set_through(false);set_light(false);}
	virtual Ray process_ray(Ray, Vec3d, Vec3d);
	//virtual Color absorb(Color);
private:
	double diffuse;
	//Color orgin_color;
};


class Refract: public Material
{
public:
	Refract(Texture* t, double i = 1, double p = 1):Material(t), ind(i), pos(p){set_through(true);set_light(false);}
	virtual Ray process_ray(Ray, Vec3d, Vec3d);
	//virtual Color absorb(Color);
private:
	double ind; //refractive indices
	double pos; //possibility of refraction
	//Color orgin_color;
};

#endif