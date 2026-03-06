#include "./Point.h"
#include "../Graphics/Window.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../Constants/Constants.h"
#include "Source/Components/Triangle.h"
#include "Source/Components/Segment.h"
#include <cmath>

float IPoint::SquareDistance(sf::Vector2f position_) const
{
	float dx = position_.x - position.x;
	float dy = position_.y - position.y;
	return dx * dx + dy * dy;
}

float IPoint::Distance(sf::Vector2f position_) const
{
	float dx = position_.x - position.x;
	float dy = position_.y - position.y;
	return std::sqrt(dx * dx + dy * dy);
}

Point IPoint::MidPoint(Point& other)
{
	return Point(sf::Vector2f((position.x + other.position.x) / 2, (position.y + other.position.y) / 2));
}

Point::Point(sf::Vector2f position_)
{
	position = position_;
	m_shape = new sf::CircleShape;
	m_shape->setRadius(Constants::POINT_RADIUS);
	m_shape->setOrigin(Constants::POINT_RADIUS,Constants::POINT_RADIUS);
	m_shape->setPosition(position_);
	m_shape->setFillColor(Constants::POINT_COLOR);
}

Point::Point(const IPoint& other)
{
	m_shape = new sf::CircleShape(*other.m_shape);
	position = other.position;
}

Point::~Point()
{
	delete m_shape;
}

void Point::Draw(Window& window)
{
	float scale = window.GetScale(window.GetView("main"));
	m_shape->setScale(scale, scale);
	Update();
	window.Draw(*m_shape);
}

void Point::Update()
{
	m_shape->setPosition(position);
	
	if (selected)
	{
		m_shape->setFillColor(Constants::SELECTED_POINT_COLOR);
		m_shape->setOutlineThickness(2);
		m_shape->setOutlineColor(sf::Color(255, 255, 255));
	}
	else
	{
		m_shape->setFillColor(Constants::POINT_COLOR);
		m_shape->setOutlineThickness(0);
	}
}

TriangleParabolaFocusPoint::TriangleParabolaFocusPoint(Triangle* triangle, Segment* segment) : m_segment(segment),m_triangle(triangle)
{
	m_shape = new sf::CircleShape;
	m_shape->setRadius(Constants::POINT_RADIUS * 0.5);
	m_shape->setOrigin(Constants::POINT_RADIUS * 0.5, Constants::POINT_RADIUS * 0.5);
	m_shape->setFillColor(sf::Color(245, 42, 245));
	sf::Vector2f center_of_mass(-999999999999,-999999999);
	m_center_of_mass = center_of_mass;
}

TriangleParabolaFocusPoint::~TriangleParabolaFocusPoint()
{
	delete m_shape;
}

void TriangleParabolaFocusPoint::Draw(Window& window)
{
	float scale = window.GetScale(window.GetView("main"));
	m_shape->setScale(scale, scale);
	Update();
	m_shape->setPosition(position);

	if (selected)
	{
		m_shape->setFillColor(Constants::SELECTED_POINT_COLOR);
		m_shape->setOutlineThickness(2);
		m_shape->setOutlineColor(sf::Color(255, 255, 255));
	}
	else
	{
		m_shape->setFillColor(sf::Color(245, 42, 245));
		m_shape->setOutlineThickness(0);
	}
	window.Draw(*m_shape);
}

static constexpr float GetF1(float a, float b, IPoint* A, IPoint* B,
  IPoint* C) {
  const float x1 = A->position.x;
  const float x2 = B->position.x;
  const float x3 = C->position.x;
  const float y1 = A->position.y;
  const float y2 = B->position.y;
  const float y3 = C->position.y;

  const float a_squared = a * a;
  const float a_cubed = a * a * a;
  const float a_fourth = a * a * a * a;
  const float a_fifth = a * a * a * a * a;
  const float b_squared = b * b;
  const float b_cubed = b * b * b;
  const float b_fourth = b * b * b * b;
  const float b_fifth = b * b * b * b * b;
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

  return -(a_fifth * x1_squared * y2_fourth -
    4 * a_fifth * x1_squared * y2_cubed * y3 +
    6 * a_fifth * x1_squared * y2_squared * y3_squared -
    4 * a_fifth * x1_squared * y2 * y3_cubed +
    a_fifth * x1_squared * y3_fourth -
    2 * a_fifth * x1 * x2 * y1_squared * y2_squared +
    4 * a_fifth * x1 * x2 * y1_squared * y2 * y3 -
    2 * a_fifth * x1 * x2 * y1_squared * y3_squared +
    4 * a_fifth * x1 * x2 * y1 * y2_squared * y3 -
    8 * a_fifth * x1 * x2 * y1 * y2 * y3_squared +
    4 * a_fifth * x1 * x2 * y1 * y3_cubed -
    2 * a_fifth * x1 * x2 * y2_squared * y3_squared +
    4 * a_fifth * x1 * x2 * y2 * y3_cubed -
    2 * a_fifth * x1 * x2 * y3_fourth -
    2 * a_fifth * x1 * x3 * y1_squared * y2_squared +
    4 * a_fifth * x1 * x3 * y1_squared * y2 * y3 -
    2 * a_fifth * x1 * x3 * y1_squared * y3_squared +
    4 * a_fifth * x1 * x3 * y1 * y2_cubed -
    8 * a_fifth * x1 * x3 * y1 * y2_squared * y3 +
    4 * a_fifth * x1 * x3 * y1 * y2 * y3_squared -
    2 * a_fifth * x1 * x3 * y2_fourth +
    4 * a_fifth * x1 * x3 * y2_cubed * y3 -
    2 * a_fifth * x1 * x3 * y2_squared * y3_squared +
    a_fifth * x2_squared * y1_fourth -
    4 * a_fifth * x2_squared * y1_cubed * y3 +
    6 * a_fifth * x2_squared * y1_squared * y3_squared -
    4 * a_fifth * x2_squared * y1 * y3_cubed +
    a_fifth * x2_squared * y3_fourth -
    2 * a_fifth * x2 * x3 * y1_fourth +
    4 * a_fifth * x2 * x3 * y1_cubed * y2 +
    4 * a_fifth * x2 * x3 * y1_cubed * y3 -
    2 * a_fifth * x2 * x3 * y1_squared * y2_squared -
    8 * a_fifth * x2 * x3 * y1_squared * y2 * y3 -
    2 * a_fifth * x2 * x3 * y1_squared * y3_squared +
    4 * a_fifth * x2 * x3 * y1 * y2_squared * y3 +
    4 * a_fifth * x2 * x3 * y1 * y2 * y3_squared -
    2 * a_fifth * x2 * x3 * y2_squared * y3_squared +
    a_fifth * x3_squared * y1_fourth -
    4 * a_fifth * x3_squared * y1_cubed * y2 +
    6 * a_fifth * x3_squared * y1_squared * y2_squared -
    4 * a_fifth * x3_squared * y1 * y2_cubed +
    a_fifth * x3_squared * y2_fourth - a_fifth * y1_fourth * y2_squared +
    2 * a_fifth * y1_fourth * y2 * y3 -
    a_fifth * y1_fourth * y3_squared +
    2 * a_fifth * y1_cubed * y2_cubed -
    2 * a_fifth * y1_cubed * y2_squared * y3 -
    2 * a_fifth * y1_cubed * y2 * y3_squared +
    2 * a_fifth * y1_cubed * y3_cubed -
    a_fifth * y1_squared * y2_fourth -
    2 * a_fifth * y1_squared * y2_cubed * y3 +
    6 * a_fifth * y1_squared * y2_squared * y3_squared -
    2 * a_fifth * y1_squared * y2 * y3_cubed -
    a_fifth * y1_squared * y3_fourth +
    2 * a_fifth * y1 * y2_fourth * y3 -
    2 * a_fifth * y1 * y2_cubed * y3_squared -
    2 * a_fifth * y1 * y2_squared * y3_cubed +
    2 * a_fifth * y1 * y2 * y3_fourth -
    a_fifth * y2_fourth * y3_squared +
    2 * a_fifth * y2_cubed * y3_cubed -
    a_fifth * y2_squared * y3_fourth +
    4 * a_fourth * b * x1_squared * x2 * y1 * y2_squared -
    8 * a_fourth * b * x1_squared * x2 * y1 * y2 * y3 +
    4 * a_fourth * b * x1_squared * x2 * y1 * y3_squared -
    4 * a_fourth * b * x1_squared * x2 * y2_cubed +
    8 * a_fourth * b * x1_squared * x2 * y2_squared * y3 -
    4 * a_fourth * b * x1_squared * x2 * y2 * y3_squared +
    4 * a_fourth * b * x1_squared * x3 * y1 * y2_squared -
    8 * a_fourth * b * x1_squared * x3 * y1 * y2 * y3 +
    4 * a_fourth * b * x1_squared * x3 * y1 * y3_squared -
    4 * a_fourth * b * x1_squared * x3 * y2_squared * y3 +
    8 * a_fourth * b * x1_squared * x3 * y2 * y3_squared -
    4 * a_fourth * b * x1_squared * x3 * y3_cubed -
    4 * a_fourth * b * x1 * x2_squared * y1_cubed +
    4 * a_fourth * b * x1 * x2_squared * y1_squared * y2 +
    8 * a_fourth * b * x1 * x2_squared * y1_squared * y3 -
    8 * a_fourth * b * x1 * x2_squared * y1 * y2 * y3 -
    4 * a_fourth * b * x1 * x2_squared * y1 * y3_squared +
    4 * a_fourth * b * x1 * x2_squared * y2 * y3_squared +
    8 * a_fourth * b * x1 * x2 * x3 * y1_cubed -
    12 * a_fourth * b * x1 * x2 * x3 * y1_squared * y2 -
    12 * a_fourth * b * x1 * x2 * x3 * y1_squared * y3 -
    12 * a_fourth * b * x1 * x2 * x3 * y1 * y2_squared +
    48 * a_fourth * b * x1 * x2 * x3 * y1 * y2 * y3 -
    12 * a_fourth * b * x1 * x2 * x3 * y1 * y3_squared +
    8 * a_fourth * b * x1 * x2 * x3 * y2_cubed -
    12 * a_fourth * b * x1 * x2 * x3 * y2_squared * y3 -
    12 * a_fourth * b * x1 * x2 * x3 * y2 * y3_squared +
    8 * a_fourth * b * x1 * x2 * x3 * y3_cubed -
    4 * a_fourth * b * x1 * x3_squared * y1_cubed +
    8 * a_fourth * b * x1 * x3_squared * y1_squared * y2 +
    4 * a_fourth * b * x1 * x3_squared * y1_squared * y3 -
    4 * a_fourth * b * x1 * x3_squared * y1 * y2_squared -
    8 * a_fourth * b * x1 * x3_squared * y1 * y2 * y3 +
    4 * a_fourth * b * x1 * x3_squared * y2_squared * y3 +
    4 * a_fourth * b * x1 * y1_cubed * y2_squared -
    8 * a_fourth * b * x1 * y1_cubed * y2 * y3 +
    4 * a_fourth * b * x1 * y1_cubed * y3_squared -
    6 * a_fourth * b * x1 * y1_squared * y2_cubed +
    6 * a_fourth * b * x1 * y1_squared * y2_squared * y3 +
    6 * a_fourth * b * x1 * y1_squared * y2 * y3_squared -
    6 * a_fourth * b * x1 * y1_squared * y3_cubed +
    2 * a_fourth * b * x1 * y1 * y2_fourth +
    4 * a_fourth * b * x1 * y1 * y2_cubed * y3 -
    12 * a_fourth * b * x1 * y1 * y2_squared * y3_squared +
    4 * a_fourth * b * x1 * y1 * y2 * y3_cubed +
    2 * a_fourth * b * x1 * y1 * y3_fourth -
    2 * a_fourth * b * x1 * y2_fourth * y3 +
    2 * a_fourth * b * x1 * y2_cubed * y3_squared +
    2 * a_fourth * b * x1 * y2_squared * y3_cubed -
    2 * a_fourth * b * x1 * y2 * y3_fourth +
    4 * a_fourth * b * x2_squared * x3 * y1_squared * y2 -
    4 * a_fourth * b * x2_squared * x3 * y1_squared * y3 -
    8 * a_fourth * b * x2_squared * x3 * y1 * y2 * y3 +
    8 * a_fourth * b * x2_squared * x3 * y1 * y3_squared +
    4 * a_fourth * b * x2_squared * x3 * y2 * y3_squared -
    4 * a_fourth * b * x2_squared * x3 * y3_cubed -
    4 * a_fourth * b * x2 * x3_squared * y1_squared * y2 +
    4 * a_fourth * b * x2 * x3_squared * y1_squared * y3 +
    8 * a_fourth * b * x2 * x3_squared * y1 * y2_squared -
    8 * a_fourth * b * x2 * x3_squared * y1 * y2 * y3 -
    4 * a_fourth * b * x2 * x3_squared * y2_cubed +
    4 * a_fourth * b * x2 * x3_squared * y2_squared * y3 +
    2 * a_fourth * b * x2 * y1_fourth * y2 -
    2 * a_fourth * b * x2 * y1_fourth * y3 -
    6 * a_fourth * b * x2 * y1_cubed * y2_squared +
    4 * a_fourth * b * x2 * y1_cubed * y2 * y3 +
    2 * a_fourth * b * x2 * y1_cubed * y3_squared +
    4 * a_fourth * b * x2 * y1_squared * y2_cubed +
    6 * a_fourth * b * x2 * y1_squared * y2_squared * y3 -
    12 * a_fourth * b * x2 * y1_squared * y2 * y3_squared +
    2 * a_fourth * b * x2 * y1_squared * y3_cubed -
    8 * a_fourth * b * x2 * y1 * y2_cubed * y3 +
    6 * a_fourth * b * x2 * y1 * y2_squared * y3_squared +
    4 * a_fourth * b * x2 * y1 * y2 * y3_cubed -
    2 * a_fourth * b * x2 * y1 * y3_fourth +
    4 * a_fourth * b * x2 * y2_cubed * y3_squared -
    6 * a_fourth * b * x2 * y2_squared * y3_cubed +
    2 * a_fourth * b * x2 * y2 * y3_fourth -
    2 * a_fourth * b * x3 * y1_fourth * y2 +
    2 * a_fourth * b * x3 * y1_fourth * y3 +
    2 * a_fourth * b * x3 * y1_cubed * y2_squared +
    4 * a_fourth * b * x3 * y1_cubed * y2 * y3 -
    6 * a_fourth * b * x3 * y1_cubed * y3_squared +
    2 * a_fourth * b * x3 * y1_squared * y2_cubed -
    12 * a_fourth * b * x3 * y1_squared * y2_squared * y3 +
    6 * a_fourth * b * x3 * y1_squared * y2 * y3_squared +
    4 * a_fourth * b * x3 * y1_squared * y3_cubed -
    2 * a_fourth * b * x3 * y1 * y2_fourth +
    4 * a_fourth * b * x3 * y1 * y2_cubed * y3 +
    6 * a_fourth * b * x3 * y1 * y2_squared * y3_squared -
    8 * a_fourth * b * x3 * y1 * y2 * y3_cubed +
    2 * a_fourth * b * x3 * y2_fourth * y3 -
    6 * a_fourth * b * x3 * y2_cubed * y3_squared +
    4 * a_fourth * b * x3 * y2_squared * y3_cubed -
    2 * a_cubed * b_squared * x1_cubed * x2 * y2_squared +
    4 * a_cubed * b_squared * x1_cubed * x2 * y2 * y3 -
    2 * a_cubed * b_squared * x1_cubed * x2 * y3_squared -
    2 * a_cubed * b_squared * x1_cubed * x3 * y2_squared +
    4 * a_cubed * b_squared * x1_cubed * x3 * y2 * y3 -
    2 * a_cubed * b_squared * x1_cubed * x3 * y3_squared +
    6 * a_cubed * b_squared * x1_squared * x2_squared * y1_squared -
    8 * a_cubed * b_squared * x1_squared * x2_squared * y1 * y2 -
    4 * a_cubed * b_squared * x1_squared * x2_squared * y1 * y3 +
    6 * a_cubed * b_squared * x1_squared * x2_squared * y2_squared -
    4 * a_cubed * b_squared * x1_squared * x2_squared * y2 * y3 +
    4 * a_cubed * b_squared * x1_squared * x2_squared * y3_squared -
    12 * a_cubed * b_squared * x1_squared * x2 * x3 * y1_squared +
    12 * a_cubed * b_squared * x1_squared * x2 * x3 * y1 * y2 +
    12 * a_cubed * b_squared * x1_squared * x2 * x3 * y1 * y3 +
    2 * a_cubed * b_squared * x1_squared * x2 * x3 * y2_squared -
    16 * a_cubed * b_squared * x1_squared * x2 * x3 * y2 * y3 +
    2 * a_cubed * b_squared * x1_squared * x2 * x3 * y3_squared +
    6 * a_cubed * b_squared * x1_squared * x3_squared * y1_squared -
    4 * a_cubed * b_squared * x1_squared * x3_squared * y1 * y2 -
    8 * a_cubed * b_squared * x1_squared * x3_squared * y1 * y3 +
    4 * a_cubed * b_squared * x1_squared * x3_squared * y2_squared -
    4 * a_cubed * b_squared * x1_squared * x3_squared * y2 * y3 +
    6 * a_cubed * b_squared * x1_squared * x3_squared * y3_squared -
    6 * a_cubed * b_squared * x1_squared * y1_squared * y2_squared +
    12 * a_cubed * b_squared * x1_squared * y1_squared * y2 * y3 -
    6 * a_cubed * b_squared * x1_squared * y1_squared * y3_squared +
    6 * a_cubed * b_squared * x1_squared * y1 * y2_cubed -
    6 * a_cubed * b_squared * x1_squared * y1 * y2_squared * y3 -
    6 * a_cubed * b_squared * x1_squared * y1 * y2 * y3_squared +
    6 * a_cubed * b_squared * x1_squared * y1 * y3_cubed -
    6 * a_cubed * b_squared * x1_squared * y2_cubed * y3 +
    12 * a_cubed * b_squared * x1_squared * y2_squared * y3_squared -
    6 * a_cubed * b_squared * x1_squared * y2 * y3_cubed -
    2 * a_cubed * b_squared * x1 * x2_cubed * y1_squared +
    4 * a_cubed * b_squared * x1 * x2_cubed * y1 * y3 -
    2 * a_cubed * b_squared * x1 * x2_cubed * y3_squared +
    2 * a_cubed * b_squared * x1 * x2_squared * x3 * y1_squared +
    12 * a_cubed * b_squared * x1 * x2_squared * x3 * y1 * y2 -
    16 * a_cubed * b_squared * x1 * x2_squared * x3 * y1 * y3 -
    12 * a_cubed * b_squared * x1 * x2_squared * x3 * y2_squared +
    12 * a_cubed * b_squared * x1 * x2_squared * x3 * y2 * y3 +
    2 * a_cubed * b_squared * x1 * x2_squared * x3 * y3_squared +
    2 * a_cubed * b_squared * x1 * x2 * x3_squared * y1_squared -
    16 * a_cubed * b_squared * x1 * x2 * x3_squared * y1 * y2 +
    12 * a_cubed * b_squared * x1 * x2 * x3_squared * y1 * y3 +
    2 * a_cubed * b_squared * x1 * x2 * x3_squared * y2_squared +
    12 * a_cubed * b_squared * x1 * x2 * x3_squared * y2 * y3 -
    12 * a_cubed * b_squared * x1 * x2 * x3_squared * y3_squared -
    8 * a_cubed * b_squared * x1 * x2 * y1_cubed * y2 +
    8 * a_cubed * b_squared * x1 * x2 * y1_cubed * y3 +
    16 * a_cubed * b_squared * x1 * x2 * y1_squared * y2_squared -
    8 * a_cubed * b_squared * x1 * x2 * y1_squared * y2 * y3 -
    8 * a_cubed * b_squared * x1 * x2 * y1_squared * y3_squared -
    8 * a_cubed * b_squared * x1 * x2 * y1 * y2_cubed -
    8 * a_cubed * b_squared * x1 * x2 * y1 * y2_squared * y3 +
    16 * a_cubed * b_squared * x1 * x2 * y1 * y2 * y3_squared +
    8 * a_cubed * b_squared * x1 * x2 * y2_cubed * y3 -
    8 * a_cubed * b_squared * x1 * x2 * y2_squared * y3_squared -
    2 * a_cubed * b_squared * x1 * x3_cubed * y1_squared +
    4 * a_cubed * b_squared * x1 * x3_cubed * y1 * y2 -
    2 * a_cubed * b_squared * x1 * x3_cubed * y2_squared +
    8 * a_cubed * b_squared * x1 * x3 * y1_cubed * y2 -
    8 * a_cubed * b_squared * x1 * x3 * y1_cubed * y3 -
    8 * a_cubed * b_squared * x1 * x3 * y1_squared * y2_squared -
    8 * a_cubed * b_squared * x1 * x3 * y1_squared * y2 * y3 +
    16 * a_cubed * b_squared * x1 * x3 * y1_squared * y3_squared +
    16 * a_cubed * b_squared * x1 * x3 * y1 * y2_squared * y3 -
    8 * a_cubed * b_squared * x1 * x3 * y1 * y2 * y3_squared -
    8 * a_cubed * b_squared * x1 * x3 * y1 * y3_cubed -
    8 * a_cubed * b_squared * x1 * x3 * y2_squared * y3_squared +
    8 * a_cubed * b_squared * x1 * x3 * y2 * y3_cubed -
    2 * a_cubed * b_squared * x2_cubed * x3 * y1_squared +
    4 * a_cubed * b_squared * x2_cubed * x3 * y1 * y3 -
    2 * a_cubed * b_squared * x2_cubed * x3 * y3_squared +
    4 * a_cubed * b_squared * x2_squared * x3_squared * y1_squared -
    4 * a_cubed * b_squared * x2_squared * x3_squared * y1 * y2 -
    4 * a_cubed * b_squared * x2_squared * x3_squared * y1 * y3 +
    6 * a_cubed * b_squared * x2_squared * x3_squared * y2_squared -
    8 * a_cubed * b_squared * x2_squared * x3_squared * y2 * y3 +
    6 * a_cubed * b_squared * x2_squared * x3_squared * y3_squared +
    6 * a_cubed * b_squared * x2_squared * y1_cubed * y2 -
    6 * a_cubed * b_squared * x2_squared * y1_cubed * y3 -
    6 * a_cubed * b_squared * x2_squared * y1_squared * y2_squared -
    6 * a_cubed * b_squared * x2_squared * y1_squared * y2 * y3 +
    12 * a_cubed * b_squared * x2_squared * y1_squared * y3_squared +
    12 * a_cubed * b_squared * x2_squared * y1 * y2_squared * y3 -
    6 * a_cubed * b_squared * x2_squared * y1 * y2 * y3_squared -
    6 * a_cubed * b_squared * x2_squared * y1 * y3_cubed -
    6 * a_cubed * b_squared * x2_squared * y2_squared * y3_squared +
    6 * a_cubed * b_squared * x2_squared * y2 * y3_cubed -
    2 * a_cubed * b_squared * x2 * x3_cubed * y1_squared +
    4 * a_cubed * b_squared * x2 * x3_cubed * y1 * y2 -
    2 * a_cubed * b_squared * x2 * x3_cubed * y2_squared -
    8 * a_cubed * b_squared * x2 * x3 * y1_squared * y2_squared +
    16 * a_cubed * b_squared * x2 * x3 * y1_squared * y2 * y3 -
    8 * a_cubed * b_squared * x2 * x3 * y1_squared * y3_squared +
    8 * a_cubed * b_squared * x2 * x3 * y1 * y2_cubed -
    8 * a_cubed * b_squared * x2 * x3 * y1 * y2_squared * y3 -
    8 * a_cubed * b_squared * x2 * x3 * y1 * y2 * y3_squared +
    8 * a_cubed * b_squared * x2 * x3 * y1 * y3_cubed -
    8 * a_cubed * b_squared * x2 * x3 * y2_cubed * y3 +
    16 * a_cubed * b_squared * x2 * x3 * y2_squared * y3_squared -
    8 * a_cubed * b_squared * x2 * x3 * y2 * y3_cubed -
    6 * a_cubed * b_squared * x3_squared * y1_cubed * y2 +
    6 * a_cubed * b_squared * x3_squared * y1_cubed * y3 +
    12 * a_cubed * b_squared * x3_squared * y1_squared * y2_squared -
    6 * a_cubed * b_squared * x3_squared * y1_squared * y2 * y3 -
    6 * a_cubed * b_squared * x3_squared * y1_squared * y3_squared -
    6 * a_cubed * b_squared * x3_squared * y1 * y2_cubed -
    6 * a_cubed * b_squared * x3_squared * y1 * y2_squared * y3 +
    12 * a_cubed * b_squared * x3_squared * y1 * y2 * y3_squared +
    6 * a_cubed * b_squared * x3_squared * y2_cubed * y3 -
    6 * a_cubed * b_squared * x3_squared * y2_squared * y3_squared -
    4 * a_squared * b_cubed * x1_cubed * x2_squared * y1 +
    4 * a_squared * b_cubed * x1_cubed * x2_squared * y2 +
    8 * a_squared * b_cubed * x1_cubed * x2 * x3 * y1 -
    4 * a_squared * b_cubed * x1_cubed * x2 * x3 * y2 -
    4 * a_squared * b_cubed * x1_cubed * x2 * x3 * y3 -
    4 * a_squared * b_cubed * x1_cubed * x3_squared * y1 +
    4 * a_squared * b_cubed * x1_cubed * x3_squared * y3 +
    4 * a_squared * b_cubed * x1_cubed * y1 * y2_squared -
    8 * a_squared * b_cubed * x1_cubed * y1 * y2 * y3 +
    4 * a_squared * b_cubed * x1_cubed * y1 * y3_squared -
    2 * a_squared * b_cubed * x1_cubed * y2_cubed +
    2 * a_squared * b_cubed * x1_cubed * y2_squared * y3 +
    2 * a_squared * b_cubed * x1_cubed * y2 * y3_squared -
    2 * a_squared * b_cubed * x1_cubed * y3_cubed +
    4 * a_squared * b_cubed * x1_squared * x2_cubed * y1 -
    4 * a_squared * b_cubed * x1_squared * x2_cubed * y2 -
    4 * a_squared * b_cubed * x1_squared * x2_squared * x3 * y1 -
    4 * a_squared * b_cubed * x1_squared * x2_squared * x3 * y2 +
    8 * a_squared * b_cubed * x1_squared * x2_squared * x3 * y3 -
    4 * a_squared * b_cubed * x1_squared * x2 * x3_squared * y1 +
    8 * a_squared * b_cubed * x1_squared * x2 * x3_squared * y2 -
    4 * a_squared * b_cubed * x1_squared * x2 * x3_squared * y3 +
    12 * a_squared * b_cubed * x1_squared * x2 * y1_squared * y2 -
    12 * a_squared * b_cubed * x1_squared * x2 * y1_squared * y3 -
    14 * a_squared * b_cubed * x1_squared * x2 * y1 * y2_squared +
    4 * a_squared * b_cubed * x1_squared * x2 * y1 * y2 * y3 +
    10 * a_squared * b_cubed * x1_squared * x2 * y1 * y3_squared +
    14 * a_squared * b_cubed * x1_squared * x2 * y2_squared * y3 -
    16 * a_squared * b_cubed * x1_squared * x2 * y2 * y3_squared +
    2 * a_squared * b_cubed * x1_squared * x2 * y3_cubed +
    4 * a_squared * b_cubed * x1_squared * x3_cubed * y1 -
    4 * a_squared * b_cubed * x1_squared * x3_cubed * y3 -
    12 * a_squared * b_cubed * x1_squared * x3 * y1_squared * y2 +
    12 * a_squared * b_cubed * x1_squared * x3 * y1_squared * y3 +
    10 * a_squared * b_cubed * x1_squared * x3 * y1 * y2_squared +
    4 * a_squared * b_cubed * x1_squared * x3 * y1 * y2 * y3 -
    14 * a_squared * b_cubed * x1_squared * x3 * y1 * y3_squared +
    2 * a_squared * b_cubed * x1_squared * x3 * y2_cubed -
    16 * a_squared * b_cubed * x1_squared * x3 * y2_squared * y3 +
    14 * a_squared * b_cubed * x1_squared * x3 * y2 * y3_squared -
    4 * a_squared * b_cubed * x1 * x2_cubed * x3 * y1 +
    8 * a_squared * b_cubed * x1 * x2_cubed * x3 * y2 -
    4 * a_squared * b_cubed * x1 * x2_cubed * x3 * y3 +
    8 * a_squared * b_cubed * x1 * x2_squared * x3_squared * y1 -
    4 * a_squared * b_cubed * x1 * x2_squared * x3_squared * y2 -
    4 * a_squared * b_cubed * x1 * x2_squared * x3_squared * y3 -
    14 * a_squared * b_cubed * x1 * x2_squared * y1_squared * y2 +
    14 * a_squared * b_cubed * x1 * x2_squared * y1_squared * y3 +
    12 * a_squared * b_cubed * x1 * x2_squared * y1 * y2_squared +
    4 * a_squared * b_cubed * x1 * x2_squared * y1 * y2 * y3 -
    16 * a_squared * b_cubed * x1 * x2_squared * y1 * y3_squared -
    12 * a_squared * b_cubed * x1 * x2_squared * y2_squared * y3 +
    10 * a_squared * b_cubed * x1 * x2_squared * y2 * y3_squared +
    2 * a_squared * b_cubed * x1 * x2_squared * y3_cubed -
    4 * a_squared * b_cubed * x1 * x2 * x3_cubed * y1 -
    4 * a_squared * b_cubed * x1 * x2 * x3_cubed * y2 +
    8 * a_squared * b_cubed * x1 * x2 * x3_cubed * y3 +
    14 * a_squared * b_cubed * x1 * x3_squared * y1_squared * y2 -
    14 * a_squared * b_cubed * x1 * x3_squared * y1_squared * y3 -
    16 * a_squared * b_cubed * x1 * x3_squared * y1 * y2_squared +
    4 * a_squared * b_cubed * x1 * x3_squared * y1 * y2 * y3 +
    12 * a_squared * b_cubed * x1 * x3_squared * y1 * y3_squared +
    2 * a_squared * b_cubed * x1 * x3_squared * y2_cubed +
    10 * a_squared * b_cubed * x1 * x3_squared * y2_squared * y3 -
    12 * a_squared * b_cubed * x1 * x3_squared * y2 * y3_squared -
    4 * a_squared * b_cubed * x2_cubed * x3_squared * y2 +
    4 * a_squared * b_cubed * x2_cubed * x3_squared * y3 -
    2 * a_squared * b_cubed * x2_cubed * y1_cubed +
    4 * a_squared * b_cubed * x2_cubed * y1_squared * y2 +
    2 * a_squared * b_cubed * x2_cubed * y1_squared * y3 -
    8 * a_squared * b_cubed * x2_cubed * y1 * y2 * y3 +
    2 * a_squared * b_cubed * x2_cubed * y1 * y3_squared +
    4 * a_squared * b_cubed * x2_cubed * y2 * y3_squared -
    2 * a_squared * b_cubed * x2_cubed * y3_cubed +
    4 * a_squared * b_cubed * x2_squared * x3_cubed * y2 -
    4 * a_squared * b_cubed * x2_squared * x3_cubed * y3 +
    2 * a_squared * b_cubed * x2_squared * x3 * y1_cubed +
    10 * a_squared * b_cubed * x2_squared * x3 * y1_squared * y2 -
    16 * a_squared * b_cubed * x2_squared * x3 * y1_squared * y3 -
    12 * a_squared * b_cubed * x2_squared * x3 * y1 * y2_squared +
    4 * a_squared * b_cubed * x2_squared * x3 * y1 * y2 * y3 +
    14 * a_squared * b_cubed * x2_squared * x3 * y1 * y3_squared +
    12 * a_squared * b_cubed * x2_squared * x3 * y2_squared * y3 -
    14 * a_squared * b_cubed * x2_squared * x3 * y2 * y3_squared +
    2 * a_squared * b_cubed * x2 * x3_squared * y1_cubed -
    16 * a_squared * b_cubed * x2 * x3_squared * y1_squared * y2 +
    10 * a_squared * b_cubed * x2 * x3_squared * y1_squared * y3 +
    14 * a_squared * b_cubed * x2 * x3_squared * y1 * y2_squared +
    4 * a_squared * b_cubed * x2 * x3_squared * y1 * y2 * y3 -
    12 * a_squared * b_cubed * x2 * x3_squared * y1 * y3_squared -
    14 * a_squared * b_cubed * x2 * x3_squared * y2_squared * y3 +
    12 * a_squared * b_cubed * x2 * x3_squared * y2 * y3_squared -
    2 * a_squared * b_cubed * x3_cubed * y1_cubed +
    2 * a_squared * b_cubed * x3_cubed * y1_squared * y2 +
    4 * a_squared * b_cubed * x3_cubed * y1_squared * y3 +
    2 * a_squared * b_cubed * x3_cubed * y1 * y2_squared -
    8 * a_squared * b_cubed * x3_cubed * y1 * y2 * y3 -
    2 * a_squared * b_cubed * x3_cubed * y2_cubed +
    4 * a_squared * b_cubed * x3_cubed * y2_squared * y3 +
    a * b_fourth * x1_fourth * x2_squared -
    2 * a * b_fourth * x1_fourth * x2 * x3 +
    a * b_fourth * x1_fourth * x3_squared -
    a * b_fourth * x1_fourth * y2_squared +
    2 * a * b_fourth * x1_fourth * y2 * y3 -
    a * b_fourth * x1_fourth * y3_squared -
    2 * a * b_fourth * x1_cubed * x2_cubed +
    2 * a * b_fourth * x1_cubed * x2_squared * x3 +
    2 * a * b_fourth * x1_cubed * x2 * x3_squared -
    8 * a * b_fourth * x1_cubed * x2 * y1 * y2 +
    8 * a * b_fourth * x1_cubed * x2 * y1 * y3 +
    4 * a * b_fourth * x1_cubed * x2 * y2_squared -
    4 * a * b_fourth * x1_cubed * x2 * y3_squared -
    2 * a * b_fourth * x1_cubed * x3_cubed +
    8 * a * b_fourth * x1_cubed * x3 * y1 * y2 -
    8 * a * b_fourth * x1_cubed * x3 * y1 * y3 -
    4 * a * b_fourth * x1_cubed * x3 * y2_squared +
    4 * a * b_fourth * x1_cubed * x3 * y3_squared +
    a * b_fourth * x1_squared * x2_fourth +
    2 * a * b_fourth * x1_squared * x2_cubed * x3 -
    6 * a * b_fourth * x1_squared * x2_squared * x3_squared +
    10 * a * b_fourth * x1_squared * x2_squared * y1 * y2 -
    10 * a * b_fourth * x1_squared * x2_squared * y1 * y3 -
    10 * a * b_fourth * x1_squared * x2_squared * y2 * y3 +
    10 * a * b_fourth * x1_squared * x2_squared * y3_squared +
    2 * a * b_fourth * x1_squared * x2 * x3_cubed -
    4 * a * b_fourth * x1_squared * x2 * x3 * y2_squared +
    8 * a * b_fourth * x1_squared * x2 * x3 * y2 * y3 -
    4 * a * b_fourth * x1_squared * x2 * x3 * y3_squared +
    a * b_fourth * x1_squared * x3_fourth -
    10 * a * b_fourth * x1_squared * x3_squared * y1 * y2 +
    10 * a * b_fourth * x1_squared * x3_squared * y1 * y3 +
    10 * a * b_fourth * x1_squared * x3_squared * y2_squared -
    10 * a * b_fourth * x1_squared * x3_squared * y2 * y3 -
    2 * a * b_fourth * x1 * x2_fourth * x3 +
    2 * a * b_fourth * x1 * x2_cubed * x3_squared +
    4 * a * b_fourth * x1 * x2_cubed * y1_squared -
    8 * a * b_fourth * x1 * x2_cubed * y1 * y2 +
    8 * a * b_fourth * x1 * x2_cubed * y2 * y3 -
    4 * a * b_fourth * x1 * x2_cubed * y3_squared +
    2 * a * b_fourth * x1 * x2_squared * x3_cubed -
    4 * a * b_fourth * x1 * x2_squared * x3 * y1_squared +
    8 * a * b_fourth * x1 * x2_squared * x3 * y1 * y3 -
    4 * a * b_fourth * x1 * x2_squared * x3 * y3_squared -
    2 * a * b_fourth * x1 * x2 * x3_fourth -
    4 * a * b_fourth * x1 * x2 * x3_squared * y1_squared +
    8 * a * b_fourth * x1 * x2 * x3_squared * y1 * y2 -
    4 * a * b_fourth * x1 * x2 * x3_squared * y2_squared +
    4 * a * b_fourth * x1 * x3_cubed * y1_squared -
    8 * a * b_fourth * x1 * x3_cubed * y1 * y3 -
    4 * a * b_fourth * x1 * x3_cubed * y2_squared +
    8 * a * b_fourth * x1 * x3_cubed * y2 * y3 +
    a * b_fourth * x2_fourth * x3_squared -
    a * b_fourth * x2_fourth * y1_squared +
    2 * a * b_fourth * x2_fourth * y1 * y3 -
    a * b_fourth * x2_fourth * y3_squared -
    2 * a * b_fourth * x2_cubed * x3_cubed -
    4 * a * b_fourth * x2_cubed * x3 * y1_squared +
    8 * a * b_fourth * x2_cubed * x3 * y1 * y2 -
    8 * a * b_fourth * x2_cubed * x3 * y2 * y3 +
    4 * a * b_fourth * x2_cubed * x3 * y3_squared +
    a * b_fourth * x2_squared * x3_fourth +
    10 * a * b_fourth * x2_squared * x3_squared * y1_squared -
    10 * a * b_fourth * x2_squared * x3_squared * y1 * y2 -
    10 * a * b_fourth * x2_squared * x3_squared * y1 * y3 +
    10 * a * b_fourth * x2_squared * x3_squared * y2 * y3 -
    4 * a * b_fourth * x2 * x3_cubed * y1_squared +
    8 * a * b_fourth * x2 * x3_cubed * y1 * y3 +
    4 * a * b_fourth * x2 * x3_cubed * y2_squared -
    8 * a * b_fourth * x2 * x3_cubed * y2 * y3 -
    a * b_fourth * x3_fourth * y1_squared +
    2 * a * b_fourth * x3_fourth * y1 * y2 -
    a * b_fourth * x3_fourth * y2_squared +
    2 * b_fifth * x1_fourth * x2 * y2 -
    2 * b_fifth * x1_fourth * x2 * y3 -
    2 * b_fifth * x1_fourth * x3 * y2 +
    2 * b_fifth * x1_fourth * x3 * y3 -
    2 * b_fifth * x1_cubed * x2_squared * y2 +
    2 * b_fifth * x1_cubed * x2_squared * y3 +
    2 * b_fifth * x1_cubed * x3_squared * y2 -
    2 * b_fifth * x1_cubed * x3_squared * y3 -
    2 * b_fifth * x1_squared * x2_cubed * y1 +
    2 * b_fifth * x1_squared * x2_cubed * y3 +
    2 * b_fifth * x1_squared * x2_squared * x3 * y1 +
    2 * b_fifth * x1_squared * x2_squared * x3 * y2 -
    4 * b_fifth * x1_squared * x2_squared * x3 * y3 +
    2 * b_fifth * x1_squared * x2 * x3_squared * y1 -
    4 * b_fifth * x1_squared * x2 * x3_squared * y2 +
    2 * b_fifth * x1_squared * x2 * x3_squared * y3 -
    2 * b_fifth * x1_squared * x3_cubed * y1 +
    2 * b_fifth * x1_squared * x3_cubed * y2 +
    2 * b_fifth * x1 * x2_fourth * y1 -
    2 * b_fifth * x1 * x2_fourth * y3 -
    4 * b_fifth * x1 * x2_squared * x3_squared * y1 +
    2 * b_fifth * x1 * x2_squared * x3_squared * y2 +
    2 * b_fifth * x1 * x2_squared * x3_squared * y3 +
    2 * b_fifth * x1 * x3_fourth * y1 -
    2 * b_fifth * x1 * x3_fourth * y2 -
    2 * b_fifth * x2_fourth * x3 * y1 +
    2 * b_fifth * x2_fourth * x3 * y3 +
    2 * b_fifth * x2_cubed * x3_squared * y1 -
    2 * b_fifth * x2_cubed * x3_squared * y3 +
    2 * b_fifth * x2_squared * x3_cubed * y1 -
    2 * b_fifth * x2_squared * x3_cubed * y2 -
    2 * b_fifth * x2 * x3_fourth * y1 +
    2 * b_fifth * x2 * x3_fourth * y2) /
    (4 * (a_squared + b_squared) *
      (x1 * y2 - x2 * y1 - x1 * y3 + x3 * y1 + x2 * y3 - x3 * y2) *
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
};

static float constexpr GetF2(float a, float b, IPoint* A, IPoint* B,
  IPoint* C) {
  const float x1 = A->position.x;
  const float x2 = B->position.x;
  const float x3 = C->position.x;
  const float y1 = A->position.y;
  const float y2 = B->position.y;
  const float y3 = C->position.y;

  const float a_squared = a * a;
  const float a_cubed = a * a * a;
  const float a_fourth = a * a * a * a;
  const float a_fifth = a * a * a * a * a;
  const float b_squared = b * b;
  const float b_cubed = b * b * b;
  const float b_fourth = b * b * b * b;
  const float b_fifth = b * b * b * b * b;
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

  return -(-2 * a_fifth * x1 * y1_squared * y2_cubed +
    2 * a_fifth * x1 * y1_squared * y2_squared * y3 +
    2 * a_fifth * x1 * y1_squared * y2 * y3_squared -
    2 * a_fifth * x1 * y1_squared * y3_cubed +
    2 * a_fifth * x1 * y1 * y2_fourth -
    4 * a_fifth * x1 * y1 * y2_squared * y3_squared +
    2 * a_fifth * x1 * y1 * y3_fourth -
    2 * a_fifth * x1 * y2_fourth * y3 +
    2 * a_fifth * x1 * y2_cubed * y3_squared +
    2 * a_fifth * x1 * y2_squared * y3_cubed -
    2 * a_fifth * x1 * y2 * y3_fourth +
    2 * a_fifth * x2 * y1_fourth * y2 -
    2 * a_fifth * x2 * y1_fourth * y3 -
    2 * a_fifth * x2 * y1_cubed * y2_squared +
    2 * a_fifth * x2 * y1_cubed * y3_squared +
    2 * a_fifth * x2 * y1_squared * y2_squared * y3 -
    4 * a_fifth * x2 * y1_squared * y2 * y3_squared +
    2 * a_fifth * x2 * y1_squared * y3_cubed +
    2 * a_fifth * x2 * y1 * y2_squared * y3_squared -
    2 * a_fifth * x2 * y1 * y3_fourth -
    2 * a_fifth * x2 * y2_squared * y3_cubed +
    2 * a_fifth * x2 * y2 * y3_fourth -
    2 * a_fifth * x3 * y1_fourth * y2 +
    2 * a_fifth * x3 * y1_fourth * y3 +
    2 * a_fifth * x3 * y1_cubed * y2_squared -
    2 * a_fifth * x3 * y1_cubed * y3_squared +
    2 * a_fifth * x3 * y1_squared * y2_cubed -
    4 * a_fifth * x3 * y1_squared * y2_squared * y3 +
    2 * a_fifth * x3 * y1_squared * y2 * y3_squared -
    2 * a_fifth * x3 * y1 * y2_fourth +
    2 * a_fifth * x3 * y1 * y2_squared * y3_squared +
    2 * a_fifth * x3 * y2_fourth * y3 -
    2 * a_fifth * x3 * y2_cubed * y3_squared +
    4 * a_fourth * b * x1_squared * y1 * y2_cubed -
    4 * a_fourth * b * x1_squared * y1 * y2_squared * y3 -
    4 * a_fourth * b * x1_squared * y1 * y2 * y3_squared +
    4 * a_fourth * b * x1_squared * y1 * y3_cubed -
    a_fourth * b * x1_squared * y2_fourth -
    4 * a_fourth * b * x1_squared * y2_cubed * y3 +
    10 * a_fourth * b * x1_squared * y2_squared * y3_squared -
    4 * a_fourth * b * x1_squared * y2 * y3_cubed -
    a_fourth * b * x1_squared * y3_fourth -
    8 * a_fourth * b * x1 * x2 * y1_cubed * y2 +
    8 * a_fourth * b * x1 * x2 * y1_cubed * y3 +
    10 * a_fourth * b * x1 * x2 * y1_squared * y2_squared -
    10 * a_fourth * b * x1 * x2 * y1_squared * y3_squared -
    8 * a_fourth * b * x1 * x2 * y1 * y2_cubed +
    8 * a_fourth * b * x1 * x2 * y1 * y2 * y3_squared +
    8 * a_fourth * b * x1 * x2 * y2_cubed * y3 -
    10 * a_fourth * b * x1 * x2 * y2_squared * y3_squared +
    2 * a_fourth * b * x1 * x2 * y3_fourth +
    8 * a_fourth * b * x1 * x3 * y1_cubed * y2 -
    8 * a_fourth * b * x1 * x3 * y1_cubed * y3 -
    10 * a_fourth * b * x1 * x3 * y1_squared * y2_squared +
    10 * a_fourth * b * x1 * x3 * y1_squared * y3_squared +
    8 * a_fourth * b * x1 * x3 * y1 * y2_squared * y3 -
    8 * a_fourth * b * x1 * x3 * y1 * y3_cubed +
    2 * a_fourth * b * x1 * x3 * y2_fourth -
    10 * a_fourth * b * x1 * x3 * y2_squared * y3_squared +
    8 * a_fourth * b * x1 * x3 * y2 * y3_cubed -
    a_fourth * b * x2_squared * y1_fourth +
    4 * a_fourth * b * x2_squared * y1_cubed * y2 -
    4 * a_fourth * b * x2_squared * y1_cubed * y3 -
    4 * a_fourth * b * x2_squared * y1_squared * y2 * y3 +
    10 * a_fourth * b * x2_squared * y1_squared * y3_squared -
    4 * a_fourth * b * x2_squared * y1 * y2 * y3_squared -
    4 * a_fourth * b * x2_squared * y1 * y3_cubed +
    4 * a_fourth * b * x2_squared * y2 * y3_cubed -
    a_fourth * b * x2_squared * y3_fourth +
    2 * a_fourth * b * x2 * x3 * y1_fourth -
    10 * a_fourth * b * x2 * x3 * y1_squared * y2_squared +
    8 * a_fourth * b * x2 * x3 * y1_squared * y2 * y3 -
    10 * a_fourth * b * x2 * x3 * y1_squared * y3_squared +
    8 * a_fourth * b * x2 * x3 * y1 * y2_cubed +
    8 * a_fourth * b * x2 * x3 * y1 * y3_cubed -
    8 * a_fourth * b * x2 * x3 * y2_cubed * y3 +
    10 * a_fourth * b * x2 * x3 * y2_squared * y3_squared -
    8 * a_fourth * b * x2 * x3 * y2 * y3_cubed -
    a_fourth * b * x3_squared * y1_fourth -
    4 * a_fourth * b * x3_squared * y1_cubed * y2 +
    4 * a_fourth * b * x3_squared * y1_cubed * y3 +
    10 * a_fourth * b * x3_squared * y1_squared * y2_squared -
    4 * a_fourth * b * x3_squared * y1_squared * y2 * y3 -
    4 * a_fourth * b * x3_squared * y1 * y2_cubed -
    4 * a_fourth * b * x3_squared * y1 * y2_squared * y3 -
    a_fourth * b * x3_squared * y2_fourth +
    4 * a_fourth * b * x3_squared * y2_cubed * y3 +
    a_fourth * b * y1_fourth * y2_squared -
    2 * a_fourth * b * y1_fourth * y2 * y3 +
    a_fourth * b * y1_fourth * y3_squared -
    2 * a_fourth * b * y1_cubed * y2_cubed +
    2 * a_fourth * b * y1_cubed * y2_squared * y3 +
    2 * a_fourth * b * y1_cubed * y2 * y3_squared -
    2 * a_fourth * b * y1_cubed * y3_cubed +
    a_fourth * b * y1_squared * y2_fourth +
    2 * a_fourth * b * y1_squared * y2_cubed * y3 -
    6 * a_fourth * b * y1_squared * y2_squared * y3_squared +
    2 * a_fourth * b * y1_squared * y2 * y3_cubed +
    a_fourth * b * y1_squared * y3_fourth -
    2 * a_fourth * b * y1 * y2_fourth * y3 +
    2 * a_fourth * b * y1 * y2_cubed * y3_squared +
    2 * a_fourth * b * y1 * y2_squared * y3_cubed -
    2 * a_fourth * b * y1 * y2 * y3_fourth +
    a_fourth * b * y2_fourth * y3_squared -
    2 * a_fourth * b * y2_cubed * y3_cubed +
    a_fourth * b * y2_squared * y3_fourth -
    2 * a_cubed * b_squared * x1_cubed * y2_cubed +
    2 * a_cubed * b_squared * x1_cubed * y2_squared * y3 +
    2 * a_cubed * b_squared * x1_cubed * y2 * y3_squared -
    2 * a_cubed * b_squared * x1_cubed * y3_cubed +
    12 * a_cubed * b_squared * x1_squared * x2 * y1_squared * y2 -
    12 * a_cubed * b_squared * x1_squared * x2 * y1_squared * y3 -
    14 * a_cubed * b_squared * x1_squared * x2 * y1 * y2_squared +
    14 * a_cubed * b_squared * x1_squared * x2 * y1 * y3_squared +
    4 * a_cubed * b_squared * x1_squared * x2 * y2_cubed +
    10 * a_cubed * b_squared * x1_squared * x2 * y2_squared * y3 -
    16 * a_cubed * b_squared * x1_squared * x2 * y2 * y3_squared +
    2 * a_cubed * b_squared * x1_squared * x2 * y3_cubed -
    12 * a_cubed * b_squared * x1_squared * x3 * y1_squared * y2 +
    12 * a_cubed * b_squared * x1_squared * x3 * y1_squared * y3 +
    14 * a_cubed * b_squared * x1_squared * x3 * y1 * y2_squared -
    14 * a_cubed * b_squared * x1_squared * x3 * y1 * y3_squared +
    2 * a_cubed * b_squared * x1_squared * x3 * y2_cubed -
    16 * a_cubed * b_squared * x1_squared * x3 * y2_squared * y3 +
    10 * a_cubed * b_squared * x1_squared * x3 * y2 * y3_squared +
    4 * a_cubed * b_squared * x1_squared * x3 * y3_cubed +
    4 * a_cubed * b_squared * x1 * x2_squared * y1_cubed -
    14 * a_cubed * b_squared * x1 * x2_squared * y1_squared * y2 +
    10 * a_cubed * b_squared * x1 * x2_squared * y1_squared * y3 +
    12 * a_cubed * b_squared * x1 * x2_squared * y1 * y2_squared -
    16 * a_cubed * b_squared * x1 * x2_squared * y1 * y3_squared -
    12 * a_cubed * b_squared * x1 * x2_squared * y2_squared * y3 +
    14 * a_cubed * b_squared * x1 * x2_squared * y2 * y3_squared +
    2 * a_cubed * b_squared * x1 * x2_squared * y3_cubed -
    8 * a_cubed * b_squared * x1 * x2 * x3 * y1_cubed +
    4 * a_cubed * b_squared * x1 * x2 * x3 * y1_squared * y2 +
    4 * a_cubed * b_squared * x1 * x2 * x3 * y1_squared * y3 +
    4 * a_cubed * b_squared * x1 * x2 * x3 * y1 * y2_squared +
    4 * a_cubed * b_squared * x1 * x2 * x3 * y1 * y3_squared -
    8 * a_cubed * b_squared * x1 * x2 * x3 * y2_cubed +
    4 * a_cubed * b_squared * x1 * x2 * x3 * y2_squared * y3 +
    4 * a_cubed * b_squared * x1 * x2 * x3 * y2 * y3_squared -
    8 * a_cubed * b_squared * x1 * x2 * x3 * y3_cubed +
    4 * a_cubed * b_squared * x1 * x3_squared * y1_cubed +
    10 * a_cubed * b_squared * x1 * x3_squared * y1_squared * y2 -
    14 * a_cubed * b_squared * x1 * x3_squared * y1_squared * y3 -
    16 * a_cubed * b_squared * x1 * x3_squared * y1 * y2_squared +
    12 * a_cubed * b_squared * x1 * x3_squared * y1 * y3_squared +
    2 * a_cubed * b_squared * x1 * x3_squared * y2_cubed +
    14 * a_cubed * b_squared * x1 * x3_squared * y2_squared * y3 -
    12 * a_cubed * b_squared * x1 * x3_squared * y2 * y3_squared -
    4 * a_cubed * b_squared * x1 * y1_cubed * y2_squared +
    8 * a_cubed * b_squared * x1 * y1_cubed * y2 * y3 -
    4 * a_cubed * b_squared * x1 * y1_cubed * y3_squared +
    4 * a_cubed * b_squared * x1 * y1_squared * y2_cubed -
    4 * a_cubed * b_squared * x1 * y1_squared * y2_squared * y3 -
    4 * a_cubed * b_squared * x1 * y1_squared * y2 * y3_squared +
    4 * a_cubed * b_squared * x1 * y1_squared * y3_cubed -
    4 * a_cubed * b_squared * x1 * y1 * y2_cubed * y3 +
    8 * a_cubed * b_squared * x1 * y1 * y2_squared * y3_squared -
    4 * a_cubed * b_squared * x1 * y1 * y2 * y3_cubed -
    2 * a_cubed * b_squared * x2_cubed * y1_cubed +
    2 * a_cubed * b_squared * x2_cubed * y1_squared * y3 +
    2 * a_cubed * b_squared * x2_cubed * y1 * y3_squared -
    2 * a_cubed * b_squared * x2_cubed * y3_cubed +
    2 * a_cubed * b_squared * x2_squared * x3 * y1_cubed +
    14 * a_cubed * b_squared * x2_squared * x3 * y1_squared * y2 -
    16 * a_cubed * b_squared * x2_squared * x3 * y1_squared * y3 -
    12 * a_cubed * b_squared * x2_squared * x3 * y1 * y2_squared +
    10 * a_cubed * b_squared * x2_squared * x3 * y1 * y3_squared +
    12 * a_cubed * b_squared * x2_squared * x3 * y2_squared * y3 -
    14 * a_cubed * b_squared * x2_squared * x3 * y2 * y3_squared +
    4 * a_cubed * b_squared * x2_squared * x3 * y3_cubed +
    2 * a_cubed * b_squared * x2 * x3_squared * y1_cubed -
    16 * a_cubed * b_squared * x2 * x3_squared * y1_squared * y2 +
    14 * a_cubed * b_squared * x2 * x3_squared * y1_squared * y3 +
    10 * a_cubed * b_squared * x2 * x3_squared * y1 * y2_squared -
    12 * a_cubed * b_squared * x2 * x3_squared * y1 * y3_squared +
    4 * a_cubed * b_squared * x2 * x3_squared * y2_cubed -
    14 * a_cubed * b_squared * x2 * x3_squared * y2_squared * y3 +
    12 * a_cubed * b_squared * x2 * x3_squared * y2 * y3_squared +
    4 * a_cubed * b_squared * x2 * y1_cubed * y2_squared -
    4 * a_cubed * b_squared * x2 * y1_cubed * y2 * y3 -
    4 * a_cubed * b_squared * x2 * y1_squared * y2_cubed -
    4 * a_cubed * b_squared * x2 * y1_squared * y2_squared * y3 +
    8 * a_cubed * b_squared * x2 * y1_squared * y2 * y3_squared +
    8 * a_cubed * b_squared * x2 * y1 * y2_cubed * y3 -
    4 * a_cubed * b_squared * x2 * y1 * y2_squared * y3_squared -
    4 * a_cubed * b_squared * x2 * y1 * y2 * y3_cubed -
    4 * a_cubed * b_squared * x2 * y2_cubed * y3_squared +
    4 * a_cubed * b_squared * x2 * y2_squared * y3_cubed -
    2 * a_cubed * b_squared * x3_cubed * y1_cubed +
    2 * a_cubed * b_squared * x3_cubed * y1_squared * y2 +
    2 * a_cubed * b_squared * x3_cubed * y1 * y2_squared -
    2 * a_cubed * b_squared * x3_cubed * y2_cubed -
    4 * a_cubed * b_squared * x3 * y1_cubed * y2 * y3 +
    4 * a_cubed * b_squared * x3 * y1_cubed * y3_squared +
    8 * a_cubed * b_squared * x3 * y1_squared * y2_squared * y3 -
    4 * a_cubed * b_squared * x3 * y1_squared * y2 * y3_squared -
    4 * a_cubed * b_squared * x3 * y1_squared * y3_cubed -
    4 * a_cubed * b_squared * x3 * y1 * y2_cubed * y3 -
    4 * a_cubed * b_squared * x3 * y1 * y2_squared * y3_squared +
    8 * a_cubed * b_squared * x3 * y1 * y2 * y3_cubed +
    4 * a_cubed * b_squared * x3 * y2_cubed * y3_squared -
    4 * a_cubed * b_squared * x3 * y2_squared * y3_cubed -
    8 * a_squared * b_cubed * x1_cubed * x2 * y1 * y2 +
    8 * a_squared * b_cubed * x1_cubed * x2 * y1 * y3 +
    6 * a_squared * b_cubed * x1_cubed * x2 * y2_squared -
    6 * a_squared * b_cubed * x1_cubed * x2 * y3_squared +
    8 * a_squared * b_cubed * x1_cubed * x3 * y1 * y2 -
    8 * a_squared * b_cubed * x1_cubed * x3 * y1 * y3 -
    6 * a_squared * b_cubed * x1_cubed * x3 * y2_squared +
    6 * a_squared * b_cubed * x1_cubed * x3 * y3_squared -
    6 * a_squared * b_cubed * x1_squared * x2_squared * y1_squared +
    16 * a_squared * b_cubed * x1_squared * x2_squared * y1 * y2 -
    8 * a_squared * b_cubed * x1_squared * x2_squared * y1 * y3 -
    6 * a_squared * b_cubed * x1_squared * x2_squared * y2_squared -
    8 * a_squared * b_cubed * x1_squared * x2_squared * y2 * y3 +
    12 * a_squared * b_cubed * x1_squared * x2_squared * y3_squared +
    12 * a_squared * b_cubed * x1_squared * x2 * x3 * y1_squared -
    8 * a_squared * b_cubed * x1_squared * x2 * x3 * y1 * y2 -
    8 * a_squared * b_cubed * x1_squared * x2 * x3 * y1 * y3 -
    6 * a_squared * b_cubed * x1_squared * x2 * x3 * y2_squared +
    16 * a_squared * b_cubed * x1_squared * x2 * x3 * y2 * y3 -
    6 * a_squared * b_cubed * x1_squared * x2 * x3 * y3_squared -
    6 * a_squared * b_cubed * x1_squared * x3_squared * y1_squared -
    8 * a_squared * b_cubed * x1_squared * x3_squared * y1 * y2 +
    16 * a_squared * b_cubed * x1_squared * x3_squared * y1 * y3 +
    12 * a_squared * b_cubed * x1_squared * x3_squared * y2_squared -
    8 * a_squared * b_cubed * x1_squared * x3_squared * y2 * y3 -
    6 * a_squared * b_cubed * x1_squared * x3_squared * y3_squared +
    6 * a_squared * b_cubed * x1_squared * y1_squared * y2_squared -
    12 * a_squared * b_cubed * x1_squared * y1_squared * y2 * y3 +
    6 * a_squared * b_cubed * x1_squared * y1_squared * y3_squared -
    2 * a_squared * b_cubed * x1_squared * y1 * y2_cubed +
    2 * a_squared * b_cubed * x1_squared * y1 * y2_squared * y3 +
    2 * a_squared * b_cubed * x1_squared * y1 * y2 * y3_squared -
    2 * a_squared * b_cubed * x1_squared * y1 * y3_cubed -
    2 * a_squared * b_cubed * x1_squared * y2_cubed * y3 +
    4 * a_squared * b_cubed * x1_squared * y2_squared * y3_squared -
    2 * a_squared * b_cubed * x1_squared * y2 * y3_cubed +
    6 * a_squared * b_cubed * x1 * x2_cubed * y1_squared -
    8 * a_squared * b_cubed * x1 * x2_cubed * y1 * y2 +
    8 * a_squared * b_cubed * x1 * x2_cubed * y2 * y3 -
    6 * a_squared * b_cubed * x1 * x2_cubed * y3_squared -
    6 * a_squared * b_cubed * x1 * x2_squared * x3 * y1_squared -
    8 * a_squared * b_cubed * x1 * x2_squared * x3 * y1 * y2 +
    16 * a_squared * b_cubed * x1 * x2_squared * x3 * y1 * y3 +
    12 * a_squared * b_cubed * x1 * x2_squared * x3 * y2_squared -
    8 * a_squared * b_cubed * x1 * x2_squared * x3 * y2 * y3 -
    6 * a_squared * b_cubed * x1 * x2_squared * x3 * y3_squared -
    6 * a_squared * b_cubed * x1 * x2 * x3_squared * y1_squared +
    16 * a_squared * b_cubed * x1 * x2 * x3_squared * y1 * y2 -
    8 * a_squared * b_cubed * x1 * x2 * x3_squared * y1 * y3 -
    6 * a_squared * b_cubed * x1 * x2 * x3_squared * y2_squared -
    8 * a_squared * b_cubed * x1 * x2 * x3_squared * y2 * y3 +
    12 * a_squared * b_cubed * x1 * x2 * x3_squared * y3_squared -
    8 * a_squared * b_cubed * x1 * x2 * y1_squared * y2_squared +
    12 * a_squared * b_cubed * x1 * x2 * y1_squared * y2 * y3 -
    4 * a_squared * b_cubed * x1 * x2 * y1_squared * y3_squared +
    12 * a_squared * b_cubed * x1 * x2 * y1 * y2_squared * y3 -
    16 * a_squared * b_cubed * x1 * x2 * y1 * y2 * y3_squared +
    4 * a_squared * b_cubed * x1 * x2 * y1 * y3_cubed -
    4 * a_squared * b_cubed * x1 * x2 * y2_squared * y3_squared +
    4 * a_squared * b_cubed * x1 * x2 * y2 * y3_cubed +
    6 * a_squared * b_cubed * x1 * x3_cubed * y1_squared -
    8 * a_squared * b_cubed * x1 * x3_cubed * y1 * y3 -
    6 * a_squared * b_cubed * x1 * x3_cubed * y2_squared +
    8 * a_squared * b_cubed * x1 * x3_cubed * y2 * y3 -
    4 * a_squared * b_cubed * x1 * x3 * y1_squared * y2_squared +
    12 * a_squared * b_cubed * x1 * x3 * y1_squared * y2 * y3 -
    8 * a_squared * b_cubed * x1 * x3 * y1_squared * y3_squared +
    4 * a_squared * b_cubed * x1 * x3 * y1 * y2_cubed -
    16 * a_squared * b_cubed * x1 * x3 * y1 * y2_squared * y3 +
    12 * a_squared * b_cubed * x1 * x3 * y1 * y2 * y3_squared +
    4 * a_squared * b_cubed * x1 * x3 * y2_cubed * y3 -
    4 * a_squared * b_cubed * x1 * x3 * y2_squared * y3_squared -
    6 * a_squared * b_cubed * x2_cubed * x3 * y1_squared +
    8 * a_squared * b_cubed * x2_cubed * x3 * y1 * y2 -
    8 * a_squared * b_cubed * x2_cubed * x3 * y2 * y3 +
    6 * a_squared * b_cubed * x2_cubed * x3 * y3_squared +
    12 * a_squared * b_cubed * x2_squared * x3_squared * y1_squared -
    8 * a_squared * b_cubed * x2_squared * x3_squared * y1 * y2 -
    8 * a_squared * b_cubed * x2_squared * x3_squared * y1 * y3 -
    6 * a_squared * b_cubed * x2_squared * x3_squared * y2_squared +
    16 * a_squared * b_cubed * x2_squared * x3_squared * y2 * y3 -
    6 * a_squared * b_cubed * x2_squared * x3_squared * y3_squared -
    2 * a_squared * b_cubed * x2_squared * y1_cubed * y2 -
    2 * a_squared * b_cubed * x2_squared * y1_cubed * y3 +
    6 * a_squared * b_cubed * x2_squared * y1_squared * y2_squared +
    2 * a_squared * b_cubed * x2_squared * y1_squared * y2 * y3 +
    4 * a_squared * b_cubed * x2_squared * y1_squared * y3_squared -
    12 * a_squared * b_cubed * x2_squared * y1 * y2_squared * y3 +
    2 * a_squared * b_cubed * x2_squared * y1 * y2 * y3_squared -
    2 * a_squared * b_cubed * x2_squared * y1 * y3_cubed +
    6 * a_squared * b_cubed * x2_squared * y2_squared * y3_squared -
    2 * a_squared * b_cubed * x2_squared * y2 * y3_cubed -
    6 * a_squared * b_cubed * x2 * x3_cubed * y1_squared +
    8 * a_squared * b_cubed * x2 * x3_cubed * y1 * y3 +
    6 * a_squared * b_cubed * x2 * x3_cubed * y2_squared -
    8 * a_squared * b_cubed * x2 * x3_cubed * y2 * y3 +
    4 * a_squared * b_cubed * x2 * x3 * y1_cubed * y2 +
    4 * a_squared * b_cubed * x2 * x3 * y1_cubed * y3 -
    4 * a_squared * b_cubed * x2 * x3 * y1_squared * y2_squared -
    16 * a_squared * b_cubed * x2 * x3 * y1_squared * y2 * y3 -
    4 * a_squared * b_cubed * x2 * x3 * y1_squared * y3_squared +
    12 * a_squared * b_cubed * x2 * x3 * y1 * y2_squared * y3 +
    12 * a_squared * b_cubed * x2 * x3 * y1 * y2 * y3_squared -
    8 * a_squared * b_cubed * x2 * x3 * y2_squared * y3_squared -
    2 * a_squared * b_cubed * x3_squared * y1_cubed * y2 -
    2 * a_squared * b_cubed * x3_squared * y1_cubed * y3 +
    4 * a_squared * b_cubed * x3_squared * y1_squared * y2_squared +
    2 * a_squared * b_cubed * x3_squared * y1_squared * y2 * y3 +
    6 * a_squared * b_cubed * x3_squared * y1_squared * y3_squared -
    2 * a_squared * b_cubed * x3_squared * y1 * y2_cubed +
    2 * a_squared * b_cubed * x3_squared * y1 * y2_squared * y3 -
    12 * a_squared * b_cubed * x3_squared * y1 * y2 * y3_squared -
    2 * a_squared * b_cubed * x3_squared * y2_cubed * y3 +
    6 * a_squared * b_cubed * x3_squared * y2_squared * y3_squared +
    2 * a * b_fourth * x1_fourth * x2 * y2 -
    2 * a * b_fourth * x1_fourth * x2 * y3 -
    2 * a * b_fourth * x1_fourth * x3 * y2 +
    2 * a * b_fourth * x1_fourth * x3 * y3 +
    4 * a * b_fourth * x1_cubed * x2_squared * y1 -
    6 * a * b_fourth * x1_cubed * x2_squared * y2 +
    2 * a * b_fourth * x1_cubed * x2_squared * y3 -
    8 * a * b_fourth * x1_cubed * x2 * x3 * y1 +
    4 * a * b_fourth * x1_cubed * x2 * x3 * y2 +
    4 * a * b_fourth * x1_cubed * x2 * x3 * y3 +
    4 * a * b_fourth * x1_cubed * x3_squared * y1 +
    2 * a * b_fourth * x1_cubed * x3_squared * y2 -
    6 * a * b_fourth * x1_cubed * x3_squared * y3 -
    4 * a * b_fourth * x1_cubed * y1 * y2_squared +
    8 * a * b_fourth * x1_cubed * y1 * y2 * y3 -
    4 * a * b_fourth * x1_cubed * y1 * y3_squared -
    6 * a * b_fourth * x1_squared * x2_cubed * y1 +
    4 * a * b_fourth * x1_squared * x2_cubed * y2 +
    2 * a * b_fourth * x1_squared * x2_cubed * y3 +
    6 * a * b_fourth * x1_squared * x2_squared * x3 * y1 +
    6 * a * b_fourth * x1_squared * x2_squared * x3 * y2 -
    12 * a * b_fourth * x1_squared * x2_squared * x3 * y3 +
    6 * a * b_fourth * x1_squared * x2 * x3_squared * y1 -
    12 * a * b_fourth * x1_squared * x2 * x3_squared * y2 +
    6 * a * b_fourth * x1_squared * x2 * x3_squared * y3 +
    4 * a * b_fourth * x1_squared * x2 * y1 * y2_squared -
    12 * a * b_fourth * x1_squared * x2 * y1 * y2 * y3 +
    8 * a * b_fourth * x1_squared * x2 * y1 * y3_squared +
    4 * a * b_fourth * x1_squared * x2 * y2_squared * y3 -
    4 * a * b_fourth * x1_squared * x2 * y2 * y3_squared -
    6 * a * b_fourth * x1_squared * x3_cubed * y1 +
    2 * a * b_fourth * x1_squared * x3_cubed * y2 +
    4 * a * b_fourth * x1_squared * x3_cubed * y3 +
    8 * a * b_fourth * x1_squared * x3 * y1 * y2_squared -
    12 * a * b_fourth * x1_squared * x3 * y1 * y2 * y3 +
    4 * a * b_fourth * x1_squared * x3 * y1 * y3_squared -
    4 * a * b_fourth * x1_squared * x3 * y2_squared * y3 +
    4 * a * b_fourth * x1_squared * x3 * y2 * y3_squared +
    2 * a * b_fourth * x1 * x2_fourth * y1 -
    2 * a * b_fourth * x1 * x2_fourth * y3 +
    4 * a * b_fourth * x1 * x2_cubed * x3 * y1 -
    8 * a * b_fourth * x1 * x2_cubed * x3 * y2 +
    4 * a * b_fourth * x1 * x2_cubed * x3 * y3 -
    12 * a * b_fourth * x1 * x2_squared * x3_squared * y1 +
    6 * a * b_fourth * x1 * x2_squared * x3_squared * y2 +
    6 * a * b_fourth * x1 * x2_squared * x3_squared * y3 +
    4 * a * b_fourth * x1 * x2_squared * y1_squared * y2 +
    4 * a * b_fourth * x1 * x2_squared * y1_squared * y3 -
    12 * a * b_fourth * x1 * x2_squared * y1 * y2 * y3 -
    4 * a * b_fourth * x1 * x2_squared * y1 * y3_squared +
    8 * a * b_fourth * x1 * x2_squared * y2 * y3_squared +
    4 * a * b_fourth * x1 * x2 * x3_cubed * y1 +
    4 * a * b_fourth * x1 * x2 * x3_cubed * y2 -
    8 * a * b_fourth * x1 * x2 * x3_cubed * y3 -
    8 * a * b_fourth * x1 * x2 * x3 * y1_squared * y2 -
    8 * a * b_fourth * x1 * x2 * x3 * y1_squared * y3 -
    8 * a * b_fourth * x1 * x2 * x3 * y1 * y2_squared +
    48 * a * b_fourth * x1 * x2 * x3 * y1 * y2 * y3 -
    8 * a * b_fourth * x1 * x2 * x3 * y1 * y3_squared -
    8 * a * b_fourth * x1 * x2 * x3 * y2_squared * y3 -
    8 * a * b_fourth * x1 * x2 * x3 * y2 * y3_squared +
    2 * a * b_fourth * x1 * x3_fourth * y1 -
    2 * a * b_fourth * x1 * x3_fourth * y2 +
    4 * a * b_fourth * x1 * x3_squared * y1_squared * y2 +
    4 * a * b_fourth * x1 * x3_squared * y1_squared * y3 -
    4 * a * b_fourth * x1 * x3_squared * y1 * y2_squared -
    12 * a * b_fourth * x1 * x3_squared * y1 * y2 * y3 +
    8 * a * b_fourth * x1 * x3_squared * y2_squared * y3 -
    2 * a * b_fourth * x2_fourth * x3 * y1 +
    2 * a * b_fourth * x2_fourth * x3 * y3 +
    2 * a * b_fourth * x2_cubed * x3_squared * y1 +
    4 * a * b_fourth * x2_cubed * x3_squared * y2 -
    6 * a * b_fourth * x2_cubed * x3_squared * y3 -
    4 * a * b_fourth * x2_cubed * y1_squared * y2 +
    8 * a * b_fourth * x2_cubed * y1 * y2 * y3 -
    4 * a * b_fourth * x2_cubed * y2 * y3_squared +
    2 * a * b_fourth * x2_squared * x3_cubed * y1 -
    6 * a * b_fourth * x2_squared * x3_cubed * y2 +
    4 * a * b_fourth * x2_squared * x3_cubed * y3 +
    8 * a * b_fourth * x2_squared * x3 * y1_squared * y2 -
    4 * a * b_fourth * x2_squared * x3 * y1_squared * y3 -
    12 * a * b_fourth * x2_squared * x3 * y1 * y2 * y3 +
    4 * a * b_fourth * x2_squared * x3 * y1 * y3_squared +
    4 * a * b_fourth * x2_squared * x3 * y2 * y3_squared -
    2 * a * b_fourth * x2 * x3_fourth * y1 +
    2 * a * b_fourth * x2 * x3_fourth * y2 -
    4 * a * b_fourth * x2 * x3_squared * y1_squared * y2 +
    8 * a * b_fourth * x2 * x3_squared * y1_squared * y3 +
    4 * a * b_fourth * x2 * x3_squared * y1 * y2_squared -
    12 * a * b_fourth * x2 * x3_squared * y1 * y2 * y3 +
    4 * a * b_fourth * x2 * x3_squared * y2_squared * y3 -
    4 * a * b_fourth * x3_cubed * y1_squared * y3 +
    8 * a * b_fourth * x3_cubed * y1 * y2 * y3 -
    4 * a * b_fourth * x3_cubed * y2_squared * y3 -
    b_fifth * x1_fourth * x2_squared +
    2 * b_fifth * x1_fourth * x2 * x3 -
    b_fifth * x1_fourth * x3_squared + b_fifth * x1_fourth * y2_squared -
    2 * b_fifth * x1_fourth * y2 * y3 +
    b_fifth * x1_fourth * y3_squared +
    2 * b_fifth * x1_cubed * x2_cubed -
    2 * b_fifth * x1_cubed * x2_squared * x3 -
    2 * b_fifth * x1_cubed * x2 * x3_squared +
    4 * b_fifth * x1_cubed * x2 * y2 * y3 -
    4 * b_fifth * x1_cubed * x2 * y3_squared +
    2 * b_fifth * x1_cubed * x3_cubed -
    4 * b_fifth * x1_cubed * x3 * y2_squared +
    4 * b_fifth * x1_cubed * x3 * y2 * y3 -
    b_fifth * x1_squared * x2_fourth -
    2 * b_fifth * x1_squared * x2_cubed * x3 +
    6 * b_fifth * x1_squared * x2_squared * x3_squared -
    2 * b_fifth * x1_squared * x2_squared * y1 * y2 -
    2 * b_fifth * x1_squared * x2_squared * y1 * y3 -
    2 * b_fifth * x1_squared * x2_squared * y2 * y3 +
    6 * b_fifth * x1_squared * x2_squared * y3_squared -
    2 * b_fifth * x1_squared * x2 * x3_cubed +
    4 * b_fifth * x1_squared * x2 * x3 * y1 * y2 +
    4 * b_fifth * x1_squared * x2 * x3 * y1 * y3 -
    8 * b_fifth * x1_squared * x2 * x3 * y2 * y3 -
    b_fifth * x1_squared * x3_fourth -
    2 * b_fifth * x1_squared * x3_squared * y1 * y2 -
    2 * b_fifth * x1_squared * x3_squared * y1 * y3 +
    6 * b_fifth * x1_squared * x3_squared * y2_squared -
    2 * b_fifth * x1_squared * x3_squared * y2 * y3 +
    2 * b_fifth * x1 * x2_fourth * x3 -
    2 * b_fifth * x1 * x2_cubed * x3_squared +
    4 * b_fifth * x1 * x2_cubed * y1 * y3 -
    4 * b_fifth * x1 * x2_cubed * y3_squared -
    2 * b_fifth * x1 * x2_squared * x3_cubed +
    4 * b_fifth * x1 * x2_squared * x3 * y1 * y2 -
    8 * b_fifth * x1 * x2_squared * x3 * y1 * y3 +
    4 * b_fifth * x1 * x2_squared * x3 * y2 * y3 +
    2 * b_fifth * x1 * x2 * x3_fourth -
    8 * b_fifth * x1 * x2 * x3_squared * y1 * y2 +
    4 * b_fifth * x1 * x2 * x3_squared * y1 * y3 +
    4 * b_fifth * x1 * x2 * x3_squared * y2 * y3 +
    4 * b_fifth * x1 * x3_cubed * y1 * y2 -
    4 * b_fifth * x1 * x3_cubed * y2_squared -
    b_fifth * x2_fourth * x3_squared + b_fifth * x2_fourth * y1_squared -
    2 * b_fifth * x2_fourth * y1 * y3 +
    b_fifth * x2_fourth * y3_squared +
    2 * b_fifth * x2_cubed * x3_cubed -
    4 * b_fifth * x2_cubed * x3 * y1_squared +
    4 * b_fifth * x2_cubed * x3 * y1 * y3 -
    b_fifth * x2_squared * x3_fourth +
    6 * b_fifth * x2_squared * x3_squared * y1_squared -
    2 * b_fifth * x2_squared * x3_squared * y1 * y2 -
    2 * b_fifth * x2_squared * x3_squared * y1 * y3 -
    2 * b_fifth * x2_squared * x3_squared * y2 * y3 -
    4 * b_fifth * x2 * x3_cubed * y1_squared +
    4 * b_fifth * x2 * x3_cubed * y1 * y2 +
    b_fifth * x3_fourth * y1_squared -
    2 * b_fifth * x3_fourth * y1 * y2 +
    b_fifth * x3_fourth * y2_squared) /
    (4 * (a_squared + b_squared) *
      (x1 * y2 - x2 * y1 - x1 * y3 + x3 * y1 + x2 * y3 - x3 * y2) *
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

void TriangleParabolaFocusPoint::Update()
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
	if (dx*dx+dy*dy > 0.01)
	{
		m_center_of_mass = center_of_mass;

		float a = m_segment->GetPoint(1)->position.y - m_segment->GetPoint(2)->position.y;
		float b = m_segment->GetPoint(2)->position.x - m_segment->GetPoint(1)->position.x;

		position.x = GetF1(a,b, points[0], points[1], points[2]);
		position.y = GetF2(a, b, points[0], points[1], points[2]);
	}
}
