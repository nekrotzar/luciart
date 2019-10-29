#ifndef naive_h
#define naive_h

#include "tracer.h"

/**
 * @class Naive Tracer.
 * Color pixel sending one sample per pixel.
 */
class NaiveTracer : public Tracer {
public:
    /**
     * Constructor
     * @param scene Scene pointer.
     */
    NaiveTracer(Scene * scene);
    
    /*
     * Get pixel color
     * @param x Pixel coordinate in the x axis.
     * @param y Pixel coordinate in the y axis.
     * @return Color of the pixel at the coordinate (x,y).
     */
    virtual Color color_pixel(const int x, const int y);
    
    /**
     * Color of direct illumination by the blinn-phong model.
     * @param i Closest intersection information.
     * @return Color of the diffuse component.
     */
    virtual Color shade(const Intersection& i);    
};


#endif /* naive_h */
