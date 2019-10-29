#ifndef light_h
#define light_h

#include "color.h"
#include "geometry/area.h"


/**
 * @class Light.
 * Positional light in XYZ with RGB color.
 */
class Light{
public:
    float intensity;    /**< Intensity of the light. */
    Vec3 position;      /**< Position of the light. */
    Color color;        /**< Color of the light. */
    Area * area;        /**< Area of light */
    
    /**
     * Default light constructor sets light to position (0,0,0) and the color white.
     */
    Light();
    
    /**
     * Constructor sets the light's position and color values for each component.
     * @param x x component value.
     * @param y y component value.
     * @param z z component value.
     */
    Light(float x, float y, float z, float r, float g, float b);
    
    /**
     * Contructor
     * @param p Position copy.
     * @param c Color copy
     */
    Light(const Vec3 &p, const Color &c);
    
    /**
     * Set light area.
     * @param a Area.
     */
    void set_area(Area * a);
    
    /**
     * Get number of samples of the area sampler.
     * @return Number of samples.
     */
    int num_samples();
    
    /**
     * Get 3D position inside the area that defines the light.
     * @return Sampled position.
     */
    Vec3 sample_position();
};

#endif /* light_h */
