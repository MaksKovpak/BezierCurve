#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class BezierCurve : public Drawable {
	private:
		std::vector<Vector2f> points;
		const int RADIUS = 2;

	public:
		BezierCurve(std::vector<Vector2f> thePoints);

		void draw(RenderTarget& target, RenderStates states) const;
};

