#include "texture.h"
#include <cmath>
Color Check_Texture::get_color(Vec3d p)
{
	float sines = sin(0.08 * p.x()) * sin(0.08 * p.y()) * sin(0.08 * p.z());
	if(sines < 0) return t1->get_color(p);
	else return t2->get_color(p);
}


Color Perlin_Texture::get_color(Vec3d p)
{
	//return Color(255, 255, 255) * ((1 + perlin.get_noise(p)) * 0.5);
	// return Color(255, 255, 255) * perlin.get_turb(p);
	return Color(255, 255, 255) * (1 + sin(p.z() / scale + 10 * perlin.get_turb(p, scale))) * 0.5;
}
