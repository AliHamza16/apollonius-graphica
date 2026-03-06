#include "./Line.h"
#include "./Point.h"
#include "../Graphics/Window.h"
#include <SFML/Graphics/Vertex.hpp>
#include "Source/Components/Triangle.h"
#include "Source/Components/Segment.h"
#include <cmath>

Line::Line(IPoint* p1, IPoint* p2) : m_p1(p1), m_p2(p2)
{
	Update();
}

Line::~Line()
{
}

void Line::Update()
{
	sf::Vector2f diff = m_p1->position - m_p2->position;
	a = diff.y;
	b = -diff.x;
	c = -a * m_p1->position.x - b * m_p1->position.y;
}

void Line::Draw(Window& window)
{
	Update();

	sf::View* view = window.GetView("main");

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;

	sf::Vertex v1;
	sf::Vertex v2;

	// x = -(c + by)/a

	float windowSlope = window.GetSize().y / window.GetSize().x;
	float lineSlope = -a / b;

	if (lineSlope >= -windowSlope && lineSlope <= windowSlope)
	{
		v1.position = sf::Vector2f(left, -(c + a * left) / b);
		v2.position = sf::Vector2f(right, -(c + a * right) / b);
	}
	else {
		v1.position = sf::Vector2f( -(c + b * top) / a, top);
		v2.position = sf::Vector2f( -(c + b * bottom) / a, bottom);
	}

	sf::Vertex line[] = { v1, v2 };
	line[0].color = color;
	line[1].color = color;
	window.DrawLines(line, 2);

}

ParallelLine::ParallelLine(IPoint* p, ILine* l) : m_p(p), m_l(l)
{
	Update();
}

ParallelLine::~ParallelLine()
{
}

void ParallelLine::Update()
{
	a = m_l->a;
	b = m_l->b;
	c = -a * m_p->position.x - b * m_p->position.y;
}

void ParallelLine::Draw(Window& window)
{
	Update();

	sf::View* view = window.GetView("main");

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;

	sf::Vertex v1;
	sf::Vertex v2;

	// x = -(c + by)/a

	float windowSlope = window.GetSize().y / window.GetSize().x;
	float lineSlope = -a / b;

	if (lineSlope >= -windowSlope && lineSlope <= windowSlope)
	{
		v1.position = sf::Vector2f(left, -(c + a * left) / b);
		v2.position = sf::Vector2f(right, -(c + a * right) / b);
	}
	else {
		v1.position = sf::Vector2f(-(c + b * top) / a, top);
		v2.position = sf::Vector2f(-(c + b * bottom) / a, bottom);
	}

	sf::Vertex line[] = { v1, v2 };
	line[0].color = color;
	line[1].color = color;
	window.DrawLines(line, 2);
}

float ILine::Distance(sf::Vector2f position)
{
	float d = std::abs(a * position.x + b * position.y + c)/std::sqrt(a*a + b*b);
	return d;
}

float ILine::Distance(ILine& other)
{
	float d = std::abs(c - other.c) / std::sqrt(a * a + b * b);
	return d;
}

Point ILine::Intersection(ILine& other)
{
	Point p(sf::Vector2f((b * other.c - c * other.b) / (a * other.b - b * other.a), (c * other.a - a * other.c) / (a * other.b - b * other.a)));
	return p;
}

PerpendicularLine::PerpendicularLine(IPoint* p, ILine* l) : m_p(p), m_l(l)
{
	Update();
}

PerpendicularLine::~PerpendicularLine()
{
}

void PerpendicularLine::Update()
{
	a = -m_l->b;
	b = m_l->a;
	c = -a * m_p->position.x - b * m_p->position.y;
}

void PerpendicularLine::Draw(Window& window)
{
	Update();

	sf::View* view = window.GetView("main");

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;

	sf::Vertex v1;
	sf::Vertex v2;

	// x = -(c + by)/a

	float windowSlope = window.GetSize().y / window.GetSize().x;
	float lineSlope = -a / b;

	if (lineSlope >= -windowSlope && lineSlope <= windowSlope)
	{
		v1.position = sf::Vector2f(left, -(c + a * left) / b);
		v2.position = sf::Vector2f(right, -(c + a * right) / b);
	}
	else {
		v1.position = sf::Vector2f(-(c + b * top) / a, top);
		v2.position = sf::Vector2f(-(c + b * bottom) / a, bottom);
	}

	sf::Vertex line[] = { v1, v2 };
	line[0].color = color;
	line[1].color = color;
	window.DrawLines(line, 2);
}

JustLine::JustLine(float a, float b, float c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

JustLine::~JustLine()
{
}

void JustLine::Update()
{
}

void JustLine::Draw(Window& window)
{
	Update();

	sf::View* view = window.GetView("main");

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;

	sf::Vertex v1;
	sf::Vertex v2;

	// x = -(c + by)/a

	float windowSlope = window.GetSize().y / window.GetSize().x;
	float lineSlope = -a / b;

	if (lineSlope >= -windowSlope && lineSlope <= windowSlope)
	{
		v1.position = sf::Vector2f(left, -(c + a * left) / b);
		v2.position = sf::Vector2f(right, -(c + a * right) / b);
	}
	else {
		v1.position = sf::Vector2f(-(c + b * top) / a, top);
		v2.position = sf::Vector2f(-(c + b * bottom) / a, bottom);
	}

	sf::Vertex line[] = { v1, v2 };
	line[0].color = color;
	line[1].color = color;
	window.DrawLines(line, 2);
}

TriangleParabolaDirectrixLine::TriangleParabolaDirectrixLine(Triangle* triangle, Segment* segment) : m_triangle(triangle), m_segment(segment)
{
	sf::Vector2f center_of_mass(-999999999999, -999999999);
	m_center_of_mass = center_of_mass;
}

TriangleParabolaDirectrixLine::~TriangleParabolaDirectrixLine()
{
}


static constexpr float GetC(float a, float b, IPoint* A, IPoint* B, IPoint* C) {
  float x1(A->position.x);
  float x2(B->position.x);
  float x3(C->position.x);
  float y1(A->position.y);
  float y2(B->position.y);
  float y3(C->position.y);

  const float a_squared = a * a;
  const float a_cubed = a * a * a;
  const float a_fourth = a * a * a * a;
  const float b_squared = b * b;
  const float b_cubed = b * b * b;
  const float b_fourth = b * b * b * b;
  const float x1_squared = x1 * x1;
  const float x1_cubed = x1 * x1 * x1;
  const float x1_fourth = x1 * x1 * x1 * x1;
  const float x2_squared = x2 * x2;
  const float x2_cubed = x2 * x2 * x2;
  const float x2_fourth = x2 * x2 * x2 * x2;
  const float x3_squared = x3 * x3;
  const float x3_cubed = x3 * x3 * x3;
  const float x3_fourth = x3 * x3 * x3 * x3;
  const float y1_squared = y1 * y1;
  const float y1_cubed = y1 * y1 * y1;
  const float y1_fourth = y1 * y1 * y1 * y1;
  const float y2_squared = y2 * y2;
  const float y2_cubed = y2 * y2 * y2;
  const float y2_fourth = y2 * y2 * y2 * y2;
  const float y3_squared = y3 * y3;
  const float y3_cubed = y3 * y3 * y3;
  const float y3_fourth = y3 * y3 * y3 * y3;

  return -(-a_fourth * x1_squared * y2_fourth +
    4 * a_fourth * x1_squared * y2_cubed * y3 -
    6 * a_fourth * x1_squared * y2_squared * y3_squared +
    4 * a_fourth * x1_squared * y2 * y3_cubed -
    a_fourth * x1_squared * y3_fourth +
    2 * a_fourth * x1 * x2 * y1_squared * y2_squared -
    4 * a_fourth * x1 * x2 * y1_squared * y2 * y3 +
    2 * a_fourth * x1 * x2 * y1_squared * y3_squared -
    4 * a_fourth * x1 * x2 * y1 * y2_squared * y3 +
    8 * a_fourth * x1 * x2 * y1 * y2 * y3_squared -
    4 * a_fourth * x1 * x2 * y1 * y3_cubed +
    2 * a_fourth * x1 * x2 * y2_squared * y3_squared -
    4 * a_fourth * x1 * x2 * y2 * y3_cubed +
    2 * a_fourth * x1 * x2 * y3_fourth +
    2 * a_fourth * x1 * x3 * y1_squared * y2_squared -
    4 * a_fourth * x1 * x3 * y1_squared * y2 * y3 +
    2 * a_fourth * x1 * x3 * y1_squared * y3_squared -
    4 * a_fourth * x1 * x3 * y1 * y2_cubed +
    8 * a_fourth * x1 * x3 * y1 * y2_squared * y3 -
    4 * a_fourth * x1 * x3 * y1 * y2 * y3_squared +
    2 * a_fourth * x1 * x3 * y2_fourth -
    4 * a_fourth * x1 * x3 * y2_cubed * y3 +
    2 * a_fourth * x1 * x3 * y2_squared * y3_squared -
    a_fourth * x2_squared * y1_fourth +
    4 * a_fourth * x2_squared * y1_cubed * y3 -
    6 * a_fourth * x2_squared * y1_squared * y3_squared +
    4 * a_fourth * x2_squared * y1 * y3_cubed -
    a_fourth * x2_squared * y3_fourth +
    2 * a_fourth * x2 * x3 * y1_fourth -
    4 * a_fourth * x2 * x3 * y1_cubed * y2 -
    4 * a_fourth * x2 * x3 * y1_cubed * y3 +
    2 * a_fourth * x2 * x3 * y1_squared * y2_squared +
    8 * a_fourth * x2 * x3 * y1_squared * y2 * y3 +
    2 * a_fourth * x2 * x3 * y1_squared * y3_squared -
    4 * a_fourth * x2 * x3 * y1 * y2_squared * y3 -
    4 * a_fourth * x2 * x3 * y1 * y2 * y3_squared +
    2 * a_fourth * x2 * x3 * y2_squared * y3_squared -
    a_fourth * x3_squared * y1_fourth +
    4 * a_fourth * x3_squared * y1_cubed * y2 -
    6 * a_fourth * x3_squared * y1_squared * y2_squared +
    4 * a_fourth * x3_squared * y1 * y2_cubed -
    a_fourth * x3_squared * y2_fourth -
    a_fourth * y1_fourth * y2_squared +
    2 * a_fourth * y1_fourth * y2 * y3 -
    a_fourth * y1_fourth * y3_squared +
    2 * a_fourth * y1_cubed * y2_cubed -
    2 * a_fourth * y1_cubed * y2_squared * y3 -
    2 * a_fourth * y1_cubed * y2 * y3_squared +
    2 * a_fourth * y1_cubed * y3_cubed -
    a_fourth * y1_squared * y2_fourth -
    2 * a_fourth * y1_squared * y2_cubed * y3 +
    6 * a_fourth * y1_squared * y2_squared * y3_squared -
    2 * a_fourth * y1_squared * y2 * y3_cubed -
    a_fourth * y1_squared * y3_fourth +
    2 * a_fourth * y1 * y2_fourth * y3 -
    2 * a_fourth * y1 * y2_cubed * y3_squared -
    2 * a_fourth * y1 * y2_squared * y3_cubed +
    2 * a_fourth * y1 * y2 * y3_fourth -
    a_fourth * y2_fourth * y3_squared +
    2 * a_fourth * y2_cubed * y3_cubed -
    a_fourth * y2_squared * y3_fourth -
    4 * a_cubed * b * x1_squared * x2 * y1 * y2_squared +
    8 * a_cubed * b * x1_squared * x2 * y1 * y2 * y3 -
    4 * a_cubed * b * x1_squared * x2 * y1 * y3_squared +
    4 * a_cubed * b * x1_squared * x2 * y2_cubed -
    8 * a_cubed * b * x1_squared * x2 * y2_squared * y3 +
    4 * a_cubed * b * x1_squared * x2 * y2 * y3_squared -
    4 * a_cubed * b * x1_squared * x3 * y1 * y2_squared +
    8 * a_cubed * b * x1_squared * x3 * y1 * y2 * y3 -
    4 * a_cubed * b * x1_squared * x3 * y1 * y3_squared +
    4 * a_cubed * b * x1_squared * x3 * y2_squared * y3 -
    8 * a_cubed * b * x1_squared * x3 * y2 * y3_squared +
    4 * a_cubed * b * x1_squared * x3 * y3_cubed +
    4 * a_cubed * b * x1 * x2_squared * y1_cubed -
    4 * a_cubed * b * x1 * x2_squared * y1_squared * y2 -
    8 * a_cubed * b * x1 * x2_squared * y1_squared * y3 +
    8 * a_cubed * b * x1 * x2_squared * y1 * y2 * y3 +
    4 * a_cubed * b * x1 * x2_squared * y1 * y3_squared -
    4 * a_cubed * b * x1 * x2_squared * y2 * y3_squared -
    8 * a_cubed * b * x1 * x2 * x3 * y1_cubed +
    12 * a_cubed * b * x1 * x2 * x3 * y1_squared * y2 +
    12 * a_cubed * b * x1 * x2 * x3 * y1_squared * y3 +
    12 * a_cubed * b * x1 * x2 * x3 * y1 * y2_squared -
    48 * a_cubed * b * x1 * x2 * x3 * y1 * y2 * y3 +
    12 * a_cubed * b * x1 * x2 * x3 * y1 * y3_squared -
    8 * a_cubed * b * x1 * x2 * x3 * y2_cubed +
    12 * a_cubed * b * x1 * x2 * x3 * y2_squared * y3 +
    12 * a_cubed * b * x1 * x2 * x3 * y2 * y3_squared -
    8 * a_cubed * b * x1 * x2 * x3 * y3_cubed +
    4 * a_cubed * b * x1 * x3_squared * y1_cubed -
    8 * a_cubed * b * x1 * x3_squared * y1_squared * y2 -
    4 * a_cubed * b * x1 * x3_squared * y1_squared * y3 +
    4 * a_cubed * b * x1 * x3_squared * y1 * y2_squared +
    8 * a_cubed * b * x1 * x3_squared * y1 * y2 * y3 -
    4 * a_cubed * b * x1 * x3_squared * y2_squared * y3 +
    4 * a_cubed * b * x1 * y1_cubed * y2_squared -
    8 * a_cubed * b * x1 * y1_cubed * y2 * y3 +
    4 * a_cubed * b * x1 * y1_cubed * y3_squared -
    4 * a_cubed * b * x1 * y1_squared * y2_cubed +
    4 * a_cubed * b * x1 * y1_squared * y2_squared * y3 +
    4 * a_cubed * b * x1 * y1_squared * y2 * y3_squared -
    4 * a_cubed * b * x1 * y1_squared * y3_cubed +
    4 * a_cubed * b * x1 * y1 * y2_cubed * y3 -
    8 * a_cubed * b * x1 * y1 * y2_squared * y3_squared +
    4 * a_cubed * b * x1 * y1 * y2 * y3_cubed -
    4 * a_cubed * b * x2_squared * x3 * y1_squared * y2 +
    4 * a_cubed * b * x2_squared * x3 * y1_squared * y3 +
    8 * a_cubed * b * x2_squared * x3 * y1 * y2 * y3 -
    8 * a_cubed * b * x2_squared * x3 * y1 * y3_squared -
    4 * a_cubed * b * x2_squared * x3 * y2 * y3_squared +
    4 * a_cubed * b * x2_squared * x3 * y3_cubed +
    4 * a_cubed * b * x2 * x3_squared * y1_squared * y2 -
    4 * a_cubed * b * x2 * x3_squared * y1_squared * y3 -
    8 * a_cubed * b * x2 * x3_squared * y1 * y2_squared +
    8 * a_cubed * b * x2 * x3_squared * y1 * y2 * y3 +
    4 * a_cubed * b * x2 * x3_squared * y2_cubed -
    4 * a_cubed * b * x2 * x3_squared * y2_squared * y3 -
    4 * a_cubed * b * x2 * y1_cubed * y2_squared +
    4 * a_cubed * b * x2 * y1_cubed * y2 * y3 +
    4 * a_cubed * b * x2 * y1_squared * y2_cubed +
    4 * a_cubed * b * x2 * y1_squared * y2_squared * y3 -
    8 * a_cubed * b * x2 * y1_squared * y2 * y3_squared -
    8 * a_cubed * b * x2 * y1 * y2_cubed * y3 +
    4 * a_cubed * b * x2 * y1 * y2_squared * y3_squared +
    4 * a_cubed * b * x2 * y1 * y2 * y3_cubed +
    4 * a_cubed * b * x2 * y2_cubed * y3_squared -
    4 * a_cubed * b * x2 * y2_squared * y3_cubed +
    4 * a_cubed * b * x3 * y1_cubed * y2 * y3 -
    4 * a_cubed * b * x3 * y1_cubed * y3_squared -
    8 * a_cubed * b * x3 * y1_squared * y2_squared * y3 +
    4 * a_cubed * b * x3 * y1_squared * y2 * y3_squared +
    4 * a_cubed * b * x3 * y1_squared * y3_cubed +
    4 * a_cubed * b * x3 * y1 * y2_cubed * y3 +
    4 * a_cubed * b * x3 * y1 * y2_squared * y3_squared -
    8 * a_cubed * b * x3 * y1 * y2 * y3_cubed -
    4 * a_cubed * b * x3 * y2_cubed * y3_squared +
    4 * a_cubed * b * x3 * y2_squared * y3_cubed +
    2 * a_squared * b_squared * x1_cubed * x2 * y2_squared -
    4 * a_squared * b_squared * x1_cubed * x2 * y2 * y3 +
    2 * a_squared * b_squared * x1_cubed * x2 * y3_squared +
    2 * a_squared * b_squared * x1_cubed * x3 * y2_squared -
    4 * a_squared * b_squared * x1_cubed * x3 * y2 * y3 +
    2 * a_squared * b_squared * x1_cubed * x3 * y3_squared -
    6 * a_squared * b_squared * x1_squared * x2_squared * y1_squared +
    8 * a_squared * b_squared * x1_squared * x2_squared * y1 * y2 +
    4 * a_squared * b_squared * x1_squared * x2_squared * y1 * y3 -
    6 * a_squared * b_squared * x1_squared * x2_squared * y2_squared +
    4 * a_squared * b_squared * x1_squared * x2_squared * y2 * y3 -
    4 * a_squared * b_squared * x1_squared * x2_squared * y3_squared +
    12 * a_squared * b_squared * x1_squared * x2 * x3 * y1_squared -
    12 * a_squared * b_squared * x1_squared * x2 * x3 * y1 * y2 -
    12 * a_squared * b_squared * x1_squared * x2 * x3 * y1 * y3 -
    2 * a_squared * b_squared * x1_squared * x2 * x3 * y2_squared +
    16 * a_squared * b_squared * x1_squared * x2 * x3 * y2 * y3 -
    2 * a_squared * b_squared * x1_squared * x2 * x3 * y3_squared -
    6 * a_squared * b_squared * x1_squared * x3_squared * y1_squared +
    4 * a_squared * b_squared * x1_squared * x3_squared * y1 * y2 +
    8 * a_squared * b_squared * x1_squared * x3_squared * y1 * y3 -
    4 * a_squared * b_squared * x1_squared * x3_squared * y2_squared +
    4 * a_squared * b_squared * x1_squared * x3_squared * y2 * y3 -
    6 * a_squared * b_squared * x1_squared * x3_squared * y3_squared -
    6 * a_squared * b_squared * x1_squared * y1_squared * y2_squared +
    12 * a_squared * b_squared * x1_squared * y1_squared * y2 * y3 -
    6 * a_squared * b_squared * x1_squared * y1_squared * y3_squared +
    2 * a_squared * b_squared * x1_squared * y1 * y2_cubed -
    2 * a_squared * b_squared * x1_squared * y1 * y2_squared * y3 -
    2 * a_squared * b_squared * x1_squared * y1 * y2 * y3_squared +
    2 * a_squared * b_squared * x1_squared * y1 * y3_cubed +
    2 * a_squared * b_squared * x1_squared * y2_cubed * y3 -
    4 * a_squared * b_squared * x1_squared * y2_squared * y3_squared +
    2 * a_squared * b_squared * x1_squared * y2 * y3_cubed +
    2 * a_squared * b_squared * x1 * x2_cubed * y1_squared -
    4 * a_squared * b_squared * x1 * x2_cubed * y1 * y3 +
    2 * a_squared * b_squared * x1 * x2_cubed * y3_squared -
    2 * a_squared * b_squared * x1 * x2_squared * x3 * y1_squared -
    12 * a_squared * b_squared * x1 * x2_squared * x3 * y1 * y2 +
    16 * a_squared * b_squared * x1 * x2_squared * x3 * y1 * y3 +
    12 * a_squared * b_squared * x1 * x2_squared * x3 * y2_squared -
    12 * a_squared * b_squared * x1 * x2_squared * x3 * y2 * y3 -
    2 * a_squared * b_squared * x1 * x2_squared * x3 * y3_squared -
    2 * a_squared * b_squared * x1 * x2 * x3_squared * y1_squared +
    16 * a_squared * b_squared * x1 * x2 * x3_squared * y1 * y2 -
    12 * a_squared * b_squared * x1 * x2 * x3_squared * y1 * y3 -
    2 * a_squared * b_squared * x1 * x2 * x3_squared * y2_squared -
    12 * a_squared * b_squared * x1 * x2 * x3_squared * y2 * y3 +
    12 * a_squared * b_squared * x1 * x2 * x3_squared * y3_squared +
    8 * a_squared * b_squared * x1 * x2 * y1_squared * y2_squared -
    12 * a_squared * b_squared * x1 * x2 * y1_squared * y2 * y3 +
    4 * a_squared * b_squared * x1 * x2 * y1_squared * y3_squared -
    12 * a_squared * b_squared * x1 * x2 * y1 * y2_squared * y3 +
    16 * a_squared * b_squared * x1 * x2 * y1 * y2 * y3_squared -
    4 * a_squared * b_squared * x1 * x2 * y1 * y3_cubed +
    4 * a_squared * b_squared * x1 * x2 * y2_squared * y3_squared -
    4 * a_squared * b_squared * x1 * x2 * y2 * y3_cubed +
    2 * a_squared * b_squared * x1 * x3_cubed * y1_squared -
    4 * a_squared * b_squared * x1 * x3_cubed * y1 * y2 +
    2 * a_squared * b_squared * x1 * x3_cubed * y2_squared +
    4 * a_squared * b_squared * x1 * x3 * y1_squared * y2_squared -
    12 * a_squared * b_squared * x1 * x3 * y1_squared * y2 * y3 +
    8 * a_squared * b_squared * x1 * x3 * y1_squared * y3_squared -
    4 * a_squared * b_squared * x1 * x3 * y1 * y2_cubed +
    16 * a_squared * b_squared * x1 * x3 * y1 * y2_squared * y3 -
    12 * a_squared * b_squared * x1 * x3 * y1 * y2 * y3_squared -
    4 * a_squared * b_squared * x1 * x3 * y2_cubed * y3 +
    4 * a_squared * b_squared * x1 * x3 * y2_squared * y3_squared +
    2 * a_squared * b_squared * x2_cubed * x3 * y1_squared -
    4 * a_squared * b_squared * x2_cubed * x3 * y1 * y3 +
    2 * a_squared * b_squared * x2_cubed * x3 * y3_squared -
    4 * a_squared * b_squared * x2_squared * x3_squared * y1_squared +
    4 * a_squared * b_squared * x2_squared * x3_squared * y1 * y2 +
    4 * a_squared * b_squared * x2_squared * x3_squared * y1 * y3 -
    6 * a_squared * b_squared * x2_squared * x3_squared * y2_squared +
    8 * a_squared * b_squared * x2_squared * x3_squared * y2 * y3 -
    6 * a_squared * b_squared * x2_squared * x3_squared * y3_squared +
    2 * a_squared * b_squared * x2_squared * y1_cubed * y2 +
    2 * a_squared * b_squared * x2_squared * y1_cubed * y3 -
    6 * a_squared * b_squared * x2_squared * y1_squared * y2_squared -
    2 * a_squared * b_squared * x2_squared * y1_squared * y2 * y3 -
    4 * a_squared * b_squared * x2_squared * y1_squared * y3_squared +
    12 * a_squared * b_squared * x2_squared * y1 * y2_squared * y3 -
    2 * a_squared * b_squared * x2_squared * y1 * y2 * y3_squared +
    2 * a_squared * b_squared * x2_squared * y1 * y3_cubed -
    6 * a_squared * b_squared * x2_squared * y2_squared * y3_squared +
    2 * a_squared * b_squared * x2_squared * y2 * y3_cubed +
    2 * a_squared * b_squared * x2 * x3_cubed * y1_squared -
    4 * a_squared * b_squared * x2 * x3_cubed * y1 * y2 +
    2 * a_squared * b_squared * x2 * x3_cubed * y2_squared -
    4 * a_squared * b_squared * x2 * x3 * y1_cubed * y2 -
    4 * a_squared * b_squared * x2 * x3 * y1_cubed * y3 +
    4 * a_squared * b_squared * x2 * x3 * y1_squared * y2_squared +
    16 * a_squared * b_squared * x2 * x3 * y1_squared * y2 * y3 +
    4 * a_squared * b_squared * x2 * x3 * y1_squared * y3_squared -
    12 * a_squared * b_squared * x2 * x3 * y1 * y2_squared * y3 -
    12 * a_squared * b_squared * x2 * x3 * y1 * y2 * y3_squared +
    8 * a_squared * b_squared * x2 * x3 * y2_squared * y3_squared +
    2 * a_squared * b_squared * x3_squared * y1_cubed * y2 +
    2 * a_squared * b_squared * x3_squared * y1_cubed * y3 -
    4 * a_squared * b_squared * x3_squared * y1_squared * y2_squared -
    2 * a_squared * b_squared * x3_squared * y1_squared * y2 * y3 -
    6 * a_squared * b_squared * x3_squared * y1_squared * y3_squared +
    2 * a_squared * b_squared * x3_squared * y1 * y2_cubed -
    2 * a_squared * b_squared * x3_squared * y1 * y2_squared * y3 +
    12 * a_squared * b_squared * x3_squared * y1 * y2 * y3_squared +
    2 * a_squared * b_squared * x3_squared * y2_cubed * y3 -
    6 * a_squared * b_squared * x3_squared * y2_squared * y3_squared +
    4 * a * b_cubed * x1_cubed * x2_squared * y1 -
    4 * a * b_cubed * x1_cubed * x2_squared * y2 -
    8 * a * b_cubed * x1_cubed * x2 * x3 * y1 +
    4 * a * b_cubed * x1_cubed * x2 * x3 * y2 +
    4 * a * b_cubed * x1_cubed * x2 * x3 * y3 +
    4 * a * b_cubed * x1_cubed * x3_squared * y1 -
    4 * a * b_cubed * x1_cubed * x3_squared * y3 +
    4 * a * b_cubed * x1_cubed * y1 * y2_squared -
    8 * a * b_cubed * x1_cubed * y1 * y2 * y3 +
    4 * a * b_cubed * x1_cubed * y1 * y3_squared -
    4 * a * b_cubed * x1_squared * x2_cubed * y1 +
    4 * a * b_cubed * x1_squared * x2_cubed * y2 +
    4 * a * b_cubed * x1_squared * x2_squared * x3 * y1 +
    4 * a * b_cubed * x1_squared * x2_squared * x3 * y2 -
    8 * a * b_cubed * x1_squared * x2_squared * x3 * y3 +
    4 * a * b_cubed * x1_squared * x2 * x3_squared * y1 -
    8 * a * b_cubed * x1_squared * x2 * x3_squared * y2 +
    4 * a * b_cubed * x1_squared * x2 * x3_squared * y3 -
    4 * a * b_cubed * x1_squared * x2 * y1 * y2_squared +
    12 * a * b_cubed * x1_squared * x2 * y1 * y2 * y3 -
    8 * a * b_cubed * x1_squared * x2 * y1 * y3_squared -
    4 * a * b_cubed * x1_squared * x2 * y2_squared * y3 +
    4 * a * b_cubed * x1_squared * x2 * y2 * y3_squared -
    4 * a * b_cubed * x1_squared * x3_cubed * y1 +
    4 * a * b_cubed * x1_squared * x3_cubed * y3 -
    8 * a * b_cubed * x1_squared * x3 * y1 * y2_squared +
    12 * a * b_cubed * x1_squared * x3 * y1 * y2 * y3 -
    4 * a * b_cubed * x1_squared * x3 * y1 * y3_squared +
    4 * a * b_cubed * x1_squared * x3 * y2_squared * y3 -
    4 * a * b_cubed * x1_squared * x3 * y2 * y3_squared +
    4 * a * b_cubed * x1 * x2_cubed * x3 * y1 -
    8 * a * b_cubed * x1 * x2_cubed * x3 * y2 +
    4 * a * b_cubed * x1 * x2_cubed * x3 * y3 -
    8 * a * b_cubed * x1 * x2_squared * x3_squared * y1 +
    4 * a * b_cubed * x1 * x2_squared * x3_squared * y2 +
    4 * a * b_cubed * x1 * x2_squared * x3_squared * y3 -
    4 * a * b_cubed * x1 * x2_squared * y1_squared * y2 -
    4 * a * b_cubed * x1 * x2_squared * y1_squared * y3 +
    12 * a * b_cubed * x1 * x2_squared * y1 * y2 * y3 +
    4 * a * b_cubed * x1 * x2_squared * y1 * y3_squared -
    8 * a * b_cubed * x1 * x2_squared * y2 * y3_squared +
    4 * a * b_cubed * x1 * x2 * x3_cubed * y1 +
    4 * a * b_cubed * x1 * x2 * x3_cubed * y2 -
    8 * a * b_cubed * x1 * x2 * x3_cubed * y3 +
    8 * a * b_cubed * x1 * x2 * x3 * y1_squared * y2 +
    8 * a * b_cubed * x1 * x2 * x3 * y1_squared * y3 +
    8 * a * b_cubed * x1 * x2 * x3 * y1 * y2_squared -
    48 * a * b_cubed * x1 * x2 * x3 * y1 * y2 * y3 +
    8 * a * b_cubed * x1 * x2 * x3 * y1 * y3_squared +
    8 * a * b_cubed * x1 * x2 * x3 * y2_squared * y3 +
    8 * a * b_cubed * x1 * x2 * x3 * y2 * y3_squared -
    4 * a * b_cubed * x1 * x3_squared * y1_squared * y2 -
    4 * a * b_cubed * x1 * x3_squared * y1_squared * y3 +
    4 * a * b_cubed * x1 * x3_squared * y1 * y2_squared +
    12 * a * b_cubed * x1 * x3_squared * y1 * y2 * y3 -
    8 * a * b_cubed * x1 * x3_squared * y2_squared * y3 +
    4 * a * b_cubed * x2_cubed * x3_squared * y2 -
    4 * a * b_cubed * x2_cubed * x3_squared * y3 +
    4 * a * b_cubed * x2_cubed * y1_squared * y2 -
    8 * a * b_cubed * x2_cubed * y1 * y2 * y3 +
    4 * a * b_cubed * x2_cubed * y2 * y3_squared -
    4 * a * b_cubed * x2_squared * x3_cubed * y2 +
    4 * a * b_cubed * x2_squared * x3_cubed * y3 -
    8 * a * b_cubed * x2_squared * x3 * y1_squared * y2 +
    4 * a * b_cubed * x2_squared * x3 * y1_squared * y3 +
    12 * a * b_cubed * x2_squared * x3 * y1 * y2 * y3 -
    4 * a * b_cubed * x2_squared * x3 * y1 * y3_squared -
    4 * a * b_cubed * x2_squared * x3 * y2 * y3_squared +
    4 * a * b_cubed * x2 * x3_squared * y1_squared * y2 -
    8 * a * b_cubed * x2 * x3_squared * y1_squared * y3 -
    4 * a * b_cubed * x2 * x3_squared * y1 * y2_squared +
    12 * a * b_cubed * x2 * x3_squared * y1 * y2 * y3 -
    4 * a * b_cubed * x2 * x3_squared * y2_squared * y3 +
    4 * a * b_cubed * x3_cubed * y1_squared * y3 -
    8 * a * b_cubed * x3_cubed * y1 * y2 * y3 +
    4 * a * b_cubed * x3_cubed * y2_squared * y3 -
    b_fourth * x1_fourth * x2_squared +
    2 * b_fourth * x1_fourth * x2 * x3 -
    b_fourth * x1_fourth * x3_squared -
    b_fourth * x1_fourth * y2_squared +
    2 * b_fourth * x1_fourth * y2 * y3 -
    b_fourth * x1_fourth * y3_squared +
    2 * b_fourth * x1_cubed * x2_cubed -
    2 * b_fourth * x1_cubed * x2_squared * x3 -
    2 * b_fourth * x1_cubed * x2 * x3_squared -
    4 * b_fourth * x1_cubed * x2 * y2 * y3 +
    4 * b_fourth * x1_cubed * x2 * y3_squared +
    2 * b_fourth * x1_cubed * x3_cubed +
    4 * b_fourth * x1_cubed * x3 * y2_squared -
    4 * b_fourth * x1_cubed * x3 * y2 * y3 -
    b_fourth * x1_squared * x2_fourth -
    2 * b_fourth * x1_squared * x2_cubed * x3 +
    6 * b_fourth * x1_squared * x2_squared * x3_squared +
    2 * b_fourth * x1_squared * x2_squared * y1 * y2 +
    2 * b_fourth * x1_squared * x2_squared * y1 * y3 +
    2 * b_fourth * x1_squared * x2_squared * y2 * y3 -
    6 * b_fourth * x1_squared * x2_squared * y3_squared -
    2 * b_fourth * x1_squared * x2 * x3_cubed -
    4 * b_fourth * x1_squared * x2 * x3 * y1 * y2 -
    4 * b_fourth * x1_squared * x2 * x3 * y1 * y3 +
    8 * b_fourth * x1_squared * x2 * x3 * y2 * y3 -
    b_fourth * x1_squared * x3_fourth +
    2 * b_fourth * x1_squared * x3_squared * y1 * y2 +
    2 * b_fourth * x1_squared * x3_squared * y1 * y3 -
    6 * b_fourth * x1_squared * x3_squared * y2_squared +
    2 * b_fourth * x1_squared * x3_squared * y2 * y3 +
    2 * b_fourth * x1 * x2_fourth * x3 -
    2 * b_fourth * x1 * x2_cubed * x3_squared -
    4 * b_fourth * x1 * x2_cubed * y1 * y3 +
    4 * b_fourth * x1 * x2_cubed * y3_squared -
    2 * b_fourth * x1 * x2_squared * x3_cubed -
    4 * b_fourth * x1 * x2_squared * x3 * y1 * y2 +
    8 * b_fourth * x1 * x2_squared * x3 * y1 * y3 -
    4 * b_fourth * x1 * x2_squared * x3 * y2 * y3 +
    2 * b_fourth * x1 * x2 * x3_fourth +
    8 * b_fourth * x1 * x2 * x3_squared * y1 * y2 -
    4 * b_fourth * x1 * x2 * x3_squared * y1 * y3 -
    4 * b_fourth * x1 * x2 * x3_squared * y2 * y3 -
    4 * b_fourth * x1 * x3_cubed * y1 * y2 +
    4 * b_fourth * x1 * x3_cubed * y2_squared -
    b_fourth * x2_fourth * x3_squared -
    b_fourth * x2_fourth * y1_squared +
    2 * b_fourth * x2_fourth * y1 * y3 -
    b_fourth * x2_fourth * y3_squared +
    2 * b_fourth * x2_cubed * x3_cubed +
    4 * b_fourth * x2_cubed * x3 * y1_squared -
    4 * b_fourth * x2_cubed * x3 * y1 * y3 -
    b_fourth * x2_squared * x3_fourth -
    6 * b_fourth * x2_squared * x3_squared * y1_squared +
    2 * b_fourth * x2_squared * x3_squared * y1 * y2 +
    2 * b_fourth * x2_squared * x3_squared * y1 * y3 +
    2 * b_fourth * x2_squared * x3_squared * y2 * y3 +
    4 * b_fourth * x2 * x3_cubed * y1_squared -
    4 * b_fourth * x2 * x3_cubed * y1 * y2 -
    b_fourth * x3_fourth * y1_squared +
    2 * b_fourth * x3_fourth * y1 * y2 -
    b_fourth * x3_fourth * y2_squared) /
    (4 * (x1 * y2 - x2 * y1 - x1 * y3 + x3 * y1 + x2 * y3 - x3 * y2) *
      (a_cubed * y1_squared * y2 - a_cubed * y1_squared * y3 -
        a_cubed * y1 * y2_squared + a_cubed * y1 * y3_squared +
        a_cubed * y2_squared * y3 - a_cubed * y2 * y3_squared -
        2 * a_squared * b * x1 * y1 * y2 + 2 * a_squared * b * x1 * y1 * y3 +
        a_squared * b * x1 * y2_squared - a_squared * b * x1 * y3_squared -
        a_squared * b * x2 * y1_squared + 2 * a_squared * b * x2 * y1 * y2 -
        2 * a_squared * b * x2 * y2 * y3 + a_squared * b * x2 * y3_squared +
        a_squared * b * x3 * y1_squared - 2 * a_squared * b * x3 * y1 * y3 -
        a_squared * b * x3 * y2_squared + 2 * a_squared * b * x3 * y2 * y3 +
        a * b_squared * x1_squared * y2 - a * b_squared * x1_squared * y3 +
        2 * a * b_squared * x1 * x2 * y1 - 2 * a * b_squared * x1 * x2 * y2 -
        2 * a * b_squared * x1 * x3 * y1 + 2 * a * b_squared * x1 * x3 * y3 -
        a * b_squared * x2_squared * y1 + a * b_squared * x2_squared * y3 +
        2 * a * b_squared * x2 * x3 * y2 - 2 * a * b_squared * x2 * x3 * y3 +
        a * b_squared * x3_squared * y1 - a * b_squared * x3_squared * y2 -
        b_cubed * x1_squared * x2 + b_cubed * x1_squared * x3 +
        b_cubed * x1 * x2_squared - b_cubed * x1 * x3_squared -
        b_cubed * x2_squared * x3 + b_cubed * x2 * x3_squared));
}

void TriangleParabolaDirectrixLine::Update()
{
	sf::Vector2f center_of_mass(0, 0);
	const auto& points = m_triangle->GetPoints();
	for (const auto& point : points)
	{
		center_of_mass.x += point->position.x / 3;
		center_of_mass.y += point->position.y / 3;
	}

	float dx = center_of_mass.x - m_center_of_mass.x;
	float dy = center_of_mass.y - m_center_of_mass.y;
	if (dx * dx + dy * dy > 0.01)
	{
		m_center_of_mass = center_of_mass;

		a = m_segment->GetPoint(1)->position.y - m_segment->GetPoint(2)->position.y;
		b = m_segment->GetPoint(2)->position.x - m_segment->GetPoint(1)->position.x;

		c = GetC(a,b,points[0],points[1],points[2]);
	}
}

void TriangleParabolaDirectrixLine::Draw(Window& window)
{
	Update();

	sf::View* view = window.GetView("main");

	float left = view->getCenter().x - view->getSize().x * .5;
	float right = view->getCenter().x + view->getSize().x * .5;
	float top = view->getCenter().y - view->getSize().y * .5;
	float bottom = view->getCenter().y + view->getSize().y * .5;

	sf::Vertex v1;
	sf::Vertex v2;

	// x = -(c + by)/a

	float windowSlope = window.GetSize().y / window.GetSize().x;
	float lineSlope = -a / b;

	if (lineSlope >= -windowSlope && lineSlope <= windowSlope)
	{
		v1.position = sf::Vector2f(left, -(c + a * left) / b);
		v2.position = sf::Vector2f(right, -(c + a * right) / b);
	}
	else {
		v1.position = sf::Vector2f(-(c + b * top) / a, top);
		v2.position = sf::Vector2f(-(c + b * bottom) / a, bottom);
	}

	sf::Vertex line[] = { v1, v2 };
	line[0].color = color;
	line[1].color = color;
	window.DrawLines(line, 2);
}
