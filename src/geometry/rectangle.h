#ifndef rectangle_h
#define rectangle_h

#include "geometry/area.h"
#include "sampler/sampler.h"
#include "sampler/regular.h"

#include "vec3.h"
#include "vec2.h"


namespace geometry
{
	/**
	 * @class Rectangle.
	 * Rectangle area to sample light positions.
	 */
	class Rectangle : public Area {
	public:
		Vec3 a; /**< Edge of rectangle. */
		Vec3 b; /**< Edge of rectange. */

		/**
		 * Default rectangle constructor sets a unit square at the position (0,0,0).
		 */
		Rectangle();

		/**
		 * Constructor sets the rectangle position and sets the edges.
		 * @param p Position of the rectangle.
		 * @param a Edge along the x axis.
		 * @param b Edge along the y axis.
		 * @param s Sampling method.
		 */
		Rectangle(const Vec3 &p, const Vec3 &a, const Vec3 &b, Sampler * s);

		/**
		 * Get a sample position inside the rectangle.
		 * @return Sampled position.
		 */
		virtual Vec3 sample();
	};
}
#endif /* rectangle_h */
