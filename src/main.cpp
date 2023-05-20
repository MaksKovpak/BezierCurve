#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "BezierCurve.hpp"
#include "BezierPath.hpp"

using namespace sf;

int main() {
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(sf::VideoMode(1024, 800), "Bezier Curve!", Style::Default, settings);
	
	Image cursorImage;
	cursorImage.loadFromFile("../cursor.png");
	
	Cursor cursor;
	cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), Vector2u(0, 0));
	window.setMouseCursor(cursor);


	RectangleShape button(Vector2f(30, 30));
	button.setFillColor(Color::Red);
	button.setPosition(20, 20);
	bool isButtonPressed = false;


	const int RADIUS = 4;

	std::vector<CircleShape> points;
	std::vector<Vector2f> positions;

	CircleShape tempPoint(RADIUS, 100);
	tempPoint.setOrigin(RADIUS, RADIUS);

	int movableIndex = -1;

	std::unique_ptr<BezierPath> path;

	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				bool contains = false;
				for (size_t i = 0; i < points.size(); i++) {
					if (points[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
						contains = true;

										
						if (movableIndex != -1) {
							points[i].setOutlineThickness(0);
							movableIndex = -1;
						} else {
							points[i].setOutlineThickness(2);
							movableIndex = i;
							break;
						}				
					}
				}

				if (button.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
					isButtonPressed = !isButtonPressed;
					button.setFillColor(isButtonPressed ? Color::Green : Color::Red);
					
					if (isButtonPressed) {
						for (size_t i = 6; i < positions.size(); i += 3) {
							positions[i - 2] = positions[i - 3] + (positions[i - 3] - positions[i - 4]);
						}
					}

				} else if (!contains) {
					tempPoint.setPosition(Vector2f(Mouse::getPosition(window)));
					points.push_back(tempPoint);
					positions.push_back(tempPoint.getPosition());

					if (isButtonPressed && positions.size() >= 6 && positions.size() % 3 == 1) {
						positions[positions.size() - 5] = positions[positions.size() - 4] + (positions[positions.size() - 4] - positions[positions.size() - 3]);
					}
				}

			}

			if (event.type == Event::MouseMoved) {
				if (movableIndex != -1) {
					points[movableIndex].setPosition(Vector2f(Mouse::getPosition(window)));
					positions[movableIndex] = points[movableIndex].getPosition();
				}
			}
		}

		if (isButtonPressed) {
			for (size_t i = 6; i < positions.size(); i += 3) {	
				if (movableIndex == i - 2) {
					positions[i - 4] = positions[i - 3] + (positions[i - 3] - positions[i - 2]);
				}
				else if (movableIndex == i - 4) {
					positions[i - 2] = positions[i - 3] + (positions[i - 3] - positions[i - 4]);
				}
			}
		}

		window.clear(Color::White);

		path = std::make_unique<BezierPath>(positions);

		points = path->draw(window);
		
		window.draw(button);

		window.display();
	}

	return EXIT_SUCCESS;
}
