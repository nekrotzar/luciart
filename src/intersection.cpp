#include "intersection.h"

Intersection::Intersection(){
    hit_status = false;
    hitpoint = Vec3();
    normal = Vec3();
    ray = Ray();
    t = 0;
}

Intersection::Intersection(const Intersection& i){
    hit_status = i.hit_status;
    hitpoint = i.hitpoint;
    normal = i.hitpoint;
    ray = i.ray;
    t = i.t;
    material = i.material;
}
