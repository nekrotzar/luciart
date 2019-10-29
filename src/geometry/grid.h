#ifndef grid_h
#define grid_h

#include <vector>

#include "compound.h"
#include "aabb.h"

#include "utility/utility.h"
#include "utility/constants.h"


/**
 * @class Grid.
 * Uniform acceleration grid.
 */
class Grid : public Compound {
public:
    std::vector<Object*> cells;     /**< 1-dimensional array of cells. */
    int nx;                         /**< Number of cells in x direction. */
    int ny;                         /**< Number of cells in y direction. */
    int nz;                         /**< Number of cells in z direction. */
    
    /**
     * Default grid constructor.
     */
    Grid();
    
    /**
     * Setup the grid cells
     */
    void setup_cells();
        
    /**
     * Check if a ray intersects an object in a cell and stores and length.
     * @param ray Ray.
     * @param tmin Length of the intersection ray.
     * @param intersection Intersection stores normal.
     * @return Return true if the ray intersects any object, false otherwise.
     */
    bool intersect(const Ray &ray, double &tmin, Intersection &intersection);
};

#endif /* grid_h */
