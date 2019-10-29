#include "vec3.h"

Vec3::Vec3(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vec3::Vec3(double xv, double yv, double zv){
    x = xv;
    y = yv;
    z = zv;
}

Vec3::Vec3(const Vec3& v){
    x = v.x;
    y = v.y;
    z = v.z;
}

Vec3& Vec3::operator=(const Vec3& v){
    if (this == &v) {
        return (* this);
    }
    
    x = v.x;
    y = v.y;
    z = v.z;
    return (* this);
}

double Vec3::operator[](const int index) const {
    switch (index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        default:
            printf("Invalid index number.");
            exit(1);
    }
}

bool Vec3::operator==(const Vec3& v){
    return (x == v.x && y == v.y && z == v.z);
}

Vec3 Vec3::operator+(double f) const {
    return Vec3(x + f, y + f, z + f);
}

Vec3 Vec3::operator-(double f) const {
    return Vec3(x - f, y - f, z - f);
}

Vec3 Vec3::operator+(const Vec3& v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator*(double f) const {
    return Vec3(x * f, y * f, z * f);
}

Vec3 Vec3::operator/(double f) const {
    return Vec3(x / f, y / f, z / f);
}

Vec3 Vec3::cross(const Vec3& v) const {
    return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vec3 Vec3::reflect(const Vec3& v) const {
    return Vec3(((*this) - v * (*this).dot(v) * 2));
}

double Vec3::dot(const Vec3& v) const {
    return (x * v.x + y * v.y + z * v.z);
}

Vec3 Vec3::normalise(){
    return Vec3(x / length(), y / length(), z / length() );
}

double Vec3::length(){
    return fabs(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

Vec3 Vec3::inverse(){
	return Vec3(1/x,1/y,1/z);
}

