#ifndef TREE_NODE_H_
#define TREE_NODE_H_

#include "primitives.h"
#include "hitbox.h"

class Tree_node
{
public:
    Tree_node(int start = 0, int end = 0):left(NULL), right(NULL), st(start), ed(end){}
    ~Tree_node()
    {
        if(left) delete left;
        if(right) delete right;
    }
    void set_hitbox(Vec3d v1, Vec3d v2)
    {
        hb.set_bond(v1, v2);
    }
    Hitbox hb;
    Tree_node* left;
    Tree_node* right;
    int st;
    int ed;
    void print()
    {
        std::cout << '(' << st << ',' << ed << ')' << std::endl;
        if(left) left->print();
        if(right) right->print();
    }
private:
    
};



#endif