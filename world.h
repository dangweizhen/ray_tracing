#ifndef WORLD
#define WORLD
#include "basic.h"
#include "primitives.h"
#include "camera.h"
#include "primitive_list.h"

class World
{
public:
	//World():X(0),Y(0){}
	//World(int x, int y, int l);
	World(int x, int y, double l, Vec3d v, Vec3d d, int lens_d);
	~World();
	void render();
	Color color(int x, int y){return canvas[x][y];}
	bool insert(Primitive*);
	int primitive_num(){return plist.len();}
private:
	int X;
	int Y;
	double L;
	//Vec3d camera;
	Color** canvas;
	// Primitive** plist;
	// int pnum;
	Color ray_tracing(Ray r, int depth = 0);
	int antialiasing;
	Camera cam;
	Primitive_list plist;
};

#endif