#ifdef __APPLE__
    #include "adaptive.h"
#else
    #include "sampler/adaptive.h"
#endif

Adaptive::Adaptive() : Sampler(4) {
    generate_samples();
    type = ADAPTIVE;
}

void Adaptive::generate_samples(){
    samples.push_back(Vec2(0,0));
    samples.push_back(Vec2(1,0));
    samples.push_back(Vec2(0,1));
    samples.push_back(Vec2(1,1));
}

Vec2 Adaptive::sample_unit_square(){
    if (count % num_samples == 0)
        count = 0;
    
    return samples[count++ % num_samples];
}

Vec3 Adaptive::sample_hemisphere(){
    return Sampler::sample_hemisphere();
}
