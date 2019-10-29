#ifndef compound_h
#define compound_h

#include <vector>

#include "geometry/object.h"
#include "utility/utility.h"
#include "utility/constants.h"

/**
 * @class Compound.
 * Object that contains other objects.
 */
class Compound  : public Object {
public:
    std::vector<Object*> objects;   /**< Array of object pointers.*/
    
    /**
     * Default compound object constructor.
     */
    Compound();
    
    /**
     * Initialize object bounding box.
     */
    void compute_bounding_box();
    
    /**
     * Add object to compound object.
     * @param object Object pointer.
     */
    void add_object(Object * object);
    
    /**
     * Check if a ray intersects a compound object and stores and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the compound object, false otherwise.
     */
    bool intersect(const Ray &ray, double &tmin, Intersection &intersection);
};

#endif /* compound_h */
