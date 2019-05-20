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

	if (this->dino.getPosition().y > groundHeight) dino.setPosition(dino.getPosition().x, groundHeight);
	this->isGrounded = dino.getPosition().y == groundHeight ? true : false;
	if (isGrounded) {
		velocity = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) velocity = -jumpForce;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isGrounded /*&&velocity<0 gdybym chcial zrobic spadanie niezaleznie od wcisniecia spacji*/) velocity += gravity / 2;
	else if (!isGrounded) velocity += gravity;

	dino.setTexture(day?dinoTex[currentTex]:nightTex[currentTex]);
	dino.move(0, velocity);

}

void Player::render(sf::RenderWindow &window)
{
	window.draw(this->dino);
}

Player::Player() :groundHeight(266.f), gravity(.001f), isGrounded(true), jumpForce(.5f)
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

}


Player::~Player()
{
}
