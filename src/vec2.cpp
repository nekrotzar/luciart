#include "vec2.h"

Vec2::Vec2(){
    x = 0.0;
    y = 0.0;
}

Vec2::Vec2(double xv, double yv){
    x = xv;
    y = yv;
}

Vec2::Vec2(const Vec2& v){
    x = v.x;
    y = v.y;
}

Vec2& Vec2::operator=(const Vec2& v){
    if (this == &v) {
        return (* this);
    }
    
    x = v.x;
    y = v.y;
    return (* this);
}

bool Vec2::operator==(const Vec2& v){
    return (x == v.x && y == v.y);
}


Vec2 Vec2::operator+(const Vec2& v) const {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}

Vec2 Vec2::operator*(double f) const {
    return Vec2(x * f, y * f);
}

Vec2 Vec2::operator/(double f) const {
    return Vec2(x / f, y / f);
}

double Vec2::dot(const Vec2& v) const {
    return (x * v.x + y * v.y);
}

Vec2 Vec2::normalise(){
    return Vec2(x / length(), y / length());
}

double Vec2::length(){
    return fabs(sqrt(pow(x, 2) + pow(y, 2)));
}
