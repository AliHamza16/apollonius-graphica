#pragma once
#include <string>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <chrono>
#include "./CameraController.h"

namespace sf {
	class RenderWindow;
	class View;
	class Drawable;
	class Vertex;
}

class FPSInfo;

class Window
{
public:
	Window(std::string name, int width, int height);
	~Window();

	void CreateView(std::string name);
	void SetView(std::string name);

	sf::View* GetView(std::string name);
	sf::Vector2f GetSize() const;
	sf::Vector2f GetCenter() const;
	sf::Vector2f GetMousePosition() const;
	sf::Vector2f GetMousePosition(std::string name) const;
	float GetScale(sf::View* view) const;
	bool IsOpen() const;
	sf::Event* GetEvent() const;
	float GetDeltaTime();

	void Clear();
	bool PollEvent();
	void Draw(const sf::Drawable& object);
	void DrawLines(const sf::Vertex* vertices, size_t vertexCount);
	void Display();
	void Close();

	void Reset(std::string name);

	CameraController CamController;
	void HandleCamera();
	void MoveView(std::string name, sf::Vector2f offset);

	void ShowFPS();

private:
	sf::RenderWindow* m_window;
	std::unordered_map<std::string, sf::View*> m_views;
	sf::Event* m_event;
	std::chrono::high_resolution_clock m_clock;
	std::chrono::high_resolution_clock::time_point m_lastUpdate;
	FPSInfo* m_fpsInfo;
};