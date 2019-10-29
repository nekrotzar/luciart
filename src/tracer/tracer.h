#ifndef tracer_h
#define tracer_h

#include "scene.h"

/**
 * @class Tracer.
 * Color pixel depending on sampling method.
 */
class Tracer {
public:
    Scene * scene;              /**< Scene pointer. */
    Sampler * aliasing_sampler; /**< Anti-aliasing sampling method. */
    Sampler * reflect_sampler;  /**< Glossy reflection sampling method. */
    
    /**
     * Constructor
     * @param scene Scene pointer.
     */
    Tracer(Scene * scene);
        
    /**
     * Get color from ray casting.
     * @param ray Ray casted.
     * @param depth Current ray depth.
     * @param RefrIndex Refraction index.
     * @return Color.
     */
    Color rayTracing( Ray ray, int depth, float RefrIndex);
    
    /**
     * Color of direct illumination by the blinn-phong model.
     * @param i Closest intersection information.
     * @return Color of the diffuse component.
     */
    virtual Color shade(const Intersection& i) = 0;
    
    /**
     * Color contribution by reflection.
     * @param i Closest intersection information.
     * @param ray Ray.
     * @param depth Recursion depth.
     * @param RefrIndex Refraction index.
     * @return Color of the diffuse component.
     */
    Color reflectionColor(const Intersection &i, Ray ray, int depth, int RefrIndex);
    
    /**
     * Color contribution by refraction.
     * @param i Closest intersection information.
     * @param ray Ray.
     * @param depth Recursion depth.
     * @param RefrIndex Refraction index.
     * @return Color of the diffuse component.
     */
    Color refractionColor(const Intersection &i, Ray ray, int depth, int RefrIndex);

    /**
     * Get pixel color
     * @param x Pixel coordinate in the x axis.
     * @param y Pixel coordinate in the y axis.
     * @return Color of the pixel at the coordinate (x,y).
     */
    virtual Color color_pixel(const int x, const int y) = 0;
    
    /**
     * Set sampling method for anti-aliasing reflection.
     * @param s Anti-aliasing sampling method.
     */
    void set_aliasing_sampler(Sampler * s);
    
    /**
     * Set sampling method for glossy reflection.
     * @param s Reflection sampling method.
     */
    void set_reflection_sampler(Sampler * s);
};


#endif /* tracer_h */
