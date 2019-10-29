#ifdef __APPLE__
    #include "tracer.h"
#else
    #include "tracer/tracer.h"
#endif

Tracer::Tracer(Scene * s){
    scene = s;
    aliasing_sampler = NULL;
    reflect_sampler = NULL;
}

Color Tracer::reflectionColor(const Intersection &closest, Ray ray, int depth, int RefrIndex){
    Color color;
    
    // Reflecting object if specular constant is greater than 0.
    if (closest.material.specular > 0) {
        
        // Calculate perfect mirror reflection given the normal at the intersection.
        Vec3 r = (ray.direction).reflect(closest.normal).normalise();
        
        if(reflect_sampler){
            Vec3 u = Vec3(0.00423, 1.0, 0.00764).cross(r);
            u.normalise();
            Vec3 v = u.cross(r);

            Color average;
            for (int i = 0; i < reflect_sampler->num_samples; i++){
                // Get sample from hemisphere
                Vec3 sample = reflect_sampler->sample_hemisphere();
                // Ray sampled direction.
                Vec3 newDir = u * (sample.x) + v * (sample.y) + r * (sample.z);
                
                // Check if new direction is oposite to the normal.
                if(closest.normal.dot(newDir) < 0.0)
                    newDir = u * (-sample.x) + v * (-sample.y) + r * (sample.z);
                
                Ray reflectionRay = Ray(closest.hitpoint + newDir * EPSILON, newDir);
                average +=  (rayTracing(reflectionRay, ++depth, RefrIndex) * closest.material.specular) ;
            }
            average = average / reflect_sampler->num_samples;
            color += average;
        } else {
            Ray reflectionRay = Ray(closest.hitpoint + r * EPSILON, r);
            Color reflectionColor = rayTracing(reflectionRay, ++depth, RefrIndex);
            color += (reflectionColor * closest.material.specular);
        }
    }
    return color;
}

Color Tracer::refractionColor(const Intersection &closest, Ray ray, int depth, int RefrIndex){
    Color color;
    
    // Translucid object if transmitance constant is greater than 0.
    if (closest.material.transmittance > 0) {
        
        // Cosine between ray direction and object normal at the intersection.
        float cosi = ray.direction.dot(closest.normal);
        // Refraction index of the medium
        float iorI = RefrIndex;
        // Refraction index of the material
        float iorT = closest.material.ior;
        
        Vec3 normal = closest.normal;
        
        // Check if its outside or inside the surface
        if (cosi < 0) {
            // Outside the surface; the cosine of theta should be positive.
            cosi = -cosi;
        } else {
            // Inside the surface; reverse the normal direction.
            std::swap(iorI, iorT);
            normal = -closest.normal;
        }
        
        float eta = iorI/iorT;
        float k = 1 - eta * eta * (1 - cosi * cosi);
        
        // Check critical angle
        if (k >= 0) {
            Vec3 transmit = (ray.direction * eta + normal * (eta * cosi - sqrt(k))).normalise();
            
            Ray refractionRay = Ray(closest.hitpoint + transmit * EPSILON, transmit);
            Color refractedColor = rayTracing(refractionRay, ++depth, RefrIndex);
            color += refractedColor * closest.material.transmittance;
        }
    }
    
    return color;
}

Color Tracer::rayTracing( Ray ray, int depth, float RefrIndex){
    Color color;
    
    // Get closest intersection point, if any.
    Intersection closest = scene->hit_objects(ray);
    
    if (closest.hit_status) {

        color = shade(closest);
        
        if (depth >= MAX_DEPTH) {
            return color;
        }
        
        color += reflectionColor(closest, ray, depth, RefrIndex);
        color += refractionColor(closest, ray, depth, RefrIndex);
        
    } else {
        color =  scene->GetBackground();
    }
    
    // Clamp color between 0 and 1
    color.r = clamp(color.r, 0.0, 1.0);
    color.g = clamp(color.g, 0.0, 1.0);
    color.b = clamp(color.b, 0.0, 1.0);
    
    return color;
}

void Tracer::set_reflection_sampler(Sampler *s){
    if(s){
        reflect_sampler = s;
        reflect_sampler->map_samples_to_hemisphere(R_COSINE_POWER);
    } else {
        reflect_sampler = NULL;
    }

}

void Tracer::set_aliasing_sampler(Sampler *s){
    aliasing_sampler = s;
}

