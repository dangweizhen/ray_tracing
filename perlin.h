#ifndef PERLIN_H
#define PERLIN_H
#include "basic.h"
class Perlin
{
public:
    Perlin();
    ~Perlin()
    {
        delete[] rand_num;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }
    double get_noise(Vec3d& v, double scale = 25.0);
    double get_turb(Vec3d& v, double scale = 25.0, int depth = 5);
private:
    static const int point_count = 256;
    Vec3d* rand_num;
    int* perm_x;
    int* perm_y;
    int* perm_z;

};

#endif