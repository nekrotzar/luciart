#ifndef polygon_h
#define polygon_h

#include <vector>
#include "object.h"
#include "vec3.h"
#include "vec2.h"
#include "plane.h"

/**
 * @class Polygon.
 * Polygon defined by a set of vertices (n > 3).
 */
class Polygon : public Object {
public:
    int numVertices;            /**< Number of vertices of the polygon. */
    std::vector<Vec3> vertices; /**< Vertices that define the polygon surface. */
    Vec3 normal;                /**< Normal vector of the polygon. */
    Plane plane;                /**< Infinite plane embed to the polygon. */
    
    /**
     * Default polygon constructor.
     */
    Polygon();
    
    /**
     *  Contructor
     *  @param n Number of vertices.
     *  @param v Vertices vector structure.
     *  @param m Fill material.
     */
    Polygon(int n, std::vector<Vec3> &v , const Material &m);
    
    /**
     * Initialize object bounding box.
     */
    void compute_bounding_box();
    
    /**
     * Check if a ray intersects a polygon and stores normal and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the polygon, false otherwise.
     */
    bool intersect(const Ray &ray, double &tmin, Intersection &intersection);
};

#endif /* polygon_h */
