#ifndef jittered_h
#define jittered_h

#include "sampler.h"

/**
 * @class Jittered Sampler.
 * Generate random samples for distributed ray-tracing dividing the pixel in a grid of N by N.
 */
class Jittered : public Sampler {
public:
    /**
     * Default jittered sampler constructor.
     */
    Jittered();
    
    /**
     * Contructor
     * @param n Number of samples.
     */
    Jittered(const int n);
    
    /**
     * Contructor
     * @param n Number of samples.
     * @param s Number of sets.
     */
    Jittered(const int n, const int s);
    
    /**
     * Generate random samples positions in a grid of sqrt(n) x sqrt(n) sub-pixels.
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

#endif /* jittered_h */
