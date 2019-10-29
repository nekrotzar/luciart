#include "triangle.h"

Triangle::Triangle(){
    p1 = Vec3(0,0,0);
    p2 = Vec3(0,1,0);
    p3 = Vec3(1,0,0);
    normal = Vec3(0,0,1);
    compute_bounding_box();
}	

Triangle::Triangle(const Vec3& a, const Vec3& b, const Vec3& c, const Material &m){
    p1 = a;
    p2 = b;
    p3 = c;
    normal = -((p3 - p1).cross(p2 - p1)).normalise();
    material = m;
    compute_bounding_box();
}

void Triangle::compute_bounding_box(){
    Vec3 min = Vec3(INFINITY, INFINITY, INFINITY);
    Vec3 max = Vec3(-INFINITY, -INFINITY, -INFINITY);
    
    std::vector<Vec3> p;
    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    
    for (int i = 0; i < p.size(); i++) {
        if(p[i].x < min.x)
            min.x = p[i].x;
        if(p[i].y < min.y)
            min.y = p[i].y;
        if(p[i].z < min.z)
            min.z = p[i].z;
        if(p[i].x > max.x)
            max.x = p[i].x;
        if(p[i].y > max.y)
            max.y = p[i].y;
        if(p[i].z > max.z)
            max.z = p[i].z;
    }
    
    
    boundingBox.set_bounding_box(min, max);
}

bool Triangle::intersect(const Ray &ray, double &tmin, Intersection &intersection){
    //Moller-Trumbore algorithm
    
    if(mailBox.ray_id == ray.rayID){
        if(mailBox.t < 0)
            return false;
        
        tmin = mailBox.t;
        intersection.normal = normal;
        return true;
    }
    
    mailBox.ray_id = ray.rayID;
    mailBox.t = -1;
    
    /* Vectors for two edges sharing one vertex */
    Vec3 edge1 = p2 - p1;
    Vec3 edge2 = p3 - p1;
    
    /* Distance from choosen vertix to ray origin */
    Vec3 s = ray.position - p1;
    
    /* Calculate determinant */
    Vec3 h = (ray.direction).cross(edge2);
    double denom = edge1.dot(h);
    
    /* If determinant is close to 0, the ray does not intersect the triangle. */
    if (denom < EPSILON && denom > -EPSILON) {
        return false;
    }
    
	double inv_denom = 1.0 / denom;
	double beta = s.dot(h) * inv_denom;

	if (beta < 0.0 || beta > 1.0)
		return false;
    
    Vec3 q = s.cross(edge1);

	double gamma = (ray.direction).dot(q) * inv_denom;

	if (gamma < 0.0 || beta + gamma > 1.0)
		return false;
    
    double t = edge2.dot(q) * inv_denom;

    if (t > EPSILON){
        mailBox.t = t;
        tmin = t;
        intersection.normal = normal;
        return true;
    }
    
    return false;
}

