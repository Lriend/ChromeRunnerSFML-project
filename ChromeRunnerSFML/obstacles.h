#pragma once
#include "SFML/Graphics.hpp"

enum OBSTACLETYPE{SMALL, WIDE, TALL, HIGH, FLYING};

class Obstacles
{
	bool gameOver;
	sf::Time deltaTime;
	sf::Clock dClock;
	float freq;
	sf::Texture tex[2][5];
	sf::Sprite flyingObs[2];
	sf::Sprite standingObs[3];
	unsigned standingType[3];
public:
	void update(bool day);
	void render(sf::RenderWindow &window);
	bool getGameOver();
	void restart();
	void updateGameOver(sf::Sprite player);
	Obstacles();
	~Obstacles();
};

