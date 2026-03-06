#pragma once

#include <SFML/System/Vector2.hpp>

class IPoint;
class Window;

class Segment
{
public:
	Segment(IPoint* point1, IPoint* point2);
	Segment(const Segment& other);
	~Segment();

	void Draw(Window& window);

	IPoint* GetPoint(int index) const;
	float GetTotalDistance(sf::Vector2f position) const;
	float GetLength() const;

private:
	IPoint* m_point1 = nullptr;
	IPoint* m_point2 = nullptr;
};