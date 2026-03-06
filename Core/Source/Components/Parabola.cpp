#include "Parabola.h"
#include "../Graphics/Window.h"
#include "Source/Components/Line.h"
#include "Source/Components/Point.h"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector> 
#include <cmath>

Parabola::Parabola(IPoint* p, ILine* l) : m_focus(p), m_directrix(l)
{
}

Parabola::~Parabola()
{
}

void Parabola::Draw(Window& window)
{

	sf::View* view = window.GetView("main");

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;

	float scale = window.GetScale(window.GetView("main"));

	Point* bottom_left = new Point(sf::Vector2f(left, bottom));
	Point* bottom_right = new Point(sf::Vector2f(right, bottom));
	Point* top_left = new Point(sf::Vector2f(left, top));
	Point* top_right = new Point(sf::Vector2f(right, top));
	std::vector<Point*> points = { bottom_left, bottom_right, top_left, top_right };

	Point* closest_point = bottom_left;

	sf::Vertex v1;
	sf::Vertex v2;
	sf::Vertex v1_;
	sf::Vertex v2_;

	PerpendicularLine axis_of_symetry(m_focus, m_directrix);
	ParallelLine focus_line(m_focus, m_directrix);
	Point intersection = axis_of_symetry.Intersection(*m_directrix);
	Point vertex = m_focus->MidPoint(intersection);
	ParallelLine vertex_line(&vertex, m_directrix);
	ParallelLine parallel_line(&vertex, m_directrix);

	v1.position = vertex.position;
	v2.position = vertex.position;
	
	float windowSlope = window.GetSize().y / window.GetSize().x;
	float lineSlope = -vertex_line.a / vertex_line.b;

	float closest_distance = INFINITY;
	for (const auto& point : points)
	{
		float d = point->Distance(vertex.position);
		if (d < closest_distance)
		{
			closest_point = point;
			closest_distance = d;
		}
	}

	int direction = 1;
	int sign = parallel_line.c < m_directrix->c ? -1:1;


	if (vertex.position.x >= left && vertex.position.x <= right && vertex.position.y >= top && vertex.position.y <= bottom)
	{
	float dc = std::sqrt(axis_of_symetry.a*axis_of_symetry.a+axis_of_symetry.b*axis_of_symetry.b) * sign * scale * 5;
		while (true)
		{
			if ((v1.position.x < left || v1.position.x > right || v1.position.y < top || v1.position.y > bottom) && (v2.position.x < left || v2.position.x > right || v2.position.y < top || v2.position.y > bottom))
			{
				break;
			}

			v1_.position = parallel_line.Intersection(axis_of_symetry).position;
			v2_.position = v1_.position;

			float r = parallel_line.Distance(*m_directrix);
			float h = parallel_line.Distance(m_focus->position);
			float x = r > h ? std::sqrt(r*r-h*h) : 0;

			float angle = std::atan(-parallel_line.a/parallel_line.b);
			float dx = x * std::cos(angle);
			float dy = x * std::sin(angle);

			v1_.position -= sf::Vector2f(dx, dy);
			v2_.position -= sf::Vector2f(-dx, -dy);

			v1.color = color;
			v2.color = color;
			v1_.color = color;
			v2_.color = color;

			sf::Vertex seg1[] = { v1, v1_ };
			sf::Vertex seg2[] = { v2, v2_ };

			window.DrawLines(seg1, 2);
			window.DrawLines(seg2, 2);

			v1.position = v1_.position;
			v2.position = v2_.position;
			parallel_line.c += dc;

		}
	}
	else {
		int i = 0;
		while (i<300)
		{

			float dc = std::sqrt(axis_of_symetry.a * axis_of_symetry.a + axis_of_symetry.b * axis_of_symetry.b) * sign * scale * 5;
			v1_.position = parallel_line.Intersection(axis_of_symetry).position;
			v2_.position = v1_.position;

			float r = parallel_line.Distance(*m_directrix);
			float h = parallel_line.Distance(m_focus->position);
			float x = r > h ? std::sqrt(r * r - h * h) : 0;

			float angle = std::atan(-parallel_line.a / parallel_line.b);
			float dx = x * std::cos(angle);
			float dy = x * std::sin(angle);

			v1_.position -= sf::Vector2f(dx, dy);
			v2_.position -= sf::Vector2f(-dx, -dy);

			v1.color = color;
			v2.color = color;
			v1_.color = color;
			v2_.color = color;

			sf::Vertex seg1[] = { v1, v1_ };
			sf::Vertex seg2[] = { v2, v2_ };

			window.DrawLines(seg1, 2);
			window.DrawLines(seg2, 2);

			v1.position = v1_.position;
			v2.position = v2_.position;
			parallel_line.c += dc;
			i++;

		}
	}


	for (const auto& point : points)
	{
		delete point;
	}

}
