#ifndef TEXTURE
#define TEXTURE
#include "basic.h"


class Texture
{
public:
	virtual Color get_color(Vec3d p) = 0; 
};

class Constant_Texure: public Texture
{
public:
	Constant_Texure(Color co):c(co){}
	virtual Color get_color(Vec3d p){return c;}
private:
	Color c;
};

class Check_Texture: public Texture
{
public:
	Check_Texture(Texture* te1, Texture* te2):t1(te1), t2(te2){}
	virtual Color get_color(Vec3d p);
private:
	Texture* t1;
	Texture* t2;
};

#endif
