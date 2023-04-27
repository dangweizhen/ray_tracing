#include <vector>
#include "primitives.h"
#include "ray.h"
#include "tree_node.h"
class Primitive_list
{
public:
    void insert(Primitive *);
    bool collide(Ray&, int& , double& );
    bool collide_adv(Ray&, int& , double& );
    Primitive* get(int n);
    int p_num() {return plist.size();}
    void build();
    void print()
    {
        t->print();
    }
    int len(){return plist.size();};
private:
    std::vector<Primitive*> plist;
    Tree_node* t;
    void build(int,int,Tree_node*&);
    bool collide_advance(Ray&, int& , double& , Tree_node*);
};