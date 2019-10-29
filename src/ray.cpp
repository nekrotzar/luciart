#include "ray.h"

unsigned long Ray::increment = 0;

Ray::Ray(){
    position = Vec3(0,0,0);
    direction = Vec3(0,0,1);
    rayID = Ray::increment++;
}

Ray::Ray(const Vec3& p, const Vec3& d){
    position = p;
    direction = d;
    rayID = Ray::increment++;
}
