#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

class Point;
class Segment;
class IPoint;

class Triangle
{
public:
	Triangle();
	Triangle(const Triangle& other);
	~Triangle();

	void AddSegment(Segment* p);
	Segment* GetSelectedSegment(sf::Vector2f position, float scale);
	std::vector<Segment*> GetSegments() const;
	std::vector<IPoint*> GetPoints() const;

private:
	Segment* m_s1 = nullptr;
	Segment* m_s2 = nullptr;
	Segment* m_s3 = nullptr;
};