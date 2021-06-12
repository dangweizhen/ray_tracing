#include <iostream>
#include "basic.h"
#include "ray.h"
#include "world.h"
#include "material.h"
#include "primitives.h"
#include "camera.h"
#include <fstream>
#include <cstdlib>


using namespace std;

int X = 960;
int Y = 720;
double L = 1500;
double F = 50;
int main()
{
	srand(0);
	World w(X, Y, L, Vec3d(0, 0, L), Vec3d(0,0,-1), F);
	//
	Sphere* s1 = new Sphere(Vec3d(0,0,0), 80);
	//s1->setColor(Color(255,191,0));
	s1->setMaterial(new Diffuse(Color(255,191,0)));
	w.insert(s1);

	Sphere* s2 = new Sphere(Vec3d(160,0,0), 80);
	//s2->setColor(Color(0,191,255));
	s2->setMaterial(new Refract(Color(240,240,240), 1.5, 0.99));
	w.insert(s2);

	Sphere* s3 = new Sphere(Vec3d(-160,0,0), 80);
	s3->setMaterial(new Reflect(Color(225,225,225), -0.2));
	//s3->setColor(Color(0,255,191));
	w.insert(s3);

	Sphere* s6 = new Sphere(Vec3d(-280,40,0), 40);
	s6->setMaterial(new Diffuse(Color(0,255,191)));
	//s3->setColor(Color(0,255,191));
	w.insert(s6);

	Sphere* s7 = new Sphere(Vec3d(-40,40,200), 40);
	s7->setMaterial(new Reflect(Color(225,225,225), 0.05));
	//s3->setColor(Color(0,255,191));
	w.insert(s7);

	Sphere* s4 = new Sphere(Vec3d(-150,-40,-300), 120);
	s4->setMaterial(new Diffuse(Color(225,0,191)));
	//s3->setColor(Color(0,255,191));
	w.insert(s4);

	//
	Sphere* s5 = new Sphere(Vec3d(0, 100000, 0), 99920);
	s5->setMaterial(new Diffuse(Color(191,255,0)));
	//s4->setColor(Color(191,255,0));
	w.insert(s5);

	w.render();
	ofstream o("pic.ppm");
	if(o.fail())  
	{
		cout << "Fail to open file..." << endl;
		return 0;
	}
	o << "P3\n" << X << " " << Y << "\n255\n";
	for(int i = 0;i < Y;i ++)
		for(int j = 0; j < X;j ++)
		{
			Color c = w.color(i,j);
			o << int(c.r()) << " " << int(c.g()) << " " << int(c.b()) << "\n";
		}
	return 0;
}

