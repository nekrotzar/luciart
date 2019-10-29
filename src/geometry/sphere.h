#ifndef sphere_h
#define sphere_h

#include "object.h"
#include "vec3.h"

/**
 * @class Sphere.
 * Plane defined by a center and a radius.
 * If the radius is negative only the inside is visible.
 */
class Sphere : public Object {
public:
    double radius;   /** Radius of the sphere. */
    Vec3 center;    /** Center of the sphere in XYZ. */
    
    /**
     * Default plane constructor.
     */
    Sphere();
    
    /**
     *  Contructor
     *  @param c Center of the sphere.
     *  @param r Radius.
     */
    Sphere(const Vec3 &c, float r);
    
    /**
     *  Contructor
     *  @param c Center of the sphere.
     *  @param r Radius.
     *  @param m Fill material
     */
    Sphere(const Vec3 &c, float r, const Material &m);
    
    /**
     * Initialize object bounding box.
     */
    void compute_bounding_box();
    
    /**
     * Check if a ray intersects a sphere and stores normal and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the sphere, false otherwise.
     */
    bool intersect(const Ray &ray, double& tmin ,Intersection &intersection);
    
};

#endif /* sphere_h */
