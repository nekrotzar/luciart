#ifndef regular_h
#define regular_h

#include "sampler.h"

/**
 * @class Regular Sampler.
 * Generate samples for distributed ray-tracing dividing the pixel in a grid of N by N.
 */
class Regular : public Sampler {
public:
    /**
     * Default regular sampler constructor.
     */
    Regular();
    
    /**
     * Contructor
     * @param n Number of samples.
     */
    Regular(const int n);
    
    /**
     * Generate sample positions in a grid of sqrt(n) x sqrt(n).
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

#endif /* regular_h */
