#ifndef triangle_h
#define triangle_h

#include "object.h"
#include "polygon.h"
#include "plane.h"
#include "vec2.h"

#include "utility/constants.h"

/**
 * @class Triangle.
 * Triangle defined by three vertices and a normal vector.
 */
class Triangle : public Object {
public:
    Vec3 p1;        /**< First point. */
    Vec3 p2;        /**< Second point. */
    Vec3 p3;        /**< Third point. */
    Vec3 normal;    /**< Normal of the triangle. */
    
    /**
     * Default triangle constructor.
     */
    Triangle();
    
    /**
     *  Contructor
     *  @param a First vertex.
     *  @param b Second vertex.
     *  @param c Third vertex.
     *  @param m Fill material.
     */
    Triangle(const Vec3& a, const Vec3& b, const Vec3& c, const Material &m);
    
    /**
     * Initialize triangle bounding box.
     */
    void compute_bounding_box();
    
    /**
     * Check if a ray intersects a triangle and stores and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the triangle, false otherwise.
     */
    bool intersect(const Ray &ray, double &tmin, Intersection &intersection);
};

#endif /* triangle_h */
