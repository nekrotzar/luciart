#ifdef __APPLE__
    #include "regular.h"
#else
    #include "sampler/regular.h"
#endif

Regular::Regular() : Sampler(){
    generate_samples();
    type = SELECTIVE;
}

Regular::Regular(const int n) : Sampler::Sampler(n) {
    generate_samples();
    type = SELECTIVE;
}

void Regular::generate_samples(){
    int n = sqrt(num_samples);
    
    for (int j = 0; j < num_sets; j++)
        for (int p = 0; p < n; p++)
            for (int q = 0; q < n; q++)
                samples.push_back(Vec2((float) (p + 0.5)/n, (float) (q + 0.5)/n));
}

Vec2 Regular::sample_unit_square(){
    if (count % num_samples == 0)
        count = 0;
    return samples[count++ % num_samples];
}

Vec3 Regular::sample_hemisphere(){
    if (count % num_samples == 0)
        count = 0;
    return hemisphere_samples[count++ % num_samples];
}
