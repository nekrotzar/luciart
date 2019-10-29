#ifdef __APPLE__
    #include "sampler.h"
#else
    #include "sampler/sampler.h"
#endif
#define _USE_MATH_DEFINES
#include <cmath>

Sampler::Sampler(){
    count = 0;
    jump = 0;
    num_samples = 1;
    num_sets = 100;
}

Sampler::Sampler(const int n){
    count = 0;
    jump = 0;
    num_samples = n;
    num_sets = 100;
}

Sampler::Sampler(const int n, const int s){
    count = 0;
    jump = 0;
    num_samples = n;
    num_sets = s;
}

void Sampler::map_samples_to_hemisphere(const float exp){
    size_t size = samples.size();
    hemisphere_samples.reserve(num_samples * num_sets);
    
    for (int i = 0; i < size; i++) {
        float cos_phi = cos(2.0 * M_PI * samples[i].x);
        float sin_phi = sin(2.0 * M_PI * samples[i].x);
        float cos_theta = pow((1.0 - samples[i].y), 1.0 / (exp + 1.0));
        float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
        float pu = sin_theta * cos_phi;
        float pv = sin_theta * sin_phi;
        float pw = cos_theta;
        hemisphere_samples.push_back(Vec3(pu, pv, pw));
    }
}

void Sampler::map_samples_to_unit_disk()
{
	size_t size = samples.size();
	float r, phi;		// polar coordinates
	Vec2 sp; 		// sample point on unit disk

	diskSamples.reserve(size);

	for (int j = 0; j < size; j++) {
		// map sample point to [-1, 1] X [-1,1]

		sp.x = 2.0 * samples[j].x - 1.0;
		sp.y = 2.0 * samples[j].y - 1.0;

		if (sp.x > -sp.y) {			// sectors 1 and 2
			if (sp.x > sp.y) {		// sector 1
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else {					// sector 2
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else {						// sectors 3 and 4
			if (sp.x < sp.y) {		// sector 3
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else {					// sector 4
				r = -sp.y;
				if (sp.y != 0.0)	// avoid division by zero at origin
					phi = 6 - sp.x / sp.y;
				else
					phi = 0.0;
			}
		}

		phi *= M_PI / 4.0;

		diskSamples[j].x = r * cos(phi);
		diskSamples[j].y = r * sin(phi);
	}

	samples.erase(samples.begin(), samples.end());
}

Vec2 Sampler::sample_unit_square(){
    if (count % num_samples == 0)
        jump = (random_int() % num_sets) * num_samples;
    
    return samples[jump + count++ % num_samples];
}

Vec2 Sampler::sample_unit_disk() {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (random_int() % num_sets) * num_samples;

	return diskSamples[jump + count++ % num_samples];
	//return (diskSamples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

Vec3 Sampler::sample_hemisphere(){
    if(count % num_samples == 0)
        jump = (random_int() % num_sets) * num_samples;
    return hemisphere_samples[jump + count++ % num_samples];
}

