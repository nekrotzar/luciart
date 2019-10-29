#ifndef aabb_h
#define aabb_h

#include "utility/constants.h"
#include "vec3.h"
#include "ray.h"
#include "intersection.h"

/**
 * @class AABB.
 * Axis aligned bounding box defined by minimum and maximum values for x,y and z coordinates.
 */
class AABB {
public:
    double xmin;    /**< Minimum x coordinate. */
    double xmax;    /**< Maximum x coordinate. */
    double ymin;    /**< Minimum y coordinate. */
    double ymax;    /**< Maximum y coordinate. */
    double zmin;    /**< Minimum z coordinate. */
    double zmax;    /**< Maximum z coordinate. */
    
    /**
     * Default AABB constructor.
     */
    AABB();
    
    /**
     * Contructor
     * @param xmin x minimum value.
     * @param xmax x maximum value.
     * @param ymin y minimum value.
     * @param ymax y maximum value.
     * @param zmin z minimum value.
     * @param zmax z maximum value.
     */
    AABB(const double xmin, const double xmax, const double ymin, const double ymax, const double zmin, const double zmax);
    
    /**
     * Constructor
     * @param pmin 3D point with minimum coordinate values.
     * @param pmax 3D point with maximum coordinate values.
     */
    AABB(const Vec3 pmin, const Vec3 pmax);
    
    /**
     * Check if a ray intersects a bounding box and stores and length.
     * @param ray Ray.
     * @param t1 Entering t.
     * @param t0 Exiting t.
     * @param tmin Minimum t values.
     * @param tmax Maximum t values;
     * @return Return true if the ray intersects the triangle, false otherwise.
     */
    bool intersect(const Ray &ray, double &t0, double &t1, Vec3 &tmin, Vec3 &tmax);
        
    /**
     * Check if the ray origin is inside the bounding box.w
     * @param p Point to be tested.
     * @return Return true if point is inside the bounding box, false otherwise.
     */
    bool inside(const Vec3 &p);
    
    /**
     * Set bounding box.
     * @param min Minimum coordinates.
     * @param max Maximum coordinates.
     */
    void set_bounding_box(const Vec3 &min, const Vec3 &max);
};


#endif /* aabb_h */
