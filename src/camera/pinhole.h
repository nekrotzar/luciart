#ifndef pinhole_h
#define pinhole_h

#include "camera.h"

/**
 * @class PinholeCamera.
 * Camera defined by a single point (eye), at and up vectors.
 */
class PinholeCamera : public Camera {
public:
    /**
     * Default constructor. Uses default values for everything.
     */
    PinholeCamera();
    
    /**
     * Constructor.
     *
     * @param eye The centre of projection as a vector.
     * @param at The point the camera is looking at.
     * @param up The direction that must be up for the camera,
     * as a vector.
     * @param x The width of the image to produce.
     * @param y The height of the image to produce.
     * @param angle The camera's viewing angle in radians.
     * @param hither The distance from the eye to the hither plane.
     */
    PinholeCamera(Vec3 eye, Vec3 at, Vec3 up, int x, int y, float angle, float hither);
    
    /**
     * Calculate ray from a point in the view plane.
     * @param x Pixel point x coordinate.
     * @param y Pixel point y coordinate.
     * @return Ray that hits the point from the camera position.
     */
    Ray calculatePrimaryRay(double x, double y);

};

#endif /* pinhole_h */
