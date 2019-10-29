#ifdef __APPLE__
    #include "camera.h"
#else
    #include "camera/camera.h"
#endif

Camera::Camera(){    
    eye = Vec3(0,0,0);
    at = Vec3(0,0,-1);
    up = Vec3(0,1,0);
    resX = DEFAULT_WIDTH;
    resY = DEFAULT_HEIGHT;
    angle = DEFAULT_ANGLE;
    hither = DEFAULT_HITHER;
    yon = INFINITY;
    init();
}

Camera::Camera(Vec3 eyeVec, Vec3 atVec, Vec3 upVec, int x, int y, float ang, float hith){
    eye = eyeVec;
    at = atVec;
    up = upVec;
    resX = x;
    resY = y;
    angle = ang;
    hither = hith;
    yon = INFINITY;
    init();
}

void Camera::init(){
    d_f = (eye - at).length();
    
    z_e = (eye - at).normalise();
    x_e = (up.cross(z_e)).normalise();
    y_e = z_e.cross(x_e);
    
    height = 2 * d_f * tan((angle * M_PI / 180.0) / 2);
    width = (resX / resY) * height;
}

int Camera::GetResX(void){return resX;}
int Camera::GetResY(void){return resY;}

Ray Camera::calculatePrimaryRay(double x, double y){
    return Ray();
}

void Camera::set_dof_sampler(Sampler * s){
    sampler = s;
    
    if(type == DISK && (s != NULL))
        sampler->map_samples_to_unit_disk();
}

void Camera::set_lens_type(int t){
    type = t;
}

