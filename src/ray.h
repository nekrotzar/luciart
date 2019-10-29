#ifndef ray_h
#define ray_h

#include "vec3.h"
/**
 * @class Ray.
 * Ray from a 3d point directed by unit vector.
 */
class Ray {
public:
    Vec3 direction; /**< Direction of the ray */
    Vec3 position;  /**< The origin of the ray */
    unsigned long rayID; /**< Unique id of the ray */
    static unsigned long increment; /**< Keeps info about last ray id.*/
    
    /**
     * Default ray constructor.
     */
    Ray();
    
    /**
     * Constructor sets the ray origin and direction.
     * @param p position of the ray.
     * @param d direction of the ray.
     */
    Ray(const Vec3& p, const Vec3& d);
};

#endif /* ray_h */
