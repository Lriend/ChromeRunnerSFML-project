#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
	bool day;
	sf::RectangleShape ground;
	sf::RectangleShape clouds[3];
	int derSpeedSir[3];
	sf::RectangleShape moon;
public:
	bool getDay();
	void handleEvents(sf::Event &event);
	void update();
	void render(sf::RenderWindow &window);
	Scene();
	~Scene();
};

