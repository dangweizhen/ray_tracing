#include "primitive_list.h"
#include <algorithm>

bool cmp_x(Primitive* p1, Primitive* p2)
{
    return p1->get_min_x() < p2->get_min_x();
}

bool cmp_y(Primitive* p1, Primitive* p2)
{
    return p1->get_min_y() < p2->get_min_y();
}

bool cmp_z(Primitive* p1, Primitive* p2)
{
    return p1->get_min_z() < p2->get_min_z();
}

bool Primitive_list::collide(Ray& r, int& collide_num, double& collide_length)
{
    collide_num = -1;
    collide_length = -1;
    for(int i = 0;i < plist.size();i ++)
    {
        double l = plist[i]->collide(r);
        if(l >= EPS && (collide_length < 0 || l < collide_length))
        {
            collide_num = i;
			collide_length = l;
        }
    }
    return collide_num >= 0;
}

void Primitive_list::insert(Primitive * p)
{
    plist.push_back(p);
}

Primitive* Primitive_list::get(int n)
{
    return plist[n];
}

void Primitive_list::build()
{
    int st = 0;
    int ed = plist.size();
    build(st,ed,t);
}

void Primitive_list::build(int st, int ed, Tree_node*& p)
{
    if(st >= ed)
    {
        p = NULL;
        return;
    }
    p = new Tree_node(st, ed);
    double x_max = plist[st]->get_max_x(), y_max = plist[st]->get_max_y(), z_max = plist[st]->get_max_z();
    double x_min = plist[st]->get_min_x(), y_min = plist[st]->get_min_y(), z_min = plist[st]->get_min_z();
    if(st == ed-1)
    {
        p->set_hitbox(Vec3d(x_max, y_max, z_max), Vec3d(x_min, y_min, z_min));
        return;
    }
    for(int i = st + 1;i < ed;i ++)
    {
        //build hitbox for [st, ed)
        x_max = max(x_max, plist[i]->get_max_x());
        x_min = max(x_min, plist[i]->get_min_x());

        y_max = max(y_max, plist[i]->get_max_y());
        y_min = max(y_min, plist[i]->get_min_y());

        z_max = max(z_max, plist[i]->get_max_z());
        z_min = max(z_min, plist[i]->get_min_z());
    }
    p->set_hitbox(Vec3d(x_max, y_max, z_max), Vec3d(x_min, y_min, z_min));
    // split into 2 parts
    int random_num = rand() % 3;
    if(random_num == 0) sort(plist.begin()+st, plist.begin()+ed, cmp_x);
    else if(random_num == 1) sort(plist.begin()+st, plist.begin()+ed, cmp_y);
    else sort(plist.begin()+st, plist.begin()+ed, cmp_z);
    build(st, (st+ed)/2, p->left);
    build((st+ed)/2, ed, p->right);
}

bool Primitive_list::collide_adv(Ray& r, int& collide_num, double& collide_length)
{
    int collide_n = -1;
    double collide_l = -1;
    bool res = collide_advance(r, collide_n, collide_l, t);
    collide_num = collide_n;
    collide_length = collide_l;
    return res;
}


bool Primitive_list::collide_advance(Ray& r, int& collide_num, double& collide_length, Tree_node* t)
{
    if(t == NULL) return false;
    if(t->left == NULL && t->right == NULL)
    {
        double l = plist[t->st]->collide(r);
        if(l >= EPS)
        {
            collide_num = t->st;
            collide_length = l;
            return true;
        }
        return false;
    }
    double res = false;
    if(t->left)
    {
        int c_n = -1;
        double c_l = -1;
        if(collide_advance(r, c_n, c_l, t->left))
        {
            res = true;
            if(collide_length < 0 || c_l < collide_length)
            {
                collide_num = c_n;
                collide_length = c_l;
            }
        }
    }
    if(t->right)
    {
        int c_n = -1;
        double c_l = -1;
        if(collide_advance(r, c_n, c_l, t->right))
        {
            res = true;
            if(collide_length < 0 || c_l < collide_length)
            {
                collide_num = c_n;
                collide_length = c_l;
            }
        }
    }
    return res;
}
