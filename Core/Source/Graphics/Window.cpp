#include "Window.h"
#include <SFML/Graphics.hpp>
#include "../Components/FPS-Info.h"

Window::Window(std::string name, int width, int height)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), name, sf::Style::Default);
	m_event = new sf::Event;
	CreateView("main");
	CreateView("ui");
	SetView("main");

	m_fpsInfo = new FPSInfo;
	m_window->setFramerateLimit(144);
}

Window::~Window()
{
	delete m_window;
	for (const auto& [name, view] : m_views)
		delete view;
	delete m_fpsInfo;
}

void Window::CreateView(std::string name)
{
	sf::View* view = new sf::View;
	view->setSize(GetSize());
	view->setCenter(GetCenter());
	m_views[name] = view;
}

void Window::SetView(std::string name)
{
	m_window->setView(*GetView(name));
}

sf::View* Window::GetView(std::string name)
{
	return m_views.at(name);
}

sf::Vector2f Window::GetSize() const
{
	return sf::Vector2f(m_window->getSize());
}

sf::Vector2f Window::GetCenter() const
{
	return 0.5f * GetSize();
}

sf::Vector2f Window::GetMousePosition() const
{
	return sf::Vector2f(sf::Mouse::getPosition(*m_window));
}

sf::Vector2f Window::GetMousePosition(std::string name) const
{
	return sf::Vector2f(sf::Mouse::getPosition(*m_window)) * GetScale(m_views.at(name)) +
		(m_views.at(name)->getCenter() - m_views.at(name)->getSize() * 0.5f);
}

float Window::GetScale(sf::View* view) const
{
	return view->getSize().x / GetSize().x;
}

bool Window::IsOpen() const
{
	return m_window->isOpen();
}

sf::Event* Window::GetEvent() const
{
	return m_event;
}

float Window::GetDeltaTime()
{
	auto dt = std::chrono::duration_cast<std::chrono::microseconds>(m_clock.now() - m_lastUpdate).count();
	m_lastUpdate = m_clock.now();
	float dt_seconds = dt * 1e-6;
	m_fpsInfo->Update(dt_seconds);
	return dt_seconds;
}

void Window::Clear()
{
	m_window->clear(sf::Color::Black);
}

bool Window::PollEvent()
{
	return m_window->pollEvent(*m_event);
}

void Window::Draw(const sf::Drawable& object)
{
	m_window->draw(object);
}

void Window::DrawLines(const sf::Vertex* vertices, size_t vertexCount)
{
	m_window->draw(vertices, vertexCount, sf::Lines);
}

void Window::Display()
{
	m_window->display();
}

void Window::Close()
{
	m_window->close();
}

void Window::Reset(std::string name)
{
	sf::View* view = GetView(name);
	view->setSize(GetSize());
	view->setCenter(GetCenter());
}

void Window::HandleCamera()
{
	sf::View* view = GetView("main");
	constexpr float ZOOMIN_FACTOR = 0.99;
	constexpr float ZOOMOUT_FACTOR = 1/ZOOMIN_FACTOR;
	constexpr float dx = 0.6;
	float scale = GetScale(GetView("main"));

	if (CamController.states[0])
	{
		view->zoom(ZOOMIN_FACTOR);
	}
	else if (CamController.states[1])
	{
		view->zoom(ZOOMOUT_FACTOR);
	}

	if (CamController.states[2])
	{
		view->move(-dx * scale, 0);
	}
	if (CamController.states[3])
	{
		view->move(dx * scale, 0);
	}
	if (CamController.states[4]) {
		view->move(0, -dx * scale);
	}
	if (CamController.states[5])
	{
		view->move(0, dx * scale);
	}
}

void Window::MoveView(std::string name, sf::Vector2f offset)
{
	GetView(name)->move(offset);
}

void Window::ShowFPS()
{
	m_fpsInfo->Draw(*this);
}
