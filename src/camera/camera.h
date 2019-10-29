#ifndef camera_h
#define camera_h

#include "vec3.h"
#include "ray.h"

#include "utility/constants.h"
#include "sampler/sampler.h"

#define _USE_MATH_DEFINES

#define DEFAULT_WIDTH 256
#define DEFAULT_HEIGHT 256
#define DEFAULT_ANGLE 45
#define DEFAULT_HITHER 0

/**
 * @class Camera.
 * Camera defined by eye, at and up vectors.
 */
class Camera {
public:

    Vec3 eye;       /**< The eye location in XYZ. */
    Vec3 at;        /**< Direction of the camera as an XYZ vector. */
    Vec3 up;        /**< Direction up from the camera as an XYZ vector. */
    
    float angle;    /**< The field of view angle of the camera, in radians. */
    float hither;   /**< Distance of the near plane from the eye. */
    float yon;      /**< Distance of the far plane from the eye. */
    
    int resX;       /**< Horizontal resolution in pixels. */
    int resY;       /**< Vertical resolution in pixels. */
    
    float width;    /**< Width of the projection window. */
    float height;   /**< Height of the projection window. */
    
    float d_f;      /**< Distance from the eye to center of the frame. */
    
    Vec3 y_e;       /**< Orthnormal vector of projection frame, u. */
    Vec3 x_e;       /**< Orthnormal vector of projection frame, v. */
    Vec3 z_e;       /**< Orthnormal vector of projection frame, n. */
    
    Sampler * sampler;  /**< Depth of field sampling technique. */
    int type;           /**< Type of area sampling. (disk - true, square - false) */


    /**
     * Default constructor. Uses default values for everything.
     */
    Camera();
    
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
    Camera(Vec3 eye, Vec3 at, Vec3 up, int x, int y, float angle, float hither);
    
    /**
     * Initiatize camera frame dimensions and vectors.
     *
     */
    virtual void init();
    
    /**
     * Get image resolution width.
     */
    virtual int GetResX(void);
    
    /**
     * Get image resolution height.
     */
    virtual int GetResY(void);
    
    /**
     * Calculate ray from a point in the view plane.
     * @param x Pixel point x coordinate.
     * @param y Pixel point y coordinate.
     * @return Ray that hits the point from the camera position.
     */
    virtual Ray calculatePrimaryRay(double x, double y) ;
    
    /**
     * Set sampling type for depth of field.
     * (used in thin lens camera)
     * @param s Sampling method.
     */
    void set_dof_sampler(Sampler * s);
    
    /**
     * Set the lens area type.
     * @param type Area type code. (0 - square, 1 - disk)
     */
    void set_lens_type(int type);
};

#endif /* camera_h */
