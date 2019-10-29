#ifdef __APPLE__
    #include "random.h"
#else
    #include "sampler/random.h"
#endif
Random::Random() : Sampler() {
    generate_samples();
    type = SELECTIVE;
}

Random::Random(const int n) : Sampler(n) {
    generate_samples();
    type = SELECTIVE;
}

Random::Random(Sampler* sp) : Sampler(sp->num_samples) {
	samples = sp->samples;
	type = SELECTIVE;
}

void Random::generate_samples(){
    for(int q = 0; q < num_sets; q++)
        for (int p = 0; p < num_samples; p++)
            samples.push_back(Vec2(random_float(),random_float()));
}

Vec2 Random::sample_unit_square(){
    if (count % num_samples == 0)
        jump = (random_int() % num_sets) * num_samples;
    
    return samples[jump + count++ % num_samples];
}

Vec3 Random::sample_hemisphere(){
    if (count % num_samples == 0)
        jump = (random_int() % num_sets) * num_samples;
    
    return hemisphere_samples[jump + count++ % num_samples];
}
