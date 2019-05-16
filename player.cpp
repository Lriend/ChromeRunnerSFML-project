#include "player.h"

void Player::handleEvents(sf::Event & event)
{
}

void Player::update(bool day)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&isGrounded&& !jump && dino.getPosition().y >= 0) {
		jump = true;
		isGrounded = false;
		velocity.y = -jumpForce;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jump = false;
	}

	if (dino.getPosition().y< groundHeight || velocity.y < 0)
	{
		velocity.y += gravity;
	}
	else {
		dino.setPosition(dino.getPosition().x, groundHeight);
		velocity.y = 0;
		isGrounded = true;
	}
	dino.move(velocity.x, velocity.y);

	this->dino.setFillColor(day ? sf::Color(60, 60, 60, 255) : sf::Color(195, 195, 195, 255));
}

void Player::render(sf::RenderWindow &window)
{
	window.draw(this->dino);
}

Player::Player()
{

	this->dino.setSize(sf::Vector2f(50.f, 80.f));
	this->dino.setPosition(sf::Vector2f(50.f, 250.f));
	this->dino.setFillColor(sf::Color(60, 60, 60, 255));

	this->gravity = .001f;
	this->groundHeight = 250;
	this->jumpTime = 0;

	this->jump = false;
	this->isGrounded = true;
	this->jumpForce = .65f;

	this->velocity = sf::Vector2f(0, 0);
}


Player::~Player()
{
}
