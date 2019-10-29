#ifndef constants_h
#define constants_h

#define FILENAME "test_dof.nff"     /**< Default file name. */

#define POINT_BY_POINT  0           /**< Render scene point by point.*/
#define LINE_BY_LINE    1           /**< Render scene line by line. */
#define FULL_FRAME      2           /**< Render scene full frame. */
#define WRITE_FILE      3           /**< Save render to image file. */

#define ADAPTIVE_THRESHOLD 0.3      /**< Adaptive threshold. */
#define ADAPTIVE_MAX_DEPTH 3        /**< Maximum adaptive recursion depth. */
#define MAX_DEPTH 6                 /**< Maximum ray recursion depth. */
#define EPSILON 1e-10                /**< Floating point bias. */

#define SELECTIVE 0                 /**< Sampling type. */
#define ADAPTIVE  1                 /**< Sampling type. */

#define GRID_M_FACTOR 2.0           /**< Grid multiplying factor. */

#define LENS_TYPE 1                 /**< Lens surface type. (0 - disk, 1- square) */
#define LENS_RADIUS 0.25            /**< Lens camera radius. */
#define FOCAL_DISTANCE 3.4          /**< Camera focal distance. */
#define ZOOM 1.0                    /**< Camera zoom factor. */

#define SQUARE 0
#define DISK 1

#define R_COSINE_POWER 10           /**< Specular reflection cosine power. Smaller values translate into distorted reflections */

#endif /* constants_h */
