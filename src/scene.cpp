#include "scene.h"

Scene::Scene() {
    background = Color(0,0,0);
    grid = NULL;
}

bool Scene::inShadow(const Ray &shadowRay){
    double t;
    Intersection intersection;
    
    for (Object * object: objects) {
        if ((object->intersect(shadowRay, t,  intersection))){
            return true;
        }
    }
    
    return false;
}


Intersection Scene::hit_objects(const Ray &ray){
    
    Intersection intersection;
    double t;
    Vec3 normal;
    double tmin = INFINITY;
   
    // Check intersection with all objects in the scene.
    if(grid == NULL){
        for (Object * object: objects) {
            if ((object->intersect(ray, t,  intersection) && (t < tmin))) {
                intersection.hit_status = true;
                normal = intersection.normal;
                tmin = t;
                intersection.material = object->material;
            }
        }
        
        if (intersection.hit_status) {
            intersection.t = tmin;
            intersection.normal = normal;
            intersection.hitpoint = ray.position + ray.direction * tmin;
        }
    
        
    // Check intersection with grid cells.
    } else {
        if(grid->intersect(ray, t, intersection)){
            intersection.hit_status = true;
            intersection.hitpoint = ray.position + ray.direction * t;
        } 

    }
    
    return intersection;
}

Camera* Scene::GetCamera(){
    return camera;
}

Color Scene::GetBackground(){
    return background;
}

std::vector<Light*> Scene::GetLights(){
    return lights;
}

std::vector<Object*> Scene::GetObjects(){
    return objects;
}

