#include "world.h"
#include "ray.h"
#include "basic.h"
#include <cstdlib>
#include <iostream>

Color BACKGROUND(255,255,255);
int MAXP = 512;
int DEFAULT_ANTI = 250;
int MAX_DEPTH = 5;
/*
World::World(int x, int y)
{
	X = x;
	Y = y;
	canvas = new Color*[Y];
	for(int i = 0;i < Y;i ++)
	{
		canvas[i] = new Color[X];
	}
	camera = Vec3d(0,0,-100);
	plist = new Primitive*[MAXP];
	pnum = 0;
	antialiasing = DEFAULT_ANTI;
}
*/

World::World(int x, int y, double l, Vec3d p, Vec3d d, int len_d):cam(x, y, l, p, d, len_d)
{
	X = x;
	Y = y;
	L = l;
	//camera = p;
	canvas = new Color*[y];
	for(int i = 0;i < y;i ++)
	{
		canvas[i] = new Color[x];
	}
	plist = new Primitive*[MAXP];
	pnum = 0;
	antialiasing = DEFAULT_ANTI;
}

World::~World()
{
	for(int i = 0;i < Y;i ++)
	{
		delete[] canvas[i];
	}
	delete[] canvas;
	delete[] plist;
}

bool World::insert(Primitive* p)
{
	if(pnum >= MAXP)
	{
		return false;
	}
	plist[pnum] = p;
	pnum ++;
	return true;
}

void World::render()
{
	std::cout << "rendering..." << std::endl;
	int total_p = X * Y;
	int percent_p = total_p / 100;
	int cur = 0;
	if(plist == NULL) return;
	for(int i = 0;i < Y;i ++)
		for(int j = 0;j < X;j ++)
		{
			Color res(0,0,0);
			for(int k = 0; k < antialiasing;k ++)
			{
				/*
				double delta_x = (rand() - RAND_MAX / 2.0) / double(RAND_MAX);
				double delta_y = (rand() - RAND_MAX / 2.0) / double(RAND_MAX);
				Ray r(camera, Vec3d(i-Y/2.0+delta_y, X/2.0-j+delta_x, 0) - camera);
				*/
				Ray r = cam.get_ray(j, i);
				res = res + ray_tracing(r);
			}
			canvas[i][j] = res * (1.0/antialiasing);
			canvas[i][j].check();
			if((i * X + j) % percent_p == 0)
			{
				std::cout << "rendering " << (i * X + j) / percent_p << " percent..." << std::endl;
			}
		}
}

Color World::ray_tracing(Ray r, int depth)
{
	if(depth > MAX_DEPTH) return Color(0,0,0);
	int collide_num = -1;
	double collide_length = -1;
	for(int k = 0; k < pnum;k ++)
	{
		double l = plist[k]->collide(r);
		if(l >= EPS && (collide_length < 0 || l < collide_length))
		{
			collide_num = k;
			collide_length = l;
		}
	}
	//std::cout << collide_num << endl;
	if(collide_num >= 0) 
	{
		Vec3d collide_point = r.point() + r.direction() * collide_length;
		Ray next_ray = plist[collide_num]->nextRay(r, collide_point);
		if(!next_ray.is_ray()) return Color(0,0,0);
		Color in_Color = ray_tracing(next_ray, depth + 1);
		return plist[collide_num]->absorb(in_Color);
		/*
		Color c = plist[collide_num]->getColor();
		//diffuse
		Vec3d normal = plist[collide_num]->getNorm(collide_point);
		Vec3d center = collide_point + normal;
		Vec3d dir(double(rand()) / RAND_MAX - 0.5, double(rand()) / RAND_MAX - 0.5, double(rand()) / RAND_MAX - 0.5);
		dir.norm();
		Vec3d select_p = center + dir;
		Color dif_c = ray_tracing(Ray(collide_point, select_p - collide_point), depth + 1);
		return c * dif_c * (1.0/256);
		*/
		//
	}
	return BACKGROUND;
}

