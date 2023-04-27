#include "perlin.h"
#include <cstdlib>
#include <cmath>

Perlin::Perlin()
{
    rand_num = new Vec3d[point_count];
    for(int i = 0;i < point_count;i ++)
    {
        double x = (1.0*rand()) / RAND_MAX - 0.5;
        double y = (1.0*rand()) / RAND_MAX - 0.5;
        double z = (1.0*rand()) / RAND_MAX - 0.5;
        rand_num[i] = Vec3d(x, y, z);
        rand_num[i].norm();
    }

    perm_x = new int[point_count];
    perm_y = new int[point_count];
    perm_z = new int[point_count];

    for(int i = 0;i < point_count;i ++)
    {
        perm_x[i] = i;
        perm_y[i] = i;
        perm_z[i] = i;
    }
    int tmp = 0;
    for(int i = point_count - 1;i > 0;i --)
    {
        int k_x = rand() % i;
        tmp = perm_x[k_x];
        perm_x[k_x] = perm_x[i];
        perm_x[i] = tmp;

        int k_y = rand() % i;
        tmp = perm_y[k_y];
        perm_y[k_y] = perm_y[i];
        perm_y[i] = tmp;

        int k_z = rand() % i;
        tmp = perm_z[k_z];
        perm_z[k_z] = perm_z[i];
        perm_z[i] = tmp;
    }

}

double Perlin::get_noise(Vec3d& p, double scale)
{
    /*
    int i = int(p.x() / 25) & 255;
    int j = int(p.y() / 25) & 255;
    int k = int(p.z() / 25) & 255;
    return rand_num[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
    */
    double x_calc = p.x() / scale;
    double y_calc = p.y() / scale;
    double z_calc = p.z() / scale;
    int x_int = int(x_calc);
    int y_int = int(y_calc);
    int z_int = int(z_calc);
    double x_frac = x_calc - floor(x_calc);
    x_frac = x_frac * x_frac * (3-2*x_frac);
    double y_frac = y_calc - floor(y_calc);
    y_frac = y_frac * y_frac * (3-2*y_frac);
    double z_frac = z_calc - floor(z_calc);
    z_frac = z_frac * z_frac * (3-2*z_frac);

    //double c[2][2][2];

    double res = 0;
    for(int i = 0;i < 2;i ++)
        for(int j = 0;j < 2;j ++)
            for(int k = 0;k < 2;k ++)
            {
                int x = perm_x[(x_int+i) & 255];
                int y = perm_y[(y_int+j) & 255];
                int z = perm_z[(z_int+k) & 255];
                //c[i][j][k] = rand_num[x^y^z];
                double weight = (i * x_frac + (1-i) * (1-x_frac)) * 
                                (j * y_frac + (1-j) * (1-y_frac)) * 
                                (k * z_frac + (1-k) * (1-z_frac));
                res += dot(rand_num[x^y^z], Vec3d(x_frac-i, y_frac-j, z_frac-k)) * weight;
            }

    return res;

}

double Perlin::get_turb(Vec3d& p, double scale, int depth)
{
    double accum = 0;
    Vec3d tmp_p = p;
    double weight = 1.0;
    for(int i = 0;i < depth; i ++)
    {
        accum += weight * get_noise(tmp_p, scale);
        weight *= 0.5;
        tmp_p = tmp_p * 2.0;
    }
    return fabs(accum);
}