#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>

class Window;
namespace sf {
	class Font;
	class Text;
}

class CoordinateSystem
{
public:
	CoordinateSystem();

	void Draw(Window& window);
	void ShowMouseCoordinates(Window& window);
	void UpdateMouseCoordinates(sf::Vector2f position);
	void Reset();
	sf::Vector2f GetSnapPosition(sf::Vector2f position) const;
	bool subgridsEnabled = false;
	bool gridsEnabled = true;
	float gridSize = 100;
	float n = 1;

private:
	void DrawAxes(Window& window);
	void DrawGrids(Window& window);
	void DrawSubgrids(Window& window);

	sf::Font* m_font;
	sf::Text* m_text;
	std::string m_string = "";
	sf::Vector2f m_mousePosition;

};