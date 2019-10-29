#ifndef distributed_h
#define distributed_h

#include "tracer.h"
#include "sampler/regular.h"
#include "camera/lens.h"


/**
 * @class Distributed Tracer.
 * Color pixel several samples per pixel.
 */
class DistributedTracer : public Tracer {
public:
    /**
     * Constructor
     * @param scene Scene pointer.
     */
    DistributedTracer(Scene * scene);
    
    /**
     * Get pixel color
     * @param x Pixel coordinate in the x axis.
     * @param y Pixel coordinate in the y axis.
     * @return Color of the pixel at the coordinate (x,y).
     */
    virtual Color color_pixel(const int x, const int y);
    
    /**
     * Get pixel color (selective method)
     * @param x Pixel coordinate in the x axis.
     * @param y Pixel coordinate in the y axis.
     * @return Color of the pixel at the coordinate (x,y).
     */
    virtual Color selective_color_pixel(const int x, const int y);
    
    /**
     * Get pixel color (adaptive method)
     * @param x Pixel coordinate in the x axis.
     * @param y Pixel coordinate in the y axis.
     * @return Color of the pixel at the coordinate (x,y).
     */
    virtual Color adaptive_color_pixel(double x, double y, std::vector<Color*>& colors, int index ,int depth);
    
    /**
     * Color of direct illumination by the blinn-phong model.
     * @param i Closest intersection information.
     * @return Color of the diffuse component.
     */
    virtual Color shade(const Intersection& i);
    
private:
    /**
     * Check if the pixel corner colors diference is greater than the threshold.
     * @param corners Corners of a pixel or sub-pixel.
     * @param threshold Color difference threshold value.
     * @return Return true if the colors have similar (smaller than the threshold) colors. False, otherwise.
     */
    bool checkThreshold(std::vector<Color> corners, const float threshold);
};


#endif /* distributed_h */
