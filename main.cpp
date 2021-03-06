#include <iostream>
#include "basic.h"
#include "ray.h"
#include "world.h"
#include "material.h"
#include "primitives.h"
#include "camera.h"
#include "texture.h"
#include <fstream>
#include <cstdlib>


using namespace std;

int X = 1440;
int Y = 1080;
double L = 1500;
double F = 20;
int main()
{
	srand(0);
	World w(X, Y, L, Vec3d(200, -200, L), Vec3d(-200,200,-L), F);
	//
	Sphere* s1 = new Sphere(Vec3d(0,0,0), 80);
	//s1->setColor(Color(255,191,0));
	Constant_Texure* t1 = new Constant_Texure(Color(255,191,0));
	s1->setMaterial(new Diffuse(t1));
	w.insert(s1);

	Sphere* s2 = new Sphere(Vec3d(160,0,0), 80);
	//s2->setColor(Color(0,191,255));
	Constant_Texure* t2 = new Constant_Texure(Color(240,240,240));
	s2->setMaterial(new Refract(t2, 1.5, 0.99));
	w.insert(s2);

	Sphere* s3 = new Sphere(Vec3d(-160,0,0), 80);
	Constant_Texure* t3 = new Constant_Texure(Color(225,225,225));
	s3->setMaterial(new Reflect(t3, -0.2));
	//s3->setColor(Color(0,255,191));
	w.insert(s3);

	Sphere* s6 = new Sphere(Vec3d(-280,40,0), 40);
	Constant_Texure* t6 = new Constant_Texure(Color(0,255,191));
	s6->setMaterial(new Diffuse(t6));
	//s3->setColor(Color(0,255,191));
	w.insert(s6);

	Sphere* s7 = new Sphere(Vec3d(-40,40,200), 40);
	Constant_Texure* t7 = new Constant_Texure(Color(225,225,225));
	s7->setMaterial(new Reflect(t7, 0.05));
	//s3->setColor(Color(0,255,191));
	w.insert(s7);

	Sphere* s4 = new Sphere(Vec3d(-150,-40,-300), 120);
	Constant_Texure* t4 = new Constant_Texure(Color(225,0,191));
	s4->setMaterial(new Diffuse(t4));
	//s3->setColor(Color(0,255,191));
	w.insert(s4);

	//
	Sphere* s5 = new Sphere(Vec3d(0, 100000, 0), 99920);
	Constant_Texure* t5_1 = new Constant_Texure(Color(255,255,255));
	Constant_Texure* t5_2 = new Constant_Texure(Color(0,0,0));
	Check_Texture* t5 = new Check_Texture(t5_1, t5_2);
	s5->setMaterial(new Diffuse(t5));
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

