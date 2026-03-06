#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class Window;
class IPoint;
class Point;
class Triangle;
class Segment;

class ILine
{
public:
	virtual void Draw(Window& window) = 0;
	virtual void Update()=0;

	float Distance(sf::Vector2f position);
	float Distance(ILine& other);
	Point Intersection(ILine& other);

	float a = 0;
	float b = 0;
	float c = 0;

	bool visible = true;

	sf::Color color = sf::Color(43, 191, 240);
};

class Line : public ILine
{
public:
	Line(IPoint* p1, IPoint* p2);
	~Line();

	void Update();
	void Draw(Window& window);

private:
	IPoint* m_p1 = nullptr;
	IPoint* m_p2 = nullptr;
};

class ParallelLine : public ILine
{
public:
	ParallelLine(IPoint* p, ILine* l);
	~ParallelLine();

	void Update();
	void Draw(Window& window);

private:
	IPoint* m_p = nullptr;
	ILine* m_l = nullptr;
};

class PerpendicularLine : public ILine
{
public:
	PerpendicularLine(IPoint* p, ILine* l);
	~PerpendicularLine();

	void Update();
	void Draw(Window& window);

private:
	IPoint* m_p = nullptr;
	ILine* m_l = nullptr;
};

class JustLine :public ILine {
public:
	JustLine(float a, float b, float c);
	~JustLine();

	void Update();
	void Draw(Window& window);
};

class TriangleParabolaDirectrixLine : public ILine {
public:
	TriangleParabolaDirectrixLine(Triangle* triangle, Segment* segment);
	~TriangleParabolaDirectrixLine();

	void Update();
	void Draw(Window& window);

private:
	Triangle* m_triangle = nullptr;
	Segment* m_segment = nullptr;
	sf::Vector2f m_center_of_mass = sf::Vector2f(0, 0);
};