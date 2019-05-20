#pragma once
#include "SFML/Graphics.hpp"

enum OBSTACLETEX{SMALL_ONE, SMALL_TWO, SMALL_THREE, BIRD0, BIRD1};

class Obstacles
{
	sf::Texture obstacleTex[2];
	sf::RectangleShape cactuses[3];
	sf::RectangleShape birds[3];
public:
	void update();
	void render();
	Obstacles();
	~Obstacles();
};

