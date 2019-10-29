#ifndef utility_h
#define utility_h

#include <math.h>

/*
 * Clamps number between two values.
 * @param x Value to be clamped.
 * @param min Mininum value.
 * @param max Maximum value.
 * @return Clamped value between minimum and maximum.
 */
double clamp(const double x, const double min, const double max);

/**
 * Set random seed.
 * @param seed Seed.
 */
void set_seed(const int seed);

/**
 * Returns random integer.
 * @return Random integer.
 */
int random_int();

/**
 * Returns random float.
 * @return Random float between 0 and 1.
 */
float random_float();


inline double clamp(const double x, const double min, const double max){
    return (x < min ? min: (x > max ? max : x));
}

inline void set_seed(const int seed){
    srand(seed);
}

inline int random_int(){
    return rand();
}

inline float random_float(){
    return (float) random_int() / RAND_MAX;
}


#endif /* utility_h */
