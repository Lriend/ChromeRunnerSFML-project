#include "player.h"

void Player::handleEvents(sf::Event & event)
{
}

void Player::update(bool day)
{
	int texTime = tClock.getElapsedTime().asMilliseconds() % 500;

	if (dino.getPosition().y < groundHeight) currentTex = RUN3; else
	if (texTime >= 250) currentTex = RUN0; else
			currentTex = RUN2;

	deltaTime = dClock.restart();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded && !jumpPressed && deltaTime.asMicroseconds()) {
		jumpPressed = true;

		isGrounded = false;
		velocity.y = -jumpForce;
	}
	else jumpPressed = false;

	if (dino.getPosition().y < groundHeight || velocity.y < 0)
	{
		velocity.y += gravity;
	}
	else {
		dino.setPosition(dino.getPosition().x, groundHeight);
		velocity.y = 0;
		isGrounded = true;
	}
	dino.setTexture(day?dinoTex[currentTex]:nightTex[currentTex]);
	dino.move(0, velocity.y*deltaTime.asMicroseconds()/1000);

}

void Player::render(sf::RenderWindow &window)
{
	window.draw(this->dino);
}

Player::Player()
{
	if (!this->dinoTex[START].loadFromFile("Assets/dinoStart.png")) abort();
	if (!this->dinoTex[RUN0].loadFromFile("Assets/dinoRun0.png")) abort();
	if (!this->dinoTex[RUN1].loadFromFile("Assets/dinoRun1.png")) abort();
	if (!this->dinoTex[RUN2].loadFromFile("Assets/dinoRun2.png")) abort();
	if (!this->dinoTex[RUN3].loadFromFile("Assets/dinoRun3.png")) abort();
	if (!this->dinoTex[END].loadFromFile("Assets/dinoEnd.png")) abort();

	if (!this->nightTex[START].loadFromFile("Assets/dinoStart.png")) abort();
	if (!this->nightTex[RUN0].loadFromFile("Assets/nightRun0.png")) abort();
	if (!this->nightTex[RUN1].loadFromFile("Assets/nightRun1.png")) abort();
	if (!this->nightTex[RUN2].loadFromFile("Assets/nightRun2.png")) abort();
	if (!this->nightTex[RUN3].loadFromFile("Assets/nightRun3.png")) abort();
	if (!this->nightTex[END].loadFromFile("Assets/nightEnd.png")) abort();

	this->currentTex = START;
	this->dino.setTexture(dinoTex[currentTex]);
	this->dino.setPosition(sf::Vector2f(50.f, 266.f));
	this->dino.setColor(sf::Color(255, 255, 255, 255));

	this->gravity = .001f;
	this->groundHeight = 266.f;

	this->jumpPressed = false;
	this->isGrounded = true;
	this->jumpForce = 1.2f;

	this->velocity = sf::Vector2f(0, 0);
}


Player::~Player()
{
}
