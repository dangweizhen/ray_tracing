#include "texture.h"
#include <cmath>
Color Check_Texture::get_color(Vec3d p)
{
	float sines = sin(0.08 * p.x()) * sin(0.08 * p.y()) * sin(0.08 * p.z());
	if(sines < 0) return t1->get_color(p);
	else return t2->get_color(p);
}