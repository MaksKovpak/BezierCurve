#pragma once

#include <SFML/Graphics.hpp>
#include "BezierCurve.hpp"
#include <vector>

using namespace sf;

class BezierPath  {
	private:
		std::vector<BezierCurve> curves;
		std::vector<Vector2f> points;
		std::vector<CircleShape> circles;

	public:
		BezierPath(std::vector<Vector2f> thePoints);

		std::vector<CircleShape> draw(RenderWindow& window);
};

