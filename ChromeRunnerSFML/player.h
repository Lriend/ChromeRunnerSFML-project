#pragma once
#include <SFML/Graphics.hpp>

enum DINOTEX { START, RUN0, RUN1, RUN2, RUN3, END};

class Player
{
	sf::Clock dClock;
	sf::Time deltaTime;

	const float groundHeight, gravity, jumpForce;
	float velocity;
	bool isGrounded;

	sf::Clock tClock;

	sf::Texture dinoTex[6];
	sf::Texture nightTex[6];
	DINOTEX currentTex;
	sf::Sprite dino;
public:
	void handleEvents(sf::Event &event);
	void update(bool day);
	void render(sf::RenderWindow &window);
	Player();
	~Player();
};

