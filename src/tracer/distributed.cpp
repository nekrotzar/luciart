#include "distributed.h"

DistributedTracer::DistributedTracer(Scene * s) : Tracer(s) {}

Color DistributedTracer::shade(const Intersection& closest){
    Color mat = closest.material.color;
    Color color = (mat * closest.material.ambient);
    
    for (auto light: scene->GetLights()) {
        Color average;
        
        for(int i = 0; i < light->num_samples(); i++){
            
            Vec3 a = light->sample_position();
            Vec3 l = (a - closest.hitpoint).normalise();
            
            float lambert = l.dot(closest.normal);
            if (lambert > 0.0) {
                
                /* Cast shadow ray taking in account the floating point precision */
                Ray shadowRay = Ray(closest.hitpoint + l * EPSILON, l);
                
                if (!scene->inShadow(shadowRay)) {
                    
                    // Blinn-Phong specular reflection
                    Vec3 v = (scene->GetCamera()->eye - closest.hitpoint).normalise();
                    Vec3 h = (l + v).normalise();
                    float intSpec = clamp(h.dot(closest.normal), 0.0, 1.0);
                    
                    Color lightColor = light->color * light->intensity;
                    Color diffuseColor = lightColor * lambert * (mat * closest.material.diffuse);
                    Color specularColor = lightColor * lambert * (closest.material.specular * pow(intSpec, closest.material.shininess));
                    
                    average += (specularColor + diffuseColor);
                } else {
                    average += Color();
                }
            }
        }
        average = (average / light->num_samples());
        color += average;
    }
    
    return color;
}

Color DistributedTracer::color_pixel(const int x, const int y){
    Color color = Color();
    
    // Check if it uses anti-aliasing.
    if(aliasing_sampler){
        
        // Check the type of anti-aliasing, either non-adaptive or adaptive.
        switch(aliasing_sampler->type){
            case SELECTIVE :
                color = selective_color_pixel(x, y);
                break;
            case ADAPTIVE :
            {
                int n = pow(2, ADAPTIVE_MAX_DEPTH);
                std::vector<Color*> colors((n+1)*(n+1)); // Allocate (n + 1)(n + 1) colors of the subpixels.
                color = adaptive_color_pixel(x, y, colors, 0, 0);
            }
                break;
            default:
                std::cout << "Invalid sampling type." << std::endl;
                break;
        }
    } else {
        // Check if it uses DOF
        if(scene->camera->sampler){
            int num_samples = scene->camera->sampler->num_samples;
            for (int i = 0; i < num_samples ; i++) {
                Ray ray = scene->camera->calculatePrimaryRay(x, y);
                color += rayTracing(ray, 1, 1.0 );
            }
            color = color / num_samples;
        } else {
            Ray ray = scene->camera->calculatePrimaryRay(x, y);
            color += rayTracing(ray, 1, 1.0 );
        }

    }
    
    return color;
}

Color DistributedTracer::selective_color_pixel(const int x, const int y){
    Color color = Color();
	Ray ray;

    // Get pixel color for selective sampling
    for (int i = 0; i < aliasing_sampler->num_samples; i++) {
        Vec2 sample = aliasing_sampler->sample_unit_square();

        ray = scene->camera->calculatePrimaryRay(x + sample.x, y + sample.y);
        
        color += rayTracing(ray, 1, 1.0 );
    }
    
    // Average color of pixel samples
    return (color / aliasing_sampler->num_samples);
}

Color DistributedTracer::adaptive_color_pixel(double x, double y, std::vector<Color*> &colors, int index, int depth){

    Color color = Color();
    
    // Adaptative supersampling -  4 corners of the pixel or sub-pixel.
	std::vector<Color> corners(aliasing_sampler->num_samples);
    std::vector<int> indices(aliasing_sampler->num_samples);
    
    int denom = pow(2,depth);
    int n = pow(2, ADAPTIVE_MAX_DEPTH);
    
    indices[0] = index;                                     // Left-bottom
    indices[1] = index + (n / denom);                       // Right-bottom
    indices[2] = index + ((n + 1) * n) / denom;             // Left-top
    indices[3] = index + (((n + 1) * (n + 1)) - 1) / denom; // Right-top
    
    // Calculate colors for pixel/subpixel corners
    for( int i = 0; i < aliasing_sampler->num_samples; ++i){
        
        
        // Check if color was previously calculated
        if(colors[indices[i]] == nullptr){
            Vec2 sample = aliasing_sampler->samples[i];
            double new_x = (double)(x + (sample.x / denom));
            double new_y = (double)(y + (sample.y / denom));
            
            Ray ray = scene->camera->calculatePrimaryRay(new_x, new_y);
            corners[i] = rayTracing(ray, 1, 1.0);
            colors[indices[i]] = new Color(corners[i]);
            
        } else {
            float r = colors[indices[i]]->r;
            float g = colors[indices[i]]->g;
            float b = colors[indices[i]]->b;
            corners[i] = Color(r,g,b);
        }
        
    }
    
    // If one of the corners is different enough, calculate trace subpixel colors.
    if((!checkThreshold(corners, ADAPTIVE_THRESHOLD)) && (depth < ADAPTIVE_MAX_DEPTH)){
        denom *= 2;
        
        for (int k = 0; k < aliasing_sampler->num_samples; ++k){
            Vec2 sample = aliasing_sampler->samples[k];

            double new_x = (double)(x + (sample.x / denom));
            double new_y = (double)(y + (sample.y / denom));
            
            corners[k] = adaptive_color_pixel(new_x, new_y, colors, (indices[k] / 2) , depth + 1);
        }
    }
    
    // Add 4 corners to color
    for (int i = 0; i < aliasing_sampler->num_samples; i++){
        color += corners[i];
    }
    
    color = (color / aliasing_sampler->num_samples);
    
    return color ;
}

bool DistributedTracer::checkThreshold(std::vector<Color> corners, const float threshold){
    for (int i = 0; i < aliasing_sampler->num_samples; i++) {
        for (int j = i+1; j < aliasing_sampler->num_samples; j++) {
            if (corners[i].distance(corners[j]) > threshold)
                return false;
        }
    }
    return true;
}
