#ifndef color_h
#define color_h

#include <math.h>

/**
 * @class Color.
 * RGB color.
 */
class Color {

public:
    float r;    /**< Red component value of the color. */
    float g;    /**< Green component value of the color. */
    float b;    /**< Blue component value of the color. */

    /**
     * Default color constructor sets the color to black.
     */
    Color();
    
    /**
     * Constructor sets the color values for each component.
     * @param r Red color intensity.
     * @param g Green color intensity.
     * @param b Blue color intensity.
     */
    Color(float r, float g, float b);
    
    /**
     *  Contructor
     *  @param c Color copy.
     */
    Color(const Color& c);
    
    /**
     * Assignment operator
     * @param c Right hand side color.
     * @return This color.
     */
    Color operator=(const Color& c);
    
    /**
     * Increment operator
     * @param c Right hand side color.
     * @return This color added to the right hand side color.
     */
    Color operator+=(const Color& c);
    
    /**
     * Addition operator
     * @param c Right hand side color.
     * @return This color added to the right hand side color.
     */
    Color operator+(const Color& c);
    
    /**
     * Multiplication operator
     * @param f Constant value.
     * @return This color multiplied by the constant.
     */
    Color operator*=(float f);
    
    /**
     * Division operator
     * @param f Constant value.
     * @return This color divided by the constant.
     */
    Color operator/(float f);
    
    /**
     * Scalar multiplication operator
     * @param f Constant value.
     * @return This color multiplied by the constant.
     */
    Color operator*(float f);
    
    /**
     * Color multiplication operator
     * @param c Color.
     * @return This color multiplied by the other color components.
     */
    Color operator*(const Color &c);
    
    /**
     *  Power operator
     *  @param f Value of power.
     *  @return This color powered by the constant.
     */
    Color operator^(float f);
    
    /**
     * Color distance
     * @param c Color
     * @return Distance between two colors.
     */
    float distance(const Color &c);
     
};

#endif /* color_h */
