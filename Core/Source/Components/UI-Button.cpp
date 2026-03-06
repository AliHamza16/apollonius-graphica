#include "UI-Button.h"
#include "../Graphics/Window.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../Constants/Constants.h"

Button::Button(sf::Vector2f size, sf::Vector2f position, std::string assetName) : m_size(size), m_position(position)
{
	m_sprite = new sf::Sprite;
	m_texture = new sf::Texture;

	m_texture->loadFromFile("Assets/Images/" + assetName);
	m_sprite->setTexture(*m_texture);

	//m_sprite->setOrigin(size * 0.5f);
	m_sprite->setPosition(position);
}

Button::~Button()
{
	delete m_texture;
	delete m_sprite;
}

void Button::Draw(Window& window) const
{
	window.Draw(*m_sprite);
}

bool Button::IsPressed(sf::Vector2f mousePosition)
{
	return m_sprite->getGlobalBounds().contains(mousePosition);
}

void Button::SetPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite->setPosition(position);
}

void ButtonLayout::Organize(std::unordered_map<int, Button*>& buttons)
{

	int column = 0;
	int row = 0;

	for (const auto& [id, button] : buttons)
	{

		button->SetPosition(sf::Vector2f(column * (Constants::BUTTON_SIZE.x + Constants::BUTTON_MARGIN) + Constants::BUTTON_MARGIN, row * (Constants::BUTTON_SIZE.y + Constants::BUTTON_MARGIN) + Constants::BUTTON_MARGIN)
		);

		column++;

		if (column >= 5)
		{
			row++;
			column = 0;
		}
	}
}
