#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>
#include <unordered_map>

class Window;
namespace sf {
	class Sprite;
	class Texture;
}


class Button
{
public:
	Button(sf::Vector2f size, sf::Vector2f position, std::string assetName);
	~Button();

	void Draw(Window& window) const;
	bool IsPressed(sf::Vector2f mousePosition);
	void SetPosition(sf::Vector2f position);

private:
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Sprite* m_sprite;
	sf::Texture* m_texture;
};

class ButtonLayout
{
public:
	static void Organize(std::unordered_map<int, Button*>& buttons);

private:
	ButtonLayout() {};
};