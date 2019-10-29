#include "material.h"

Material::Material(){
    color = Color();
    ambient = 0.0;
    diffuse = 0.0;
    specular = 0.0;
    shininess = 0.0;
    transmittance = 0.0;
    ior = 0.0;
}

Material::Material(const Color &c, float kd, float ks, float shine, float t, float index){
    color = c;
    ambient = 0.0;
    diffuse = kd;
    specular = ks;
    shininess = shine;
    transmittance = t;
    ior = index;
}
