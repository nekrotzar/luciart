#ifdef __APPLE__
    #include "jittered.h"
#else
    #include "sampler/jittered.h"
#endif

Jittered::Jittered() : Sampler() {
    generate_samples();
    type = SELECTIVE;
}

Jittered::Jittered(const int n) : Sampler(n) {
    generate_samples();
    type = SELECTIVE;
}

Jittered::Jittered(const int n, const int s) : Sampler(n,s) {
    generate_samples();
    type = SELECTIVE;
}

void Jittered::generate_samples(){
    int n = sqrt(num_samples);
    
    for (int j = 0; j < num_sets; j++)
        for (int p = 0; p < n; p++)
            for (int q = 0; q < n; q++)
                samples.push_back(Vec2((float) (p + random_float())/n, (float) (q + random_float())/n ));
}

Vec2 Jittered::sample_unit_square(){
    return Sampler::sample_unit_square();
}

Vec3 Jittered::sample_hemisphere(){
    return Sampler::sample_hemisphere();
}
