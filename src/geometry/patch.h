#ifndef patch_h
#define patch_h

#include <vector>
#include "polygon.h"
#include "vec3.h"

/**
 * @class PolygonPath.
 * Polygon patch defined by a set of vertices and normals.
 */
class PolygonPatch : public Polygon {
public:
    std::vector<Vec3> normals;  /**< Normals at each vertex. */
    
    /**
     * Default polygon patch constructor.
     */
    PolygonPatch();
    
    /**
     *  Contructor
     *  @param num Number of vertices.
     *  @param v Vertices vector structure.
     *  @param n Normals vector structure.
     *  @param m Fill material.
     */
    PolygonPatch(int num, std::vector<Vec3> &v, std::vector<Vec3> &n, const Material &m);
    
    /**
     * Initialize object bounding box.
     */
    void compute_bounding_box();
    
    /**
     * Check if a ray intersects a polygon patch and stores normal and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects the polygon patch, false otherwise.
     */
    bool intersect(const Ray &ray, double& tmin, Intersection &intersection);
};


#endif /* patch_h */
