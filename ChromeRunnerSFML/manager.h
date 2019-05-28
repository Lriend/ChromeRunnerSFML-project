#pragma once
#include <SFML/Graphics.hpp>
#include "scene.h"
#include "player.h"
#include "obstacles.h"

class Manager
{
	sf::Font font; sf::Text DEATH[14]; unsigned endText;
	sf::Text PAUSE[9]; unsigned hint; bool pause;
	sf::Text START; sf::Text HOWTOPLAY;
	sf::Clock lCock;
	sf::Time delta;
	sf::Clock hClock;

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
	int getHighScore();
	Manager();
	virtual ~Manager();
};

