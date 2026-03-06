#pragma once
#include <string>

class Window;
namespace sf {
	class Font;
	class Text;
}

class FPSInfo
{
public:
	FPSInfo();
	~FPSInfo();
	void Draw(Window& window);
	void Update(float dt);

private:
	float m_seconds = 0;
	int m_frames = 0;
	sf::Font* m_font;
	sf::Text* m_text;
	std::string m_string = "";
};