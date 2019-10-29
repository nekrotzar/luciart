#ifdef __APPLE__
    #include "sphere.h"
#else
    #include "geometry/sphere.h"
#endif

Sphere::Sphere(){
    center = Vec3();
    radius = 1.0;
    material = Material();
    compute_bounding_box();
}

Sphere::Sphere(const Vec3 &c, float r){
    center = c;
    radius = r;
    material = Material();
    compute_bounding_box();
}

Sphere::Sphere(const Vec3 &c, float r, const Material &m){
    center = c;
    radius = r;
    material = m;
    compute_bounding_box();
}

void Sphere::compute_bounding_box(){
    Vec3 pmin = (center - radius);
    Vec3 pmax = (center + radius);
    
    boundingBox.set_bounding_box(pmin, pmax );
}

bool Sphere::intersect(const Ray &ray, double& tmin ,Intersection &intersection){
    
    // Calculate intersection if it is in cache
    if (mailBox.ray_id == ray.rayID) {

        if(mailBox.t < 0)
            return false;
        
        tmin = mailBox.t;
        intersection.hitpoint = ray.position + (ray.direction * mailBox.t);
        intersection.normal = (intersection.hitpoint - center) / radius;
        return true;
    }
    
    // Store new ray in the mailbox
    mailBox.ray_id = ray.rayID;
    mailBox.t = -1;
    
    
    double t = 0.0;
    Vec3 hitpoint;
    Vec3 l = center - ray.position;

    double d = l.dot(l);
    double r2 = radius * radius;
    double b = l.dot(ray.direction);
    
    if (d == r2) {
        return false;
    }
    
    if (d > r2) {
        if(b < 0)
            return false;
    }
    
    double r = b * b - d + r2;
    if (r < 0) {
        return false;
    }
    
    double resq = sqrt(r);
    if (d > r2) {
        t = b - resq;
    } else if (d < r2){
        t = b + resq;
    }
    
    // Store t value in case of intersection.
    mailBox.t = t;
   
    hitpoint = ray.position + ray.direction * t;
    tmin = t;
    intersection.normal = (hitpoint - center) / radius;
    
    return true;
}
