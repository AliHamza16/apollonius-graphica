#include "CoordinateSystem.h"
#include "../Graphics/Window.h"
#include "../Constants/Constants.h"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <format>
#include <iostream>
#include <cmath>

CoordinateSystem::CoordinateSystem()
{
	m_font = new sf::Font;
	m_text = new sf::Text;

	m_font->loadFromFile("Assets/Fonts/OpenSans-Regular.ttf");
	m_text->setFont(*m_font);

	m_text->setCharacterSize(20);
	m_text->setFillColor(sf::Color::White);
}

void CoordinateSystem::Draw(Window& window)
{

	sf::View* view = window.GetView("main");

	if (gridSize / window.GetScale(view) >= 200)
	{
		gridSize /= 2;
		n *= 2;
	}
	else if (gridSize / window.GetScale(view) < 50) {
		gridSize *= 2;
		n /= 2;
	}

	if(gridsEnabled) DrawGrids(window);
	DrawAxes(window);
}

void CoordinateSystem::ShowMouseCoordinates(Window& window)
{
	m_text->setPosition(window.GetSize()-sf::Vector2f(5,10));
	window.Draw(*m_text);
}

void CoordinateSystem::UpdateMouseCoordinates(sf::Vector2f position)
{
	m_mousePosition = position * 0.01f;
	m_string = std::format("x: {0:.2f} y: {1:.2f}", m_mousePosition.x, -m_mousePosition.y);
	m_text->setString(m_string);
	m_text->setOrigin(m_text->getGlobalBounds().width, m_text->getGlobalBounds().height);
}

void CoordinateSystem::Reset()
{
	gridSize = 100;
	n = 1;
}

sf::Vector2f CoordinateSystem::GetSnapPosition(sf::Vector2f position) const
{
	float cord_x = position.x * 0.01f;
	float cord_y = -position.y * 0.01f;

	float a_x = cord_x * n;
	float a_y = cord_y * n;

	float diff_x = std::round(a_x) - a_x;
	float diff_y = std::round(a_y) - a_y;

	if (diff_x * diff_x + diff_y * diff_y < 0.02 )
	{
		return sf::Vector2f(std::round(a_x) * 100 / n, -std::round(a_y) * 100 / n);
	}
	return position;
}

void CoordinateSystem::DrawAxes(Window& window)
{
	sf::View* view = window.GetView("main");

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;


	sf::Vertex l1[] =
	{
		sf::Vertex(sf::Vector2f(left, 0)),
		sf::Vertex(sf::Vector2f(right, 0))
	};

	sf::Vertex l2[] =
	{
		sf::Vertex(sf::Vector2f(0, top)),
		sf::Vertex(sf::Vector2f(0, bottom))
	};

	l1[0].color = Constants::AXIS_COLOR;
	l1[1].color = Constants::AXIS_COLOR;

	l2[0].color = Constants::AXIS_COLOR;
	l2[1].color = Constants::AXIS_COLOR;

	window.DrawLines(l1, 2);
	window.DrawLines(l2, 2);
}

void CoordinateSystem::DrawGrids(Window& window)
{
	if (subgridsEnabled)
	{
		DrawSubgrids(window);
	}

	sf::View* view = window.GetView("main");

	float x, y;

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;

	float scale = window.GetScale(view);

	x = gridSize;
	while (x < right) {
		if (x < left)
		{
			x += gridSize;
			continue;
		}
		sf::Vertex g[] =
		{
			sf::Vertex(sf::Vector2f(x, top)),
			sf::Vertex(sf::Vector2f(x, bottom))
		};
		g[0].color = Constants::GRID_COLOR;
		g[1].color = g[0].color;

		window.DrawLines(g, 2);
		x += gridSize;
	}

	x = -gridSize;
	while (x > left) {
		if (x > right)
		{
			x -= gridSize;
			continue;
		}
		sf::Vertex g[] =
		{
			sf::Vertex(sf::Vector2f(x, top)),
			sf::Vertex(sf::Vector2f(x, bottom))
		};
		g[0].color = Constants::GRID_COLOR;
		g[1].color = g[0].color;

		window.DrawLines(g, 2);
		x -= gridSize;
	}

	y = gridSize;
	while (y < bottom) {
		if (y < top)
		{
			y += gridSize;
			continue;
		}
		sf::Vertex g[] =
		{
			sf::Vertex(sf::Vector2f(left, y)),
			sf::Vertex(sf::Vector2f(right, y))
		};
		g[0].color = Constants::GRID_COLOR;
		g[1].color = g[0].color;

		window.DrawLines(g, 2);
		y += gridSize;
	}

	y = -gridSize;
	while (y > top) {
		if (y > bottom)
		{
			y -= gridSize;
			continue;
		}
		sf::Vertex g[] =
		{
			sf::Vertex(sf::Vector2f(left, y)),
			sf::Vertex(sf::Vector2f(right, y))
		};
		g[0].color = Constants::GRID_COLOR;
		g[1].color = g[0].color;

		window.DrawLines(g, 2);
		y -= gridSize;
	}
}

void CoordinateSystem::DrawSubgrids(Window& window)
{
	sf::View* view = window.GetView("main");

	float x, y;
	float step = gridSize / 5;

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;

	float scale = window.GetScale(view);

	x = step;
	while (x < right) {
		if (x < left)
		{
			x += step;
			continue;
		}
		sf::Vertex g[] =
		{
			sf::Vertex(sf::Vector2f(x, top)),
			sf::Vertex(sf::Vector2f(x, bottom))
		};
		g[0].color = Constants::SUBGRID_COLOR;
		g[1].color = g[0].color;

		window.DrawLines(g, 2);
		x += step;
	}

	x = -step;
	while (x > left) {
		if (x > right)
		{
			x -= step;
			continue;
		}
		sf::Vertex g[] =
		{
			sf::Vertex(sf::Vector2f(x, top)),
			sf::Vertex(sf::Vector2f(x, bottom))
		};
		g[0].color = Constants::SUBGRID_COLOR;
		g[1].color = g[0].color;

		window.DrawLines(g, 2);
		x -= step;
	}

	y = step;
	while (y < bottom) {
		if (y < top)
		{
			y += step;
			continue;
		}
		sf::Vertex g[] =
		{
			sf::Vertex(sf::Vector2f(left, y)),
			sf::Vertex(sf::Vector2f(right, y))
		};
		g[0].color = Constants::SUBGRID_COLOR;
		g[1].color = g[0].color;

		window.DrawLines(g, 2);
		y += step;
	}

	y = -step;
	while (y > top) {
		if (y > bottom)
		{
			y -= step;
			continue;
		}
		sf::Vertex g[] =
		{
			sf::Vertex(sf::Vector2f(left, y)),
			sf::Vertex(sf::Vector2f(right, y))
		};
		g[0].color = Constants::SUBGRID_COLOR;
		g[1].color = g[0].color;

		window.DrawLines(g, 2);
		y -= step;
	}
}
