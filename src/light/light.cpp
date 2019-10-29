#ifdef __APPLE__
    #include "light.h"
#else
    #include "light/light.h"
#endif

Light::Light(){
    position = Vec3();
    color = Color(1.0, 1.0, 1.0);
    intensity = 1.0;
}

Light::Light(float x, float y, float z, float r, float g, float b){
    position = Vec3(x,y,z);
    color = Color(r,g,b);
    intensity = 1.0;
}

Light::Light(const Vec3 &p, const Color &c){
    position = p;
    color = c;
    intensity = 1.0;
}

void Light::set_area(Area * a){
    area = a;
}

int Light::num_samples(){
    return area->sampler->num_samples;
}

Vec3 Light::sample_position(){
    return area->sample();
}
