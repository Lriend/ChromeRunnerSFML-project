#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	float gravity, groundHeight, jumpTime, jumpForce;
	bool jump, isGrounded;
	sf::Vector2f velocity;

	sf::RectangleShape dino;
public:
	void handleEvents(sf::Event &event);
	void update(bool day);
	void render(sf::RenderWindow &window);
	Player();
	~Player();
};

