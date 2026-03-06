#include "TestRectangle.h"
#include "../Graphics/Window.h"
#include <SFML/Graphics/RectangleShape.hpp>

TestRectangle::TestRectangle(sf::Vector2f size, sf::Vector2f position) : m_size(size), m_position(position)
{
	m_shape = new sf::RectangleShape(size);
	m_shape->setPosition(position);
	m_shape->setFillColor(sf::Color::Blue);
}

TestRectangle::~TestRectangle()
{
	delete m_shape;
}

void TestRectangle::Draw(Window& window) const
{
	window.Draw(*m_shape);
}
