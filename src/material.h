#ifndef material_h
#define material_h

#include "color.h"

/**
 * @class Material.
 * Material with color and Blinn-Phong components.
 */
class Material{
public:
    Color color;            /**< Color of the material in RGB. */
    float ambient;          /**< Ambient component of the material. */
    float diffuse;          /**< Diffuse component of the material. */
    float specular;         /**< Specular component of the material. */
    float shininess;        /**< Phong cosine power for the highlights. */
    float transmittance;    /**< Contribution of the transmitting ray. */
    float ior;              /**< Index of refraction. */
    
    /**
     * Default material constructor sets color to black and Blinn-Phong components to zero.
     */
    Material();
    
    /**
     * Contructor
     * @param c Color copy.
     * @param kd diffuse component value of the material.
     * @param ks specular component value of the material.
     * @param shine shininess component value of the material.
     * @param t ray transmittion fraction contribution.
     * @param index index of refraction.
     */
    Material(const Color &c, float kd, float ks, float shine, float t, float index);
};

#endif /* material_h */
