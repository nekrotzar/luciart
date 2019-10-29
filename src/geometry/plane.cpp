#ifdef __APPLE__
    #include "plane.h"
#else
    #include "geometry/plane.h"
#endif

Plane::Plane(){
    p1 = Vec3();
    p2 = Vec3();
    p3 = Vec3();
    normal = ((p2 - p1).cross(p3 - p1)).normalise();
    material = Material();
}

Plane::Plane(const Vec3 &a, const Vec3 &b, const Vec3 &c){
    p1 = a;
    p2 = b;
    p3 = c;
    normal = ((p2 - p1).cross(p3 - p1)).normalise();
    material = Material();
}

Plane::Plane(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Material &m){
    p1 = a;
    p2 = b;
    p3 = c;
    normal = ((p2 - p1).cross(p3 - p1)).normalise();
    material = m;
}

void Plane::compute_bounding_box(){}

bool Plane::intersect(const Ray& ray, double& tmin, Intersection& intersection){
    double denom = normal.dot(ray.direction);
    
    // The plane and ray do not intersect(parallel) if the dot product is zero.
    if (abs(denom) > 0) {
        double t = (p1 - ray.position).dot(normal) / denom;
        
        // Check if intersection is behind the origin of the ray
        if (t > 0) {
            tmin = t;
            intersection.normal = normal;
            return true;
        }
    }
    return false;
}



