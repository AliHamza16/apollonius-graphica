#include "Segment.h"
#include "../Graphics/Window.h"
#include "./Point.h"
#include <SFML/Graphics/Vertex.hpp>
#include "../Constants/Constants.h"

Segment::Segment(IPoint* point1, IPoint* point2) : m_point1(point1), m_point2(point2)
{
}

Segment::Segment(const Segment& other)
{
	m_point1 = new Point(*other.m_point1);
}

Segment::~Segment()
{
}

void Segment::Draw(Window& window)
{
	sf::Vertex seg[] = {
		sf::Vertex(m_point1->position), sf::Vertex(m_point2->position)
	};

	seg[0].color = Constants::SEGMENT_COLOR;
	seg[1].color = Constants::SEGMENT_COLOR;

	window.DrawLines(seg, 2);
}

IPoint* Segment::GetPoint(int index) const
{
	switch (index)
	{
	case 1:
		return m_point1;
		break;
	case 2:
		return m_point2;
		break;
	default:
		return nullptr;
		break;
	}
}

float Segment::GetTotalDistance(sf::Vector2f position) const
{
	return m_point1->Distance(position) + m_point2->Distance(position);
}

float Segment::GetLength() const
{
	return m_point1->Distance(m_point2->position);
}
