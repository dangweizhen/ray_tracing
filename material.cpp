#include "material.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
//using namespace std;

Color Material::absorb(Color dif_c, Vec3d collide_point)
{
	if(texture != NULL)
		return texture->get_color(collide_point) * dif_c * (1.0/256);
	return Color(0,0,0);
}

Ray Diffuse::process_ray(Ray r, Vec3d collide_point, Vec3d normal)
{
	Vec3d center = collide_point + normal;
	Vec3d dir(double(rand()) / RAND_MAX - 0.5, double(rand()) / RAND_MAX - 0.5, double(rand()) / RAND_MAX - 0.5);
	dir.norm();
	Vec3d select_p = center + dir;
	return Ray(collide_point, select_p - collide_point);
	
}

Ray Reflect::process_ray(Ray r, Vec3d collide_point, Vec3d normal)
{
	Vec3d reflect_dir = r.direction() + normal * (-2 * dot(normal, r.direction()));
	if(diffuse > 0)
	{
		Vec3d dir(double(rand()) / RAND_MAX - 0.5, double(rand()) / RAND_MAX - 0.5, double(rand()) / RAND_MAX - 0.5);
		dir = dir * diffuse;
		reflect_dir = reflect_dir + dir;
		if(dot(normal, reflect_dir) <= 0) return Ray(collide_point, Vec3d(0,0,0));
	}
	return Ray(collide_point, reflect_dir);
	/*
	Vec3d center = collide_point + normal;
	Vec3d dir(double(rand()) / RAND_MAX - 0.5, double(rand()) / RAND_MAX - 0.5, double(rand()) / RAND_MAX - 0.5);
	dir.norm();
	Vec3d select_p = center + dir;
	return Ray(collide_point, select_p - collide_point);
	*/
	
}

Ray Refract::process_ray(Ray r, Vec3d collide_point, Vec3d normal)
{
	double in_n = 1;
	double out_n = ind;
	//check if ray is shoot from object
	double cos_n = dot(r.direction(), normal);
	if(cos_n >= 0)
	{
		in_n = ind;
		out_n = 1;
		normal = normal * -1;
		cos_n = -cos_n;
	}
	//check if full reflect
	bool full_ref = false;
	double square_sin_n_ = (1-cos_n * cos_n) * in_n * in_n / (out_n * out_n);
	if(square_sin_n_ >= 1.0 + EPS) full_ref = true;
	//std::cout << full_ref << endl;
	double random_num = double(rand()) / RAND_MAX;
	//if(full_ref) std::cout << "FULL_REF" << endl;
	if(!full_ref && random_num < pos)
	{
		//refract
		Vec3d refract_dir = (r.direction() - normal * cos_n) * (in_n / out_n) + normal * (-1 * sqrt(1-square_sin_n_));
		refract_dir.norm();
		//Vec3d tmp = refract_dir + r.direction() * -1;
		//std::cout << cos_n << " " << sqrt(1-square_sin_n_) << endl;
		//tmp.print();
		return Ray(collide_point + refract_dir, refract_dir);
	}
	//reflect
	Vec3d reflect_dir = r.direction() + normal * (-2 * dot(normal, r.direction()));
	return Ray(collide_point, reflect_dir);
	
	
	
}


