#ifndef WORLD
#define WORLD
#include "basic.h"
#include "primitives.h"
#include "camera.h"

class World
{
public:
	//World():X(0),Y(0){}
	//World(int x, int y, int l);
	World(int x, int y, int l, Vec3d v);
	~World();
	void render();
	Color color(int x, int y){return canvas[x][y];}
	bool insert(Primitive*);
private:
	int X;
	int Y;
	int L;
	//Vec3d camera;
	Color** canvas;
	Primitive** plist;
	int pnum;
	Color ray_tracing(Ray r, int depth = 0);
	int antialiasing;
	Camera cam;
};

#endif