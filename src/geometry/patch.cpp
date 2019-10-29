#ifdef __APPLE__
    #include "patch.h"
#else
    #include "geometry/patch.h"
#endif

PolygonPatch::PolygonPatch(){
    Polygon();
}

PolygonPatch::PolygonPatch(int num, std::vector<Vec3> &v, std::vector<Vec3> &n, const Material &m){
    Polygon(num, v ,m);
    normals = n;
}

bool PolygonPatch::intersect(const Ray &ray, double& tmin ,Intersection &intersection){
    //TODO: ray-polygon patch intersection.
    return false;
}

void PolygonPatch::compute_bounding_box(){}
