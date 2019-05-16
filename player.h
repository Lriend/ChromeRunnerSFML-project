#pragma once
#include <SFML/Graphics.hpp>

enum DINOTEX { START, RUN0, RUN1, RUN2, RUN3, END0, END1, DUCK0, DUCK1 };

class Player
{
	float gravity, groundHeight, jumpTime, jumpForce;
	bool jump, isGrounded;
	sf::Vector2f velocity;

	sf::Texture dinoTex[9];
	sf::RectangleShape dino;
public:
	void handleEvents(sf::Event &event);
	void update(bool day);
	void render(sf::RenderWindow &window);
	Player();
	~Player();
};

