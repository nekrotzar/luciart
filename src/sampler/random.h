#ifndef random_h
#define random_h

#include "sampler.h"

/**
 * @class Random Sampler.
 * Generate random samples for distributed ray-tracing.
 */
class Random : public Sampler {
public:
    /**
     * Default random sampler constructor.
     */
    Random();
    
    /**
     * Contructor
     * @param n Number of samples.
     */
    Random(const int n);

	Random(Sampler* sp);
    
    /**
     * Generate random samples positions.
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

#endif /* random_h */

