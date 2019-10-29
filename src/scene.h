#ifndef scene_h
#define scene_h

#include <vector>
#include <string>
#include <memory>

#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "material.h"
#include "light/light.h"
#include "intersection.h"
#include "camera/camera.h"
#include "geometry/object.h"
#include "geometry/grid.h"

class Scene {
public:
    Camera * camera;                /** Scene camera. */
    Grid *  grid;                   /**< Acceleration grid pointer. */
    std::vector<Light*> lights;     /** Lights in the scene. */
    std::vector<Object*> objects;   /** Objects in the scene. */

    Color background;               /** Scene background color. */
    Material fill;                  /** Current fill material. */
    
    /**
     * Default scene constructor sets background color to black.
     */
    Scene();
    ~Scene();
    
    /**
     * Get scene camera.
     * @return The camera of the scene.
     */
    Camera* GetCamera();
    
    /**
     * Get background color.
     * @return Color of the scene background.
     */
    Color GetBackground();
    
    /**
     * Get lights.
     * @return Lights of the scene as a vector.
     */
    std::vector<Light*> GetLights();
    
    /**
     * Get objects.
     * @return Object pointers of the scene as a vector .
     */
    std::vector<Object*> GetObjects();
    
    /**
     * Get intersection, if any.
     * @param ray Ray.
     * @return Intersection info.
     */
    Intersection hit_objects(const Ray &ray);
    
    /**
     * Check if ray intersects any object.
     * @param shadowRay Shadow ray.
     * @return True if ray intersectis with any object.
     */
    bool inShadow(const Ray &shadowRay);
};

#endif /* scene_h */
