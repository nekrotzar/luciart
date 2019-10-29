#ifndef object_h
#define object_h

#include <iostream>

#include "material.h"
#include "ray.h"
#include "intersection.h"
#include "aabb.h"

typedef struct Cache {
    double t = 0;
    unsigned long ray_id = LONG_MAX;
} Cache ;

/**
 * @class Object.
 * Scene object.
 */
class Object {
public:
    Material material;    /**< Object material defined by color and Blinn-Phong components */
    AABB boundingBox;      /**< Axis aligned bounding box. */
    Cache mailBox;        /**< Store previous intersection. */

    
    /**
     * Initialize object bounding box.
     */
    virtual void compute_bounding_box() = 0;
    
    /**
     * Add object to compound objects.
     * @param o Object pointer.
     */
    virtual void add_object(Object * o);
    
    /**
     * Check if a ray intersects an object and stores normal and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the object, false otherwise.
     */
    virtual bool intersect(const Ray &ray, double& tmin ,Intersection &intersection) = 0;
};

#endif /* object_h */
