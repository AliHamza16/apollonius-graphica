#include "./Core.h"
#include "./Source/Graphics/Window.h"
#include "./Source/Components/UI-Button.h"
#include "./Source/Constants/Constants.h"
#include "./Source/Components/TestRectangle.h"
#include "./Source/Components/Point.h"
#include "./Source/Components/Segment.h"
#include "./Source/Components/Triangle.h"
#include "./Source/Components/Line.h"
#include "./Source/Components/Parabola.h"
#include "./Source/Components/CoordinateSystem.h"

#include <unordered_map>

enum class Tool
{
	NONE, MOVEMENT, POINT, SEGMENT, LINE, PARRALEL_LINE, PERPENDICULAR_LINE, POLYGON, PARABOLA, TRIANGLE_PARABOLA
};


void ApolloniusGraphica::Run()
{
	Window window("Apollonius Graphica", 1200, 800);
	window.GetView("main")->setCenter(sf::Vector2f(0,0));

	std::unordered_map<int, Button*> buttons;
	std::vector<IPoint*> points;
	std::vector<Segment*> segments;
	std::vector<Triangle*> triangles;
	std::vector <ILine*> lines;
	std::vector <Parabola*> parabolas;
	Tool selectedTool = Tool::MOVEMENT;
	IPoint* movingPoint = nullptr;
	IPoint* firstPolygonPoint = nullptr;
	IPoint* lastPolygonPoint = nullptr;
	IPoint* lastSegmentPoint = nullptr;
	IPoint* lastLinePoint = nullptr;
	IPoint* parallelLinePoint = nullptr;
	IPoint* perpendicularLinePoint = nullptr;
	IPoint* parabolaPoint = nullptr;
	IPoint* triangleParabolaFocus = nullptr;
	ILine* triangleParabolaDirectrix = nullptr;
	Triangle* tempTriangle = nullptr;
	int polygonEdgeCount = 0;

	{
		buttons[0] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "cursor-48.png");
		buttons[1] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "home-48.png");
		buttons[2] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "grid-48.png");

		buttons[3] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "point-tool-48.png");
		buttons[4] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "segment-48.png");
		buttons[5] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "line-48.png");
		buttons[6] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "parralel-line-48.png");
		buttons[7] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "perpendicular-line-48.png");
		buttons[8] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "triangle-tool-48.png");
		buttons[9] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "parabola-48.png");
		buttons[10] = new Button(Constants::BUTTON_SIZE, { 0,0 }, "triangle-parabola-48.png");

		ButtonLayout::Organize(buttons);
	}

	CoordinateSystem cordSys;
	cordSys.subgridsEnabled = false;

	while (window.IsOpen())
	{

		while (window.PollEvent())
		{
			sf::Event* event = window.GetEvent();
			switch (event->type)
			{
			case sf::Event::Closed: {
				window.Close();
			} break;
			case sf::Event::Resized: {
				window.Reset("main");
				window.Reset("ui");
				window.GetView("main")->setCenter(sf::Vector2f(0, 0));
				cordSys.Reset();
			} break;
			case sf::Event::KeyPressed: {
				switch (event->key.scancode)
				{
				case sf::Keyboard::Scancode::Escape: {
					window.Close();
				} break;
				case sf::Keyboard::Scancode::NumpadPlus:
				{
					window.CamController.states[0] = true;
				} break;
				case sf::Keyboard::Scancode::NumpadMinus:
				{
					window.CamController.states[1] = true;
				} break;
				case sf::Keyboard::Scancode::Left:
				{
					window.CamController.states[2] = true;
				} break;
				case sf::Keyboard::Scancode::Right:
				{
					window.CamController.states[3] = true;
				} break;
				case sf::Keyboard::Scancode::Up:
				{
					window.CamController.states[4] = true;
				} break;
				case sf::Keyboard::Scancode::Down:
				{
					window.CamController.states[5] = true;
				} break;
				default:
					break;
				}
			} break;
			case sf::Event::KeyReleased: {
				switch (event->key.scancode)
				{
				case sf::Keyboard::Scancode::NumpadPlus:
				{
					window.CamController.Reset(0);
				} break;
				case sf::Keyboard::Scancode::NumpadMinus:
				{
					window.CamController.Reset(1);
				} break;
				case sf::Keyboard::Scancode::Left:
				{
					window.CamController.Reset(2);
				} break;
				case sf::Keyboard::Scancode::Right:
				{
					window.CamController.Reset(3);
				} break;
				case sf::Keyboard::Scancode::Up:
				{
					window.CamController.Reset(4);
				} break;
				case sf::Keyboard::Scancode::Down:
				{
					window.CamController.Reset(5);
				} break;
				default:
					break;
				}
			} break;
			case sf::Event::MouseButtonPressed: {

				sf::Vector2f mousePositionWindow = window.GetMousePosition();
				sf::Vector2f mousePositionMain = window.GetMousePosition("main");
				sf::Vector2f mousePositionUI = window.GetMousePosition("ui");
				float scaleMain = window.GetScale(window.GetView("main"));

				switch (event->mouseButton.button)
				{
				case sf::Mouse::Left: {

					Button* pressedButton = nullptr;
					int pressedButtonID =  -1;

					for (const auto& [id, button] : buttons)
					{
						if (button->IsPressed(mousePositionUI))
						{
							pressedButton = button;
							pressedButtonID = id;
						}
					}

					if (pressedButton)
					{

						for (const auto& point : points)
						{
							point->selected = false;
						}

						lastSegmentPoint = nullptr;
						lastPolygonPoint = nullptr;

						switch (pressedButtonID)
						{
						case 0:
						{
							selectedTool = Tool::MOVEMENT;
						} break;
						case 1:
						{
							window.Reset("main");
							window.GetView("main")->setCenter(sf::Vector2f(0,0));
							cordSys.Reset();
						} break;
						case 2: {
							cordSys.subgridsEnabled = cordSys.subgridsEnabled ? false : true;
						} break;
						case 3: {
							selectedTool = Tool::POINT;
						} break;
						case 4: {
							selectedTool = Tool::SEGMENT;
						} break;
						case 5: {
							selectedTool = Tool::LINE;
						} break;
						case 6: {
							selectedTool = Tool::PARRALEL_LINE;
						} break;
						case 7: {
							selectedTool = Tool::PERPENDICULAR_LINE;
						} break;
						case 8: {
							selectedTool = Tool::POLYGON;
						} break;
						case 9: {
							selectedTool = Tool::PARABOLA;
						} break;
						case 10: {
							selectedTool = Tool::TRIANGLE_PARABOLA;
						} break;
						default:
							break;
						}
					}
					else {
						switch (selectedTool)
						{
						case Tool::NONE:
							break;
						case Tool::MOVEMENT: {

							Segment* seg = nullptr;
							
							for (const auto& point : points)
							{
								if (!point->movable)
								{
									continue;
								}
								if (point->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									point->selected = true;
									movingPoint = point;
								}
								else {
									point->selected = false;
								}
							}

							for (const auto& triangle : triangles)
							{
								seg = triangle->GetSelectedSegment(mousePositionMain, scaleMain);
								if (seg)
								{
									break;
								}
							}

							if (movingPoint)
							{
								break;
							}

							window.CamController.states[6] = true;
							window.CamController.lastMousePosition = mousePositionMain;

						} break;
						case Tool::POINT:
						{
							IPoint* p = new Point(cordSys.GetSnapPosition(mousePositionMain));
							p->selected = true;
							points.push_back(p);
						} break;
						case Tool::SEGMENT: {
							IPoint* selectedPoint = nullptr;
							for (const auto& point : points)
							{
								if (point->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedPoint = point;
									point->selected = true;
								}
							}

							if (!selectedPoint)
							{
								if (lastSegmentPoint)
								{
									lastSegmentPoint->selected = false;
									lastSegmentPoint = nullptr;
								}
								break;
							}

							if (lastSegmentPoint == nullptr)
							{
								lastSegmentPoint = selectedPoint;
							}
							else if (selectedPoint != lastSegmentPoint)
							{
								Segment* seg = new Segment(lastSegmentPoint, selectedPoint);
								segments.push_back(seg);
								lastSegmentPoint->selected = false;
								lastSegmentPoint = selectedPoint;
							}

						} break;
						case Tool::LINE: {
							IPoint* selectedPoint = nullptr;
							for (const auto& point : points)
							{
								if (point->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedPoint = point;
									point->selected = true;
								}
							}

							if (!selectedPoint)
							{
								if (lastLinePoint)
								{
									lastLinePoint->selected = false;
									lastLinePoint = nullptr;
								}
								break;
							}

							if (lastLinePoint == nullptr)
							{
								lastLinePoint = selectedPoint;
							}
							else if (selectedPoint != lastLinePoint)
							{
								Line* line = new Line(lastLinePoint, selectedPoint);
								lines.push_back(line);
								lastLinePoint->selected = false;
								selectedPoint->selected = false;
								lastLinePoint = nullptr;
							}

						} break;
						case Tool::PARRALEL_LINE: {
							IPoint* selectedPoint = nullptr;
							for (const auto& point : points)
							{
								if (point->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedPoint = point;
									point->selected = true;
									break;
								}
							}

							ILine* selectedLine = nullptr;
							for (const auto& line : lines)
							{
								if (line->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedLine = line;
									break;
								}
							}

							Segment* selectedSegment = nullptr;
							for (const auto& segment : segments)
							{
								if (segment->GetTotalDistance(mousePositionMain) - segment->GetLength() <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedSegment = segment;
									break;
								}
							}

							if (parallelLinePoint == nullptr)
							{
								parallelLinePoint = selectedPoint;
							}
							else if (selectedLine != nullptr)
							{
								ParallelLine* line = new ParallelLine(parallelLinePoint, selectedLine);
								lines.push_back(line);
								parallelLinePoint->selected = false;
								parallelLinePoint = nullptr;
							}
							else if (selectedSegment != nullptr)
							{
								Line* line_ = new Line(selectedSegment->GetPoint(1), selectedSegment->GetPoint(2));
								line_->visible = false;
								ParallelLine* line = new ParallelLine(parallelLinePoint, line_);
								lines.push_back(line);
								lines.push_back(line_);
								parallelLinePoint->selected = false;
								parallelLinePoint = nullptr;
							}

						} break;
						case Tool::PERPENDICULAR_LINE: {
							IPoint* selectedPoint = nullptr;
							for (const auto& point : points)
							{
								if (point->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedPoint = point;
									point->selected = true;
									break;
								}
							}

							ILine* selectedLine = nullptr;
							for (const auto& line : lines)
							{
								if (line->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedLine = line;
									break;
								}
							}

							Segment* selectedSegment = nullptr;
							for (const auto& segment : segments)
							{
								if (segment->GetTotalDistance(mousePositionMain) - segment->GetLength() <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedSegment = segment;
									break;
								}
							}

							if (perpendicularLinePoint == nullptr)
							{
								perpendicularLinePoint = selectedPoint;
							}
							else if (selectedLine != nullptr)
							{
								PerpendicularLine* line = new PerpendicularLine(perpendicularLinePoint, selectedLine);
								lines.push_back(line);
								perpendicularLinePoint->selected = false;
								perpendicularLinePoint = nullptr;
							}
							else if (selectedSegment != nullptr)
							{
								Line* line_ = new Line(selectedSegment->GetPoint(1), selectedSegment->GetPoint(2));
								line_->visible = false;
								PerpendicularLine* line = new PerpendicularLine(perpendicularLinePoint, line_);
								lines.push_back(line);
								lines.push_back(line_);
								perpendicularLinePoint->selected = false;
								perpendicularLinePoint = nullptr;
							}

						} break;
						case Tool::POLYGON:
						{
							IPoint* selectedPoint = nullptr;
							for (const auto& point : points)
							{
								if (point->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedPoint = point;
									point->selected = true;
								}
							}

							if (!selectedPoint)
							{
								break;
							}

							if (firstPolygonPoint == nullptr)
							{
								firstPolygonPoint = selectedPoint;
								lastPolygonPoint = selectedPoint;
								tempTriangle = new Triangle();
							}
							else if (selectedPoint != lastPolygonPoint)
							{
								Segment* seg = new Segment(lastPolygonPoint, selectedPoint);
								segments.push_back(seg);
								tempTriangle->AddSegment(seg);
								polygonEdgeCount++;
								lastPolygonPoint = selectedPoint;

								if (selectedPoint == firstPolygonPoint && polygonEdgeCount >= 3)
								{
									firstPolygonPoint = nullptr;
									lastPolygonPoint = nullptr;

									if (polygonEdgeCount == 3)
									{
										Triangle* triangle = new Triangle(*tempTriangle);
										triangles.push_back(triangle);
									}

									tempTriangle = nullptr;
									polygonEdgeCount = 0;

									for (const auto& point : points)
									{
										point->selected = false;
									}
								}
							}
						} break;
						case Tool::PARABOLA: {
							IPoint* selectedPoint = nullptr;
							for (const auto& point : points)
							{
								if (point->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedPoint = point;
									point->selected = true;
									break;
								}
							}

							ILine* selectedLine = nullptr;
							for (const auto& line : lines)
							{
								if (line->Distance(mousePositionMain) <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedLine = line;
									break;
								}
							}

							Segment* selectedSegment = nullptr;
							for (const auto& segment : segments)
							{
								if (segment->GetTotalDistance(mousePositionMain) - segment->GetLength() <= Constants::POINT_RADIUS * scaleMain)
								{
									selectedSegment = segment;
									break;
								}
							}

							if (parabolaPoint == nullptr)
							{
								parabolaPoint = selectedPoint;
							}
							else if (selectedLine != nullptr)
							{
								Parabola* parabola = new Parabola(parabolaPoint, selectedLine);
								parabolas.push_back(parabola);
								parabolaPoint->selected = false;
								parabolaPoint = nullptr;
							}
							else if (selectedSegment != nullptr)
							{
								Line* line_ = new Line(selectedSegment->GetPoint(1), selectedSegment->GetPoint(2));
								line_->visible = false;
								Parabola* parabola = new Parabola(parabolaPoint, line_);
								lines.push_back(line_);
								parabolas.push_back(parabola);
								parabolaPoint->selected = false;
								parabolaPoint = nullptr;
							}

						} break;
						case Tool::TRIANGLE_PARABOLA: {
							Segment* selectedSegment = nullptr;
							Triangle* selectedTriangle = nullptr;

							for (const auto& triangle : triangles)
							{
								selectedSegment = triangle->GetSelectedSegment(mousePositionMain, scaleMain);
								if (selectedSegment)
								{
									selectedTriangle = triangle;
									std::cout << "segment selected!\n";
									break;
								}
							}

							if (selectedSegment != nullptr)
							{

								IPoint* p = new TriangleParabolaFocusPoint(selectedTriangle, selectedSegment);
								p->movable = false;

								ILine* l = new TriangleParabolaDirectrixLine(selectedTriangle, selectedSegment);

								points.push_back(p);
								lines.push_back(l);

								Parabola* pb = new Parabola(p, l);
								parabolas.push_back(pb);
							}

						} break;
						default:
							break;
						}
					}
				} break;

				case sf::Mouse::Right: {

				} break;
				default:
					break;
				}
			} break;
			case sf::Event::MouseButtonReleased: {

				sf::Vector2f mousePositionWindow = window.GetMousePosition();
				sf::Vector2f mousePositionMain = window.GetMousePosition("main");
				sf::Vector2f mousePositionUI = window.GetMousePosition("ui");

				switch (event->mouseButton.button)
				{
				case sf::Mouse::Left: {
					switch (selectedTool)
					{
					case Tool::NONE:
						break;
					case Tool::MOVEMENT:
						movingPoint = nullptr;
						window.CamController.Reset(6);
						break;
					case Tool::POINT:
						break;
					case Tool::POLYGON:
						break;
					default:
						break;
					}
				} break;
				case sf::Mouse::Right: {

				} break;
				default:
					break;
				}
			} break;
			case sf::Event::MouseMoved: {
				sf::Vector2f mousePositionWindow = window.GetMousePosition();
				sf::Vector2f mousePositionMain = window.GetMousePosition("main");
				sf::Vector2f mousePositionUI = window.GetMousePosition("ui");
				float scaleMain = window.GetScale(window.GetView("main"));

				cordSys.UpdateMouseCoordinates(mousePositionMain);

				switch (selectedTool)
				{
				case Tool::NONE:
					break;
				case Tool::MOVEMENT:
				{
					if (window.CamController.states[6])
					{
						window.MoveView("main", (window.CamController.lastMousePosition - mousePositionMain));
					}
					else if (movingPoint)
					{
						movingPoint->position = cordSys.GetSnapPosition(mousePositionMain);
					}
				} break;
				case Tool::POINT:
					break;
				case Tool::POLYGON:
					break;
				default:
					break;
				}
			} break;
			case sf::Event::MouseWheelScrolled: {
				int delta = event->mouseWheelScroll.delta;

				if (delta > 0)
				{
					window.GetView("main")->zoom(0.9);
				}
				if (delta < 0)
				{
					window.GetView("main")->zoom(1.1);
				}

			} break;
			default:
				break;
			}
		}

		float dt = window.GetDeltaTime();

		window.Clear();
		window.HandleCamera();

		window.SetView("main");
		cordSys.Draw(window);
		for (const auto& line : lines)
		{
			if (line->visible)
			{
				line->Draw(window);
			}
			else
			{
				line->Update();
			}
		}
		for (const auto& parabola : parabolas)
		{
			parabola->Draw(window);
		}
		for (const auto& segment : segments)
		{
			segment->Draw(window);
		}
		for (const auto& point : points)
		{
			point->Draw(window);
		}

		window.SetView("ui");
		for (const auto& [id, button] : buttons)
		{
			button->Draw(window);
		}
		window.ShowFPS();
		cordSys.ShowMouseCoordinates(window);

		window.Display();
	}
}
