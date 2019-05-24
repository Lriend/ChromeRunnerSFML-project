#pragma once
#include <SFML/Graphics.hpp>
#include "scene.h"
#include "player.h"
#include "obstacles.h"

class Manager
{
	sf::Font font; sf::Text DEATH[9]; unsigned endText;
	sf::RenderWindow window;
	Scene scene;
	Player player;
	Obstacles obstacles;
	sf::Event event;
	bool start;
	bool gameOver;
	bool restart;
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

