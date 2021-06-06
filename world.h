#ifndef WORLD
#define WORLD
#include "basic.h"
#include "primitives.h"


class World
{
public:
	World():X(0),Y(0){}
	World(int x, int y);
	World(int x, int y, Vec3d v);
	~World();
	void render();
	Color color(int x, int y){return canvas[x][y];}
	bool insert(Primitive*);
private:
	int X;
	int Y;
	Vec3d camera;
	Color** canvas;
	Primitive** plist;
	int pnum;
	Color ray_tracing(Ray r, int depth = 0);
	int antialiasing;
};

#endif