#include "BezierCurve.hpp"
#include <cmath>
#include <vector>


BezierCurve::BezierCurve(std::vector<Vector2f> thePoints) : points(thePoints) {}

void BezierCurve::draw(RenderTarget& target, RenderStates states) const {
	if (points.size() != 4) return;

	CircleShape tempPoint(RADIUS, 100);
	tempPoint.setFillColor(Color::Black);
	tempPoint.setOrigin(RADIUS, RADIUS);

	std::vector<Vector2f> P = points;

	float t = 0.0;

	VertexArray arr(Lines);

	for (size_t i = 0; i < 4; i++) {
		arr.append(Vertex(points[i], Color(0, 0, 255, 100)));
	}

	target.draw(arr);

	while (t <= 1.0) {
		Vector2f xy = Vector2f(
			pow(1 - t, 3) * P[0].x + 3 * t * pow(1 - t, 2) * P[1].x + 3 * t * t * (1 - t) * P[2].x + pow(t, 3) * P[3].x,
			pow(1 - t, 3) * P[0].y + 3 * t * pow(1 - t, 2) * P[1].y + 3 * t * t * (1 - t) * P[2].y + pow(t, 3) * P[3].y
		);


		tempPoint.setPosition(xy);
		target.draw(tempPoint, states);
		t += 0.001f;
	}
}