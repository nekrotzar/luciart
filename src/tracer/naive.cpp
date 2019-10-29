#ifdef __APPLE__
    #include "naive.h"
#else
    #include "tracer/naive.h"
#endif

NaiveTracer::NaiveTracer(Scene * s) : Tracer(s) {}

Color NaiveTracer::color_pixel(const int x, const int y){
    Ray ray = scene->camera->calculatePrimaryRay(x, y);
    Color color = rayTracing(ray, 1, 1.0 );
    return color;
}

Color NaiveTracer::shade(const Intersection& closest){
    Color mat = closest.material.color;
    Color color = (mat * closest.material.ambient);
    
    for (auto light: scene->GetLights()) {
        Vec3 l = (light->position - closest.hitpoint).normalise();
        
        float lambert = l.dot(closest.normal);
        
        if (lambert > 0.0) {
            
            /* Cast shadow ray taking in account the floating point precision */
            Ray shadowRay = Ray(closest.hitpoint + l * EPSILON, l);
            
            if (!scene->inShadow(shadowRay)) {
                
                // Blinn-Phong specular reflection
                Vec3 v = (scene->GetCamera()->eye - closest.hitpoint).normalise();
                Vec3 h = (l + v).normalise();
                float intSpec = clamp(h.dot(closest.normal), 0.0, 1.0);
                
                //Phong specular reflection
                //Vec3 r = l.reflect(closest.normal);
                //float intSpec = r.dot(ray.direction);
                
                Color lightColor = light->color * light->intensity;
                Color diffuseColor = lightColor * lambert * (mat * closest.material.diffuse);
                Color specularColor = lightColor * lambert * (closest.material.specular * pow(intSpec, closest.material.shininess));
                
                color += (specularColor + diffuseColor);
            }
        }
    }
    
    return color;
}
