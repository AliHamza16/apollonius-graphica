#pragma once
#include <SFML/System/Vector2.hpp>

class Window;
namespace sf {
	class RectangleShape;
}

class TestRectangle
{
public:
	TestRectangle(sf::Vector2f size, sf::Vector2f position);
	~TestRectangle();

	void Draw(Window& window) const;

private:
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::RectangleShape* m_shape;
};