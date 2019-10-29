#ifndef cylinder_h
#define cylinder_h

#include "object.h"
#include "vec3.h"
#include "material.h"

/**
 * @class Cylinder.
 * Cylinder defined by a base and a apex.
 */
class Cylinder : public Object {
public:
    Vec3 apex;          /**< Apex vertex of the cylinder. */
    Vec3 base;          /**< Base vertex of the cylinder. */
    double apexRadius;   /**< Apex radius. */
    double baseRadius;   /**< Base radius. */
    
    /**
     * Default cylinder constructor.
     */
    Cylinder();
    
    /**
     *  Contructor
     *  @param b Base vertex.
     *  @param a Apex vertex.
     *  @param bRadius Base radius.
     *  @param aRadius Apex radius.
     *  @param m Fill material.
     */
    Cylinder(const Vec3 &b, const Vec3 &a, float bRadius, float aRadius, const Material &m);
    
    /**
     * Initialize object bounding box.
     */
    void compute_bounding_box();
    
    /**
     * Check if a ray intersects a cylinder and stores normal and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the cylinder, false otherwise.
     */
    bool intersect(const Ray &ray, double& tmin ,Intersection &intersection);
};

#endif /* cylinder_h */
