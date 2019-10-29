#include "rectangle.h"

namespace geometry
{
	Rectangle::Rectangle(){
		position = Vec3(0, 0, 0);
		a = Vec3(1, 0, 0);
		b = Vec3(0, 1, 0);
		normal = Vec3(0, 0, 1);
		sampler = new Regular(1);
	}

	Rectangle::Rectangle(const Vec3 &p, const Vec3 &a1, const Vec3 &b1, Sampler * s) {
        a = a1;
        b = b1;
		position = p;
		sampler = s;
		normal = (a.cross(b)).normalise();
	}

	Vec3 Rectangle::sample() {
		Vec2 sample = sampler->sample_unit_square();

		// Move the position to the bottom corner of the rectangle
		Vec3 temp = position - (a / 2) - (b / 2);

		return (temp + a * sample.x + b * sample.y);
	}
}
