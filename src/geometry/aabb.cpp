#include "aabb.h"

AABB::AABB(){
    xmin = -1.0;
    xmax = 1.0;
    ymin = -1.0;
    ymax = 1.0;
    zmin = -1.0;
    zmax = 1.0;
}

AABB::AABB(double x0, double x1, double y0, double y1, double z0, double z1){
    xmin = x0;
    xmax = x1;
    ymin = y0;
    ymax = y1;
    zmin = z0;
    zmax = z1;
}

AABB::AABB(const Vec3 p0, const Vec3 p1){
    xmin = p0.x;
    xmax = p1.x;
    ymin = p0.y;
    ymax = p1.y;
    zmin = p0.z;
    zmax = p1.z;
}

bool AABB::intersect(const Ray &ray, double &t0, double &t1, Vec3 &tmin, Vec3 &tmax){

    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;
        
    double a = 1.0 / ray.direction.x;
    if (a >= 0) {
        tx_min = (xmin - ray.position.x) * a;
        tx_max = (xmax - ray.position.x) * a;
    } else {
        tx_min = (xmax - ray.position.x) * a;
        tx_max = (xmin - ray.position.x) * a;
    }
    
    double b = 1.0 / ray.direction.y;
    if (b >= 0) {
        ty_min = (ymin - ray.position.y) * b;
        ty_max = (ymax - ray.position.y) * b;
    } else {
        ty_min = (ymax - ray.position.y) * b;
        ty_max = (ymin - ray.position.y) * b;
    }
    
    double c = 1.0 / ray.direction.z;
    if (c >= 0) {
        tz_min = (zmin - ray.position.z) * c;
        tz_max = (zmax - ray.position.z) * c;
    } else {
        tz_min = (zmax - ray.position.z) * c;
        tz_max = (zmin - ray.position.z) * c;
    }
    
    // Find largest entering t value
    if(tx_min > ty_min)
        t0 = tx_min;
    else
        t0 = ty_min;
    if(tz_min > t0)
        t0 = tz_min;
    
    // Find smallest exiting t value
    if(tx_max < ty_max)
        t1 = tx_max;
    else
        t1 = ty_max;
    if(tz_max < t1)
        t1 = tz_max;
    
    
    // Store values of t.
    tmin = Vec3(tx_min, ty_min, tz_min);
    tmax = Vec3(tx_max, ty_max, tz_max);
    
    return (t0 < t1 && t1 > EPSILON);

}

bool AABB::inside(const Vec3 &p){
    return  (p.x > xmin && p.x < xmax) &&
            (p.y > ymin && p.y < ymax) &&
            (p.z > zmin && p.z < zmax);
}

void AABB::set_bounding_box(const Vec3 &min, const Vec3 &max){
    xmin = min.x;
    ymin = min.y;
    zmin = min.z;
    xmax = max.x;
    ymax = max.y;
    zmax = max.z;
}

