#ifndef plane_h
#define plane_h

#include "object.h"
#include "vec3.h"
#include "material.h"

/**
 * @class Plane.
 * Plane defined by 3 points A,B and C and a normal vector;
 */
class Plane : public Object {
public:
    Vec3 p1;        /**< First point. */
    Vec3 p2;        /**< Second point. */
    Vec3 p3;        /**< Third point. */
    Vec3 normal;    /**< Normal of the plane. */
    
    /**
     * Default plane constructor.
     */
    Plane();
    
    /**
     *  Contructor
     *  @param p1 First XYZ point.
     *  @param p2 Second XYZ point.
     *  @param p3 Third XYZ point.
     */
    Plane(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3);
    
    /**
     *  Contructor
     *  @param p1 First XYZ point.
     *  @param p2 Second XYZ point.
     *  @param p3 Third XYZ.
     *  @param m Fill material.
     */
    Plane(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, const Material &m);
    
    /**
     * Initialize object bounding box.
     */
    void compute_bounding_box();
    
    /**
     * Check if a ray intersects a plane and stores normal and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the plane, false otherwise.
     */
     bool intersect(const Ray &ray, double& tmin, Intersection &intersection);
};

#endif /* plane_h */
