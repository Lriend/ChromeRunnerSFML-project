#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
	bool day;
	sf::RectangleShape ground;
public:
	bool getDay();
	void handleEvents(sf::Event &event);
	void render(sf::RenderWindow &window);
	Scene();
	~Scene();
};

