#include "BezierPath.hpp"


BezierPath::BezierPath(std::vector<Vector2f> thePoints) : points(thePoints) {
	std::vector<Vector2f> temp;

	for (size_t i = 0; i < points.size(); i++) {
		temp.push_back(points[i]);

		if (i % 3 == 0 && i != 0) {
			curves.push_back(BezierCurve(temp));
			temp.clear();

			temp.push_back(points[i]);
		}
	}

	const int CIRCLE_R = 4;

	CircleShape tempPoint;
	tempPoint.rotate(45);
	tempPoint.setOutlineColor(Color::Red);

	for (size_t i = 0; i < points.size(); i++) {
		if (i % 3 == 0) {
			tempPoint.setPointCount(4);
			tempPoint.setRadius(1.5 * CIRCLE_R);
			tempPoint.setOrigin(1.5 * CIRCLE_R, 1.5 * CIRCLE_R);
			tempPoint.setFillColor(Color(255, 0, 0));
		}
		else {
			tempPoint.setPointCount(100);
			tempPoint.setRadius(CIRCLE_R);
			tempPoint.setOrigin(CIRCLE_R, CIRCLE_R);
			tempPoint.setFillColor(Color(255, 0, 0, 100));
		}

		tempPoint.setPosition(points[i]);
		circles.push_back(tempPoint);
	}
}

std::vector<CircleShape> BezierPath::draw(RenderWindow& window) {
	for (auto& curve : curves) {
		window.draw(curve);
	}

	for (auto& circle : circles) {
		window.draw(circle);
	}

	return circles;
}
