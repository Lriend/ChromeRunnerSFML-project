#pragma once
#include <SFML/Graphics.hpp>
#include "scene.h"
#include "player.h"

class Manager
{
	sf::Font font;
	sf::RenderWindow window;
	Scene scene;
	Player player;
	sf::Event event;
public:
	void handleEvents();
	void update();
	void render();
	bool isOpen();
	bool pollEvent();
	sf::Event::EventType getEventType();
	void close();
	void clear();
	void display();
	Manager();
	virtual ~Manager();
};

