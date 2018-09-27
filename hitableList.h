#ifndef _HITABLELIST_H_
#define _HITABLELIST_H_
#include "hitable.h"
class hitableList : public hitable
{
  public:
    hitable **list;
    int list_size;
    hitableList(){};
    hitableList(hitable **l, int n)
    {
        list = l;
        list_size = n;
    };
    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const
    {
        bool hitAnything = false;
        double closest_so_far = t_max; //当前射线最近距离
        for (int i = 0; i < list_size; i++)
        {
            if (list[i]->hit(r, t_min, closest_so_far, rec))
            {
                hitAnything = true;
                closest_so_far = rec.t;
            }
        }
        return hitAnything;
    };
};
#endif
