#ifndef cone_h
#define cone_h

#include "object.h"
#include "vec3.h"
#include "material.h"
#include "utility/constants.h"

/**
 * @class Cone.
 * Cone defined by a base and a apex.
 */
class Cone : public Object {
public:
    Vec3 apex;          /**< Apex vertex of the cone. */
    Vec3 base;          /**< Base vertex of the cone. */
    double apexRadius;   /**< Apex radius. */
    double baseRadius;   /**< Base radius. */
    
    /**
     * Default cone constructor.
     */
    Cone();
    
    /**
     *  Contructor
     *  @param b Base vertex.
     *  @param a Apex vertex.
     *  @param bRadius Base radius.
     *  @param aRadius Apex radius.
     *  @param m Fill material.
     */
    Cone(const Vec3 &b, const Vec3 &a, float bRadius, float aRadius, const Material &m);
    
    /**
     * Initialize object bounding box.
     */
    void compute_bounding_box();
    
    /**
     * Check if a ray intersects a cone and stores normal and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the cone, false otherwise.
     */
    bool intersect(const Ray &ray, double& tmin ,Intersection &intersection);
};

#endif /* cone_h */
