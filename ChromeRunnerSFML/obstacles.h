#pragma once
#include "SFML/Graphics.hpp"

enum OBSTACLETYPE{SMALL, WIDE, TALL, HIGH, FLYING};

class Obstacles
{
	bool gameOver;
	float freq;
	sf::Texture tex[2][5];
	sf::Sprite flyingObs[2];
	sf::Sprite standingObs[3];
	unsigned standingType[3];
public:
	void update(bool day, sf::Time deltatime);
	void render(sf::RenderWindow &window);
	bool getGameOver();
	void restart();
	void updateGameOver(sf::Sprite player);
	Obstacles();
	~Obstacles();
};

