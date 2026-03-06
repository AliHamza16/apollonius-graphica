#include "FPS-Info.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../Graphics/Window.h"

FPSInfo::FPSInfo()
{
	m_font = new sf::Font;
	m_text = new sf::Text;

	m_font->loadFromFile("Assets/Fonts/OpenSans-Regular.ttf");
	m_text->setFont(*m_font);

	m_text->setCharacterSize(20);
	m_text->setFillColor(sf::Color::White);
}

FPSInfo::~FPSInfo()
{
	delete m_font;
	delete m_text;
}

void FPSInfo::Draw(Window& window)
{
	m_text->setPosition(5, window.GetSize().y - 15);
	window.Draw(*m_text);
}

void FPSInfo::Update(float dt)
{
	m_frames += 1;
	m_seconds += dt;

	if (m_seconds > 1)
	{
		m_string = "FPS: " + std::to_string((int)(m_frames / m_seconds));
		m_text->setString(m_string);
		m_text->setOrigin(0, m_text->getGlobalBounds().height);
		m_seconds = 0;
		m_frames = 0;
	}
}
