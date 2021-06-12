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
int L = 500;
int main()
{
	srand(0);
	World w(X, Y, L+500, Vec3d(0,0,-L));
	//
	Sphere* s1 = new Sphere(Vec3d(0,0,0), 100);
	//s1->setColor(Color(255,191,0));
	s1->setMaterial(new Diffuse(Color(255,191,0)));
	w.insert(s1);

	Sphere* s2 = new Sphere(Vec3d(0,-200,0), -100);
	//s2->setColor(Color(0,191,255));
	s2->setMaterial(new Refract(Color(240,240,240), 1.5, 0.99));
	w.insert(s2);

	Sphere* s3 = new Sphere(Vec3d(0,200,0), 100);
	s3->setMaterial(new Reflect(Color(225,225,225), -0.2));
	//s3->setColor(Color(0,255,191));
	w.insert(s3);

	Sphere* s4 = new Sphere(Vec3d(-50,-150,300), 150);
	s4->setMaterial(new Diffuse(Color(225,0,191)));
	//s3->setColor(Color(0,255,191));
	w.insert(s4);

	//
	Sphere* s5 = new Sphere(Vec3d(100000,0,0), 99900);
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

