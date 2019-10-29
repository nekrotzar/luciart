#include "grid.h"

Grid::Grid(){
    Compound();
    nx = 0;
    ny = 0;
    nz = 0;
}

void Grid::setup_cells(){
    
    // Compute grid bounding box
    compute_bounding_box();
    
    Vec3 p0 = Vec3(boundingBox.xmin, boundingBox.ymin, boundingBox.zmin);
    Vec3 p1 = Vec3(boundingBox.xmax, boundingBox.ymax, boundingBox.zmax);
    
    // Number of objects
    size_t n = objects.size();
    printf("Number of objects = %ld\n", n);

    // Dimensions of the grid
    Vec3 w = p1 - p0;
    
    // Multiplying factor
    double m = GRID_M_FACTOR;
    double s = cbrt((w.x * w.y * w.z) / n );

    nx = m * w.x / s + 1;
    ny = m * w.y / s + 1;
    nz = m * w.z / s + 1;
    
    // Number of cells
    int num_cells = nx * ny * nz;
    printf("Number of grid cells = %d\n", num_cells);
    cells.reserve(num_cells);

    // Initialize cells to null.
    for (int i = 0; i < num_cells; i++) {
        cells.push_back(NULL);
    }
    
    std::vector<int> counts;
    counts.reserve(num_cells);
    
    for (int j = 0; j < num_cells; j++) {
        counts.push_back(0);
    }
    
    AABB objectBox;
    int index;
    
    for (int j = 0; j < n; j++) {
        objectBox = objects[j]->boundingBox;
        
        int ixmin = clamp((objectBox.xmin - p0.x) * nx / (p1.x - p0.x), 0.0, nx - 1);
        int iymin = clamp((objectBox.ymin - p0.y) * ny / (p1.y - p0.y), 0.0, ny - 1);
        int izmin = clamp((objectBox.zmin - p0.z) * nz / (p1.z - p0.z), 0.0, nz - 1);
        int ixmax = clamp((objectBox.xmax - p0.x) * nx / (p1.x - p0.x), 0.0, nx - 1);
        int iymax = clamp((objectBox.ymax - p0.y) * ny / (p1.y - p0.y), 0.0, ny - 1);
        int izmax = clamp((objectBox.zmax - p0.z) * nz / (p1.z - p0.z), 0.0, nz - 1);
        
        for (int iz = izmin; iz <= izmax; iz++)
            for (int iy = iymin; iy <= iymax; iy++)
                for (int ix = ixmin; ix <= ixmax; ix++) {
                    index = ix + nx * iy + nx * ny * iz;
                    
                    if (counts[index] == 0) {
                        cells[index] = objects[j];
                        counts[index] += 1;                    
                    }
                    else {
                        if (counts[index] == 1) {
                            Compound* compoundObject = new Compound;
                            compoundObject->add_object(cells[index]);
                            compoundObject->add_object(objects[j]);
                            cells[index] = compoundObject;
                            counts[index] += 1;         
                        }
                        else {
                            cells[index]->add_object(objects[j]);
                            counts[index] += 1;
                        }
                    }
                }
    }
    
    objects.erase(objects.begin(), objects.end());
    counts.erase(counts.begin(), counts.end());
}

bool Grid::intersect(const Ray &ray, double &t, Intersection &intersection){
    int ix, iy, iz;
    
    // Check intersection of ray with the grid bounding box.
    double t0, t1;
    Vec3 tmin, tmax;
    
    // Check if ray intersects the bounding box
    if(!boundingBox.intersect(ray, t0, t1, tmin, tmax)){
        return false;
    }
    
    // Check if ray is inside the grid bounding box
    if(boundingBox.inside(ray.position)){
        ix = clamp((ray.position.x - boundingBox.xmin) * nx / (boundingBox.xmax - boundingBox.xmin), 0, nx - 1);
        iy = clamp((ray.position.y - boundingBox.ymin) * ny / (boundingBox.ymax - boundingBox.ymin), 0, ny - 1);
        iz = clamp((ray.position.z - boundingBox.zmin) * nz / (boundingBox.zmax - boundingBox.zmin), 0, nz - 1);
    } else {
        Vec3 hitpoint = ray.position + ray.direction * t0;
        
        ix = clamp((hitpoint.x - boundingBox.xmin) * nx / (boundingBox.xmax - boundingBox.xmin), 0, nx - 1);
        iy = clamp((hitpoint.y - boundingBox.ymin) * ny / (boundingBox.ymax - boundingBox.ymin), 0, ny - 1);
        iz = clamp((hitpoint.z - boundingBox.zmin) * nz / (boundingBox.zmax - boundingBox.zmin), 0, nz - 1);
    }
    
    double dtx = (tmax.x - tmin.x) / nx;
    double dty = (tmax.y - tmin.y) / ny;
    double dtz = (tmax.z - tmin.z) / nz;
    
    double tx_next, ty_next, tz_next;
    int ix_step, iy_step, iz_step;
    int ix_stop, iy_stop, iz_stop;
    
    // Compute tnext for the initial cell.
    
    // For x direction of the ray
    if(ray.direction.x > 0){
        tx_next = tmin.x + (ix + 1) * dtx;
        ix_step = +1;
        ix_stop = nx;
    } else {
        tx_next = tmin.x + (nx - ix) * dtx;
        ix_step = -1;
        ix_stop = -1;
    }
    
    if(ray.direction.x == 0) {
        tx_next = INFINITY;
        ix_step = -1;
        ix_stop = -1;
    }
    
    // For y direction of the ray
    if(ray.direction.y > 0){
        ty_next = tmin.y + (iy + 1) * dty;
        iy_step = 1;
        iy_stop = ny;
    } else {
        ty_next = tmin.y + (ny - iy) * dty;
        iy_step = -1;
        iy_stop = -1;
    }
    if(ray.direction.y == 0) {
        ty_next = INFINITY;
        iy_step = -1;
        iy_stop = -1;
    }
    
    // For z direction of the ray
    if(ray.direction.z > 0){
        tz_next = tmin.z + (iz + 1) * dtz;
        iz_step = 1;
        iz_stop = nz;
    } else {
        tz_next = tmin.z + (nz - iz) * dtz;
        iz_step = -1;
        iz_stop = -1;
    }
    if(ray.direction.z == 0) {
        tz_next = INFINITY;
        iz_step = -1;
        iz_stop = -1;
    }
    
    // Grid Traversal
    
    while (true){
        int index = ix + nx * iy + nx * ny * iz;
        Object * object = cells[index];
        
        if ((tx_next < ty_next) && (tx_next < tz_next)) {
            if ((object != NULL) && (object->intersect(ray, t, intersection)) && (t < tx_next)) {
                intersection.material = object->material;
                return (true);
            }
            
            tx_next += dtx;
            ix += ix_step;
            
            if (ix == ix_stop)
                return (false);
        }
        else {
            if (ty_next < tz_next) {
                if ((object != NULL) && (object->intersect(ray, t, intersection)) && (t < ty_next)) {
                    intersection.material = object->material;
                    return (true);
                }
                ty_next += dty;
                iy += iy_step;
                
                if (iy == iy_stop)
                    return (false);
            }
            else {
                if ((object != NULL) && (object->intersect(ray, t, intersection)) && (t < tz_next)) {
                    intersection.material = object->material;
                    return (true);
                }
                
                tz_next += dtz;
                iz += iz_step;
                
                if (iz == iz_stop)
                    return (false);
            }
        }
    }
}
