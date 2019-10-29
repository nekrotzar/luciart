#include "compound.h"

Compound::Compound(){}

void Compound::add_object(Object *object){
    objects.push_back(object);
}


void Compound::compute_bounding_box(){
    Vec3 min = Vec3(INFINITY, INFINITY, INFINITY);
    Vec3 max = Vec3(-INFINITY, -INFINITY, -INFINITY);
    
    AABB objectBox;
    size_t n = objects.size();
    
    for(int j = 0; j < n; j++){
        objectBox = objects[j]->boundingBox;
        
        // Bounding box minimum coordinate
        if (objectBox.xmin < min.x) {
            min.x = objectBox.xmin;
        }
        if (objectBox.ymin < min.y) {
            min.y = objectBox.ymin;
        }
        if (objectBox.zmin < min.z) {
            min.z = objectBox.zmin;
        }
        
        // Bounding box maximum coordinate
        if (objectBox.xmax > max.x) {
            max.x = objectBox.xmax;
        }
        if (objectBox.ymax > max.y) {
            max.y = objectBox.ymax;
        }
        if (objectBox.zmax > max.z) {
            max.z = objectBox.zmax;
        }
    }
    
    min = min - EPSILON;
    max = max + EPSILON;
    
    boundingBox.set_bounding_box(min, max);
}

bool Compound::intersect(const Ray &ray, double &tmin, Intersection &intersection){
    double t;
    Vec3 normal;
    tmin = INFINITY;
    bool hit = false;
    
    
    size_t num_objects = objects.size();
    
    for (int i = 0; i < num_objects; i++) {
        if((objects[i]->intersect(ray, t, intersection)) && (t < tmin)){
            hit = true;
            normal = intersection.normal;
            tmin = t;
            material = objects[i]->material;
        }
    }
    
    if(hit){
        intersection.hit_status = true;
        intersection.t = tmin;
        intersection.normal = normal;
        intersection.material = material;
        return true;
    }
    
    return false;
    
}
