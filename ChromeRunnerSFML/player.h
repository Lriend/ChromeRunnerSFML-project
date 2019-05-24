#pragma once
#include <SFML/Graphics.hpp>

enum DINOTEX { START, RUN0, RUN2, RUN3, DUCK0, DUCK2, END};

class Player
{
	sf::Clock dClock;
	sf::Time deltaTime;

	const float groundHeight, gravity, jumpForce;
	sf::Vector2f velocity;
	bool isGrounded, duck;

	sf::Clock tClock;

	sf::Texture dinoTex[8];
	sf::Texture nightTex[8];
	DINOTEX currentTex;
	sf::Sprite dino;
public:
	void handleEvents(sf::Event &event);
	void update(bool day);
	void render(sf::RenderWindow &window);
	void restart();
	void die(bool day);
	sf::Sprite getDinoSprite();
	Player();
	~Player();
};

