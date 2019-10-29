#ifdef __APPLE__
    #include "pinhole.h"
#else
    #include "camera/pinhole.h"
#endif

PinholeCamera::PinholeCamera() : Camera() {}
PinholeCamera::PinholeCamera(Vec3 eye, Vec3 at, Vec3 up, int x, int y, float angle, float hither) : Camera(eye, at, up, x, y, angle, hither) {}

Ray PinholeCamera::calculatePrimaryRay(double x, double y){
    
    // Ray at the left bottom corner of the square pixel
    Vec3 d = z_e * (-d_f) + (y_e) * height * ((y / (float) resY) - (0.5)) + x_e * width * ((x / (float) resX) - (0.5));
    
    return Ray(eye, d.normalise());
}
