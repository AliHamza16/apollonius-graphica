#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

class CameraController
{
public:
	void Reset(int index);
	void Move(sf::Vector2f offset);

	std::vector<bool> states = {false, false, false, false, false, false, false};
	// zoomIn, zoomOut, moveLeft, moveRight, moveUp, moveDown, moveWithMouse

	sf::Vector2f lastMousePosition;
private:
};
