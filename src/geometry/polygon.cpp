#ifdef __APPLE__
    #include "polygon.h"
#else
    #include "geometry/polygon.h"
#endif

Polygon::Polygon(){
    numVertices = 0;
    material = Material();
    compute_bounding_box();
}

Polygon::Polygon(int n, std::vector<Vec3> &v , const Material &m){
    numVertices = n;
    vertices = v;
    material = m;
    plane = Plane(vertices[0], vertices[1], vertices[2], m);
    compute_bounding_box();

}

void Polygon::compute_bounding_box(){
    Vec3 min = Vec3(INFINITY, INFINITY, INFINITY);
    Vec3 max = Vec3(-INFINITY, -INFINITY, -INFINITY);
    
    for(auto vertex: vertices){
        if(vertex.x < min.x)
            min.x = vertex.x;
        if(vertex.y < min.y)
            min.y = vertex.y;
        if(vertex.z < min.z)
            min.z = vertex.z;
        if(vertex.x > max.x)
            max.x = vertex.x;
        if(vertex.x > max.y)
            max.y = vertex.y;
        if(vertex.z > max.z)
            max.z = vertex.z;
    }
    boundingBox.set_bounding_box(min, max);
}

bool Polygon::intersect(const Ray &ray, double& tmin, Intersection &intersection){
    // Badouel ray-polygon intersection
    
    Intersection temp;
    double t;
    
    // Intersect with the embedding plane
    if (plane.intersect(ray, t, temp)) {

        Vec3 hitpoint = ray.position + ray.direction * t;
        
        // Calculate dominant axis.
        double max = fmax(fmax(fabs(temp.normal.x), fabs(temp.normal.y)), fabs(temp.normal.z));
        int u, v;
        
        
        if (fabs(temp.normal.x) == max) {
            u = 1;
            v = 2;
        } else if (fabs(temp.normal.y) == max) {
            u = 0;
            v = 2;
        } else {
            u = 0;
            v = 1;
        }
        
        // TODO: Optimize this. Set dominant coordinant to zero instead of creating new vertices.
        // Get u,v vertices
        std::vector<Vec2> projVertices;
        for (int i = 0; i < vertices.size(); i++) {
            // Center the 2D vertices around the hit point.
            projVertices.push_back(Vec2(vertices[i][u] - hitpoint[u], vertices[i][v] - hitpoint[v]));
        }
        
        // Odd-even parity rule (Haine's algorithm)
        int parity = 0;
        int sign, nextsign;
        
        
        for (int i = 0; i < numVertices ; i++) {
            double u = projVertices[i].x;
            double u_next = projVertices[(i+1) % numVertices].x;
            double v = projVertices[i].y;
            double v_next = projVertices[(i+1) % numVertices].y;
            
            
            // Check y coordinates signs.
            if (v >= 0)
                sign = +1;
            else
                sign = -1;
            
            if (v_next >= 0)
                nextsign = +1;
            else
                nextsign = -1;
            
            // If the y-coordinates has the same sign, there is no interesection
            if (sign != nextsign) {
                
                // Check if x coordinate are both positive.
                if ((v > 0) && (v_next > 0))
                    parity++;
                
                // Check if x coordinates differ in sign.
                if ((u > 0) || (u_next > 0)) {
                    // Calculate the intersection
                    double xinter = u - v * (u_next - u) / (v_next - v);
                    
                    if (xinter > 0) {
                        parity++;
                    }
                }
            }
        }
        
        if ((parity % 2) == 1) {
            intersection.normal = temp.normal;
            tmin = t;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
