#include "color.h"

Color::Color(){
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Color::Color(float red, float green, float blue){
    r = red;
    g = green;
    b = blue;
}

Color::Color(const Color &c){
    r = c.r;
    g = c.g;
    b = c.b;
}

Color Color::operator=(const Color &c){
    r = c.r;
    g = c.g;
    b = c.b;
    return * this;
}

Color Color::operator+=(const Color &c){
    r += c.r;
    g += c.g;
    b += c.b;
    return * this;
}

Color Color::operator*=(float f){
    r *= f;
    g *= f;
    b *= f;
    return * this;
}

Color Color::operator+(const Color &c){
    return Color(r + c.r, g + c.g, b + c.b);
}

Color Color::operator*(const Color &c){
    return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::operator*(float f){
    return Color(r * f, g * f, b * f);
}

Color Color::operator/(float f){
    return Color(r / f, g / f, b / f);
}

Color Color::operator^(float f){
    return Color(pow(r,f) , pow(g,f), pow(b,f));
}

float Color::distance(const Color &c){
    return (fabs(r - c.r) + fabs(g - c.g) + fabs(b - c.b));
}
