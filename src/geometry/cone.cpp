#include "cone.h"

Cone::Cone(){
    base = Vec3(0.0,0.0,0.0);
    apex = Vec3(1.0,1.0,1.0);
    baseRadius = 1.0;
    apexRadius = 1e-3;
    material = Material();
}

Cone::Cone(const Vec3 &b, const Vec3 &a, float bRadius, float aRadius, const Material &m){
    base = b;
    apex = a;
    baseRadius = bRadius;
    apexRadius = aRadius;
    material = m;
}

void Cone::compute_bounding_box(){}

bool Cone::intersect(const Ray &ray, double& tmin, Intersection &intersection){
    // TODO: ray-cone intersection

	Vec3 dir = apex - base;
	double theta = atan((baseRadius - apexRadius) / dir.length());
	double cosSqr = pow(cos(theta), 2);

	dir.normalise();


	Vec3 extendedApex = apex + dir * (apexRadius / tan(theta));



	const Vec3& A = dir;
	const Vec3& D = ray.direction;
	const Vec3 E = ray.position - extendedApex;



	double c2 = pow(A.dot(D), 2) - cosSqr;
	double c1 = A.dot(D) * A.dot(E) - cosSqr * D.dot(E);
	double c0 = pow(A.dot(E), 2) - cosSqr * E.dot(E);

	double disc = c1 * c1 - c0 * c2;

	/* We ignore cases where disc == 0 / disc < 0. The former has no visible
	* impact on image quality, and the latter indicates an abscence of
	* intersections. False will be returned for both occurrences. */
	if (disc > EPSILON)
	{
		double t0 = (-c1 - sqrt(disc)) * (1 / c2);
		double t1 = (-c1 + sqrt(disc)) * (1 / c2);

		/* Note that this object is one-sided. As such, we are only interested in
		* the first intersection that is in front of the ray origin. */
		double t_final = t0;
		if (t0 < -EPSILON)
		{
			if (t1 < -EPSILON)
			{
				return false;
			}
			else
			{
				t_final = t1;
			}
		}
		else
		{
			if (t1 < t0)
			{
				t_final = t1;
			}
		}

		Vec3 point = ray.position + ray.direction * t_final;

		/* This ensures that the point is within the stated apex & base
		* coordinates. */
		if ( ( (point - apex).dot(A) <= -EPSILON) && ((point - base).dot(A) >= EPSILON))
		{

			/* To calculate the normal at a point, we project that point onto
			* the direction vector of the cone and add it to the apex. Now we
			* have a point on the central axis of the cone. We can simply
			* subtract this from the point on the surface to obtain the
			* normal. */
			Vec3 v = point - apex;
			Vec3 aux1 = dir.inverse() * v.dot(dir);

			Vec3 proj = dir * aux1.dot(dir);
			Vec3 norm = (point - (apex + proj)).normalise();

            tmin = t_final;

		
			intersection.t = tmin;
			intersection.hitpoint = point;
			intersection.normal = norm;

			return true;
		}
	}
	
		return false;
	

}

