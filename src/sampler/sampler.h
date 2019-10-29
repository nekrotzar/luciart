#ifndef sampler_h
#define sampler_h

#include <vector>
#include "vec2.h"
#include "vec3.h"

#include "utility/utility.h"
#include "utility/constants.h"


/**
 * @class Sampler.
 * Generate samples for distributed ray-tracing.
 */
class Sampler{
public:
    int type;                               /**< Type of sampling. (0 - selective, 1 - adaptive) */
    int num_samples;                        /**< Number of samples to be generated. */
    int num_sets;                           /**< Number of pattern stored. */
    int jump;                               /**< Random index jump. */
    unsigned long count;                    /**< Number of sample points used */
    std::vector<Vec2> samples;              /**< Sample positions in the 2D plane. */
	std::vector<Vec2> diskSamples;          /**< Sample positions on a unit disk. */
    std::vector<Vec3> hemisphere_samples;   /**< Sample position in an hemisphere. */
    std::vector<int> shuffled_indices;      /**< Shuffled samples indices. */
    
    /**
     * Default sampler constructor.
     */
    Sampler();
    
    /**
     * Contructor
     * @param n Number of samples.
     */
    Sampler(const int n);
    
    /**
     * Contructor
     * @param n Number of samples.
     * @param s Number of sets.
     */
    Sampler(const int n, const int s);
    
    /**
     * Generate sample positions.
     */
    virtual void generate_samples() = 0;
    
    /**
     * Sample unit square.
     * @return 2D position in the square.
     */
    virtual Vec2 sample_unit_square() = 0;

    /**
     * Sample disk.
     * @return 2D position in the disk.
     */
	virtual Vec2 sample_unit_disk();
    
    /**
     * Sample hemisphere.
     * @return 3D position in an hemisphere.
     */
    virtual Vec3 sample_hemisphere() = 0;
    
    /**
     * Sample positions in an hemisphere.
     * @param exp Exponential.
     */
    void map_samples_to_hemisphere(const float exp);

    /**
     * Sample positions in an disk.
     */
	void map_samples_to_unit_disk();
};

#endif /* sampler_h */
