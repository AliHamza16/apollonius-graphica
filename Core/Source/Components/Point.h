#pragma once
#include <SFML/System/Vector2.hpp>

class Window;
namespace sf {
	class CircleShape;
}
class Triangle;
class Segment;
class Point;

class IPoint {
	friend class Point;
	friend class TriangleParabolaFocusPoint;
public:
	virtual void Draw(Window& window) = 0;
	virtual void Update() = 0;

	float SquareDistance(sf::Vector2f position) const;
	float Distance(sf::Vector2f position) const;
	Point MidPoint(Point& other);

	sf::Vector2f position;
	bool selected = false;
	bool movable = true;
	
private:
	sf::CircleShape* m_shape;
};

class Point : public IPoint
{
public:
	Point(sf::Vector2f position);
	Point(const IPoint& other);
	~Point();

	void Draw(Window& window);
	void Update();
};



class TriangleParabolaFocusPoint : public IPoint {
public: 
	TriangleParabolaFocusPoint(Triangle* triangle, Segment* segment);
	~TriangleParabolaFocusPoint();

	void Draw(Window& window);
	void Update();

private:
	Triangle* m_triangle = nullptr;
	Segment* m_segment = nullptr;
	sf::Vector2f m_center_of_mass = sf::Vector2f(0,0);
};
