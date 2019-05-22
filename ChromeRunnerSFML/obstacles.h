#pragma once
#include "SFML/Graphics.hpp"

enum OBSTACLETEX{STH};

class Obstacles
{
	bool gameOver;
	sf::Time deltaTime;
	sf::Clock dClock;
	float freq;
	sf::Texture dayTex[1];
	sf::Texture nightTex[1];
	sf::Sprite obstacles[5];
public:
	void update(bool day);
	void render(sf::RenderWindow &window);
	bool getGameOver();
	void restart();
	Obstacles();
	~Obstacles();
};

