#include "Triangle.h"
#include "./Segment.h"
#include "./Point.h"
#include <algorithm>

Triangle::Triangle()
{
}

Triangle::Triangle(const Triangle& other)
{
	m_s1 = other.m_s1;
	m_s2 = other.m_s2;
	m_s3 = other.m_s3;
}

Triangle::~Triangle()
{
}

void Triangle::AddSegment(Segment* s)
{
	if (m_s1 == nullptr)
	{
		m_s1 = s;
	}
	else if (m_s2 == nullptr)
	{
		m_s2 = s;
	}
	else if (m_s3 == nullptr)
	{
		m_s3 = s;
	}
}

static float GetTotalDistance(Segment* s, sf::Vector2f position) {
	return s->GetPoint(1)->Distance(position) + s->GetPoint(2)->Distance(position);
};

Segment* Triangle::GetSelectedSegment(sf::Vector2f position, float scale)
{
	if (GetTotalDistance(m_s1, position) - m_s1->GetLength() < scale * 0.5)
	{
		return m_s1;
	}

	if (GetTotalDistance(m_s2, position) - m_s2->GetLength() < scale * 0.5)
	{
		return m_s2;
	}

	if (GetTotalDistance(m_s3, position) - m_s3->GetLength() < scale * 0.5)
	{
		return m_s3;
	}

	return nullptr;
}

std::vector<Segment*> Triangle::GetSegments() const
{
	return std::vector<Segment*>{m_s1, m_s2, m_s3};
}

std::vector<IPoint*> Triangle::GetPoints() const
{
	const auto& segments = GetSegments();
	std::vector<IPoint*> points;
	for (const auto& segment : segments)
	{
		if (std::find(points.begin(), points.end(), segment->GetPoint(1)) != points.end())
		{

		}
		else {
			points.push_back(segment->GetPoint(1));
		}

		if (std::find(points.begin(), points.end(), segment->GetPoint(2)) != points.end())
		{

		}
		else {
			points.push_back(segment->GetPoint(2));
		}

	}
		return points;
}
