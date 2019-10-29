#include "camera/lens.h"

LensCamera::LensCamera(Vec3 eye, Vec3 at, Vec3 up, int x, int y, float angle, float hither, float r, float focus, float z)
	: Camera(eye, at, up, x, y, angle, hither)
{
    radius = r;
    focusDistance = focus;
    zoom = z;
}

Ray LensCamera::calculatePrimaryRay(double x, double y){
    float ratio = focusDistance / d_f;
    
    //Point where it hits the focal plane.
    Vec2 centerPoint;
    centerPoint.x = (((x / (float) resX) - 0.5) * width) * ratio / zoom;
    centerPoint.y = (((y / (float) resY) - 0.5) * height) * ratio / zoom;
    
    Vec2 samplePoint;
    
    if(type)
        samplePoint = sampler->sample_unit_disk();
    else
        samplePoint = sampler->sample_unit_square();
    
    Vec2 lensPoint = samplePoint * radius;
    
    Vec3 origin = eye +  (x_e * lensPoint.x) + (y_e * lensPoint.y);
    Vec3 direction = x_e * (centerPoint.x - lensPoint.x) + y_e * (centerPoint.y - lensPoint.y) - z_e * focusDistance;
    
    return Ray(origin, direction.normalise());
}
