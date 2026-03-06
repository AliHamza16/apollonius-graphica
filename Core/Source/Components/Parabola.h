#pragma once
#include <SFML/Graphics/Color.hpp>

class Window;
class IPoint;
class ILine;

class Parabola
{
public:
	Parabola(IPoint* p, ILine* l);
	~Parabola();

	void Draw(Window& window);

	sf::Color color = sf::Color(245, 42, 245);

private:
	IPoint* m_focus = nullptr;
	ILine* m_directrix = nullptr;
};