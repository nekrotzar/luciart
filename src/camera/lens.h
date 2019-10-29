#ifndef lens_h
#define lens_h

#include "camera.h"
#include "sampler/random.h"


/**
 * @class LensCamera.
 * Camera defined by an area (lens radius) and a sampling method.
 */
class LensCamera : public Camera
{
public:
    float zoom;                        /**< Zoom factor */
    float radius;                      /**< Radius of the lens disk. */
    float focusDistance;               /**< Distance from the lens to the focal plane. */
    
    /**
     * Default constructor. Uses default values for everything.
     */
    LensCamera();
    
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
     * @param radius Lens radius.
     * @param focus Focus distance.
     */
    LensCamera(Vec3 eye, Vec3 at, Vec3 up, int x, int y, float angle, float hither, float radius, float focus, float zoom);

    /**
     * Calculate ray from a point in the view plane.
     * @param x Pixel point x coordinate.
     * @param y Pixel point y coordinate.
     * @return Ray that hits the point from the camera position.
     */
    Ray calculatePrimaryRay(double x, double y);
};


#endif /* lens_h */
