#ifndef adaptive_h
#define adaptive_h

#include "sampler.h"

/**
 * @class Monte Carlo Sampler.
 * Generate 4 samples for each corner of the pixel or sub-pixel.
 */
class Adaptive : public Sampler {
public:
    /**
     * Default monte carlo Adaptive sampler constructor.
     */
    Adaptive();
    
    /**
     * Generate sample positions in the corners of a unit pixel.
     */
    virtual void generate_samples();
    
    /**
     * Sample unit square.
     */
    virtual Vec2 sample_unit_square();
    
    /**
     * Sample hemisphere
     */
    virtual Vec3 sample_hemisphere();
};

#endif /* adaptive_h */

