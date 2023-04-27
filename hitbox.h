#ifndef _HITBOX_H_
#define _HITBOX_H_
#include "ray.h"
#include "basic.h"


class Hitbox
{
public:
	bool collide(Ray&);
	Hitbox(){}
	void set_bond(Vec3d, Vec3d);
    double get_max_x(){return max(x1, x2);}
    double get_min_x(){return min(x1, x2);}
    double get_max_y(){return max(y1, y2);}
    double get_min_y(){return min(y1, y2);}
    double get_max_z(){return max(z1, z2);}
    double get_min_z(){return min(z1, z2);}
private:
	double x1, x2;
	double y1, y2;
	double z1, z2;
};

#endif