#ifndef vec2_h
#define vec2_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @class Vec2.
 * Vector in XY.
 */
class Vec2 {
public:
    double x;    /**< x component value of the vector. */
    double y;    /**< y component value of the vector. */
    
    /**
     * Default vector constructor sets to (0,0).
     */
    Vec2();
    
    /**
     * Constructor sets the vector values for each component.
     * @param x x component value.
     * @param y y component value.
     */
    Vec2(double x, double y);
    
    /**
     *  Contructor
     *  @param v Vec3 copy.
     */
    Vec2(const Vec2 &v);
    
    /**
     * Assignment operator
     * @param v Right hand side vector.
     * @return This vector.
     */
    Vec2& operator=(const Vec2& v);
    
    /**
     * Comparison operator
     * @param v Right hand side vector.
     * @return Return true if every component are equal.
     */
    bool operator==(const Vec2& v);
    
    /**
     * Addition operator
     * @param v Right hand side vector.
     * @return Sum of the two vectors components.
     */
    Vec2 operator+(const Vec2& v) const ;
    
    /**
     * Subtraction operator
     * @param v Right hand side vector.
     * @return Difference of the two vectors components.
     */
    Vec2 operator-(const Vec2& v) const;
    
    /**
     * Negation operator
     * @return Negated vector.
     */
    Vec2 operator-() const;
    
    /**
     * Scalar multiplication operator
     * @param f Right hand side scalar.
     * @return Scaled vector.
     */
    Vec2 operator*(const double f) const;
    
    /**
     * Scalar division operator
     * @param f Right hand side scalar.
     * @return The vector resulting from a scalar division.
     */
    Vec2 operator/(const double f) const ;
    
    /**
     * Calculates the dot product between two vectors.
     * @param v Right side vector of dot product operation.
     * @return The value of the dot product.
     */
    double dot(const Vec2& v) const;
    
    /**
     * Calculates the normalised vector.
     * @return The normalised vector.
     */
    Vec2 normalise();
    
    /**
     * Calculates the length of a vector.
     * @return The length of the vector.
     */
    double length();
};

#endif /* vec2_h */

