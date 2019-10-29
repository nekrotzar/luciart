#ifndef intersection_h
#define intersection_h

#include "vec3.h"
#include "ray.h"
#include "material.h"

/**
 * @class Intersection
 * Intersection between a ray and an object.
 */
class Intersection {
public:
    bool hit_status;    /**< Ray hit an object is true, false otherwise. */
    Vec3 hitpoint;      /**< Intersection 3D point between ray and point. */
    Vec3 normal;        /**< Normal 3D vector in the intersected point. */
    Ray ray;            /**< Ray used in intersection */
    double t;           /**< Lenght of ray from ray origin to the hit point. */
    Material material;  /**< Material of the intersected object for color shading */
    
    /**
     * Default constructor. Uses default values for everything.
     */
    Intersection();
    
    /**
     *  Constructor
     *  @param i Intersection copy.
     */
    Intersection(const Intersection& i);
};

#endif /* intersection_h */
