#ifndef area_h
#define area_h

#include "vec3.h"
#include "sampler/sampler.h"

/**
 * @class Area.
 * Area to sample light positions.
 */
class Area {
public:
    Vec3 position;      /**< Position at the center of the area. */
    Vec3 normal;        /**< Normal of the area surface. */
    Sampler * sampler;  /**< Sampling method. */
    
    /**
     * Get a sample position inside the  area.
     * @return Sampled position.
     */
    virtual Vec3 sample() = 0;
};

#endif /* area_h */
