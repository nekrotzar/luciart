#ifndef vec3_h
#define vec3_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @class Vec3.
 * Vector in XYZ.
 */
class Vec3 {
public:
    double x;    /**< x component value of the vector. */
    double y;    /**< y component value of the vector. */
    double z;    /**< z component value of the vector. */
    
    /**
     * Default vector constructor sets to (0,0,0).
     */
    Vec3();
    
    /**
     * Constructor sets the vector values for each component.
     * @param x x component value.
     * @param y y component value.
     * @param z z component value.
     */
    Vec3(double x, double y, double z);
    
    /**
     *  Contructor
     *  @param v Vec3 copy.
     */
    Vec3(const Vec3 &v);
    
    /**
     * Assignment operator
     * @param v Right hand side vector.
     * @return This vector.
     */
    Vec3& operator=(const Vec3& v);
    
    /**
     * Vector indexing.
     * @param i Index of the component.
     * @return The vector component corresponing to the index.
     */
    double operator[](const int i) const;
    
    /**
     * Comparison operator
     * @param v Right hand side vector.
     * @return Return true if every component are equal.
     */
    bool operator==(const Vec3& v);
    
    /**
     * Scalar addition operator
     * @param f Right hand side scalar.
     * @return Sum of the two vectors components.
     */
    Vec3 operator+(double f) const ;
    
    /**
     * Scalar subtraction operator
     * @param f Right hand side scalar.
     * @return Difference of the two vectors components.
     */
    Vec3 operator-(double f) const;
    
    /**
     * Vector addition operator
     * @param v Right hand side vector.
     * @return Sum of the two vectors components.
     */
    Vec3 operator+(const Vec3& v) const ;
    
    /**
     * Vector subtraction operator
     * @param v Right hand side vector.
     * @return Difference of the two vectors components.
     */
    Vec3 operator-(const Vec3& v) const;
    
    /**
     * Negation operator
     * @return Negated vector.
     */
    Vec3 operator-() const;
    
    /**
     * Scalar multiplication operator
     * @param f Right hand side scalar.
     * @return Scaled vector.
     */
    Vec3 operator*(const double f) const;
    
    /**
     * Scalar division operator
     * @param f Right hand side scalar.
     * @return The vector resulting from a scalar division.
     */
    Vec3 operator/(const double f) const ;
    
    /**
     * Calculates the cross product between two vectors.
     * @param v Right side vector of cross product operation.
     * @return The resulting vector of the cross product.
     */
    Vec3 cross(const Vec3& v) const;
    
    /**
     * Calculates the reflected vector between two vectors.
     * @param v Right side vector of reflect operation.
     * @return The reflection of this vector.
     */
    Vec3 reflect(const Vec3& v) const;
    
    /**
     * Calculates the dot product between two vectors.
     * @param v Right side vector of dot product operation.
     * @return The value of the dot product.
     */
    double dot(const Vec3& v) const;
    
    /**
     * Calculates the normalised vector.
     * @return The normalised vector.
     */
    Vec3 normalise();
    
    /**
     * Calculates the length of a vector.
     * @return The length of the vector.
     */
    double length();


	/*
	* Returns inverse Vector
	* Carefull with divisions by zero
	*@ returns 1/vec3
	*/
	Vec3 inverse();


};

#endif /* vec3_h */
