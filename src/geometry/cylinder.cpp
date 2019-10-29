#ifdef __APPLE__
    #include "cylinder.h"
#else
    #include "geometry/cylinder.h"
#endif

Cylinder::Cylinder(){
    base = Vec3(0.0,0.0,0.0);
    apex = Vec3(1.0,1.0,1.0);
    baseRadius = 1.0;
    apexRadius = 1e-3;
    material = Material();
}

Cylinder::Cylinder(const Vec3 &b, const Vec3 &a, float bRadius, float aRadius, const Material &m){
    base = b;
    apex = a;
    baseRadius = bRadius;
    apexRadius = aRadius;
    material = m;
}

void Cylinder::compute_bounding_box(){}

bool Cylinder::intersect(const Ray &ray, double& tmin, Intersection &intersection){
    double t;
    
    double inv_radius = 1 / baseRadius;
    double a = ray.direction.x * ray.direction. x + ray.direction.y * ray.direction.y;
    double b = 2.0 * (ray.position.x * ray.direction.x + ray.position.y * ray.direction.y);
    double c = ray.position.x * ray.position.x + ray.position.y * ray.position.y - baseRadius * baseRadius;
    double disc = b * b - 4.0 * a * c;
    
    double y0, y1;
    
    if (base.z < apex.z) {
        y0 = base.z;
        y1 = apex.z;
    } else {
        y0 = apex.z;
        y1 = base.z;
    }
    
    if (disc < 0.0) {
        return false;
    } else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root
        
        if (t > 0) {
            double zhit = ray.position.z + t * ray.direction.z;
            
            if (zhit > base.z && zhit < apex.z) {
                tmin = t;
                intersection.normal = Vec3((ray.position.x + t * ray.direction.x) * inv_radius, (ray.position.y + t * ray.direction.y) * inv_radius, 0.0);
                
                // test for hitting from inside
                
                if (-ray.direction.dot(intersection.normal) < 0.0)
                    intersection.normal = -intersection.normal;
                return (true);
            }
        }
        
        t = (-b + e) / denom;    // larger root
        
        if (t > 0) {
            double zhit = ray.position.z + t * ray.direction.z;
            
            if (zhit > y0 && zhit < y1) {
                tmin = t;
                intersection.normal = Vec3((ray.position.x + t * ray.direction.x) * inv_radius,(ray.position.y + t * ray.direction.y) * inv_radius, 0.0);
                
                // test for hitting inside surface
                
                if (-ray.direction.dot(intersection.normal) < 0.0)
                    intersection.normal = -intersection.normal;
                
                
                return (true);
            }
        }
    }
    
    return false;
}
