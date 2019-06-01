#include "player.h"

void Player::update(bool day, sf::Event &event, sf::Time deltaTime)
{
	int texTime = tClock.getElapsedTime().asMilliseconds() % 200;

	if (dino.getPosition().y < groundHeight) currentTex = RUN3; else
	if (texTime >= 100) currentTex = RUN0; else
			currentTex = RUN2;

	if (this->dino.getPosition().y > groundHeight) dino.setPosition(dino.getPosition().x, groundHeight);
	this->isGrounded = dino.getPosition().y == groundHeight ? true : false;

	
	//jmp
	if (isGrounded) {
		velocity.y = 0;
		this->duck = sf::Keyboard::isKeyPressed(sf::Keyboard::Down)?true: sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? true : false;
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !duck) { velocity.y = -jumpForce; }
	}
	else {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) /*&&velocity<0 gdybym chcial zrobic spadanie niezaleznie od wcisniecia spacji*/) velocity.y += gravity / 2;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) velocity.y += gravity * 10;
		else velocity.y += gravity;
	}

	if (duck) {
		currentTex= (DINOTEX)((int)currentTex + 3);
	}

	//movem
	velocity.x = 0;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && dino.getPosition().x > 50) velocity.x = -.5f*deltaTime.asMicroseconds() / 1000;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && dino.getPosition().x < 750) velocity.x = .5f*deltaTime.asMicroseconds() / 1000;
	duck?dino.setTextureRect(sf::IntRect(0, 0, 59, 30)):dino.setTextureRect(sf::IntRect(0, 0, 44, 47));
	if (duck) dino.setPosition(dino.getPosition().x, 283.f);
	dino.setTexture(day?dinoTex[currentTex]:nightTex[currentTex]);
	
	dino.move(velocity);

}

void Player::render(sf::RenderWindow &window)
{
	window.draw(this->dino);
}

void Player::restart()
{
	this->currentTex = START;
	this->dino.setTexture(dinoTex[currentTex]);
	this->dino.setPosition(sf::Vector2f(50.f, 266.f));
	this->dino.setColor(sf::Color(255, 255, 255, 255));

	this->velocity = sf::Vector2f(0.f, 0.f);
}

void Player::die(bool day)
{
	this->dino.setTextureRect(sf::IntRect(0, 0, 44, 47));
	this->dino.setTexture(day?dinoTex[END]:nightTex[END]);
}

sf::Sprite Player::getDinoSprite() {
	return dino;
}

Player::Player() :groundHeight(266.f), gravity(.0004f), isGrounded(true), jumpForce(.3f), duck(false)
{
	if (!this->dinoTex[START].loadFromFile("Assets/dinoStart.png")) abort();
	if (!this->dinoTex[RUN0].loadFromFile("Assets/dinoRun0.png")) abort();
	if (!this->dinoTex[RUN2].loadFromFile("Assets/dinoRun2.png")) abort();
	if (!this->dinoTex[RUN3].loadFromFile("Assets/dinoRun3.png")) abort();
	if (!this->dinoTex[DUCK0].loadFromFile("Assets/duck0.png",sf::IntRect(0,0,59,30))) abort();
	if (!this->dinoTex[DUCK2].loadFromFile("Assets/duck2.png",sf::IntRect(0,0,59,30))) abort();
	if (!this->dinoTex[END].loadFromFile("Assets/dinoEnd.png")) abort();

	if (!this->nightTex[START].loadFromFile("Assets/dinoStart.png")) abort();
	if (!this->nightTex[RUN0].loadFromFile("Assets/nightRun0.png")) abort();
	if (!this->nightTex[RUN2].loadFromFile("Assets/nightRun2.png")) abort();
	if (!this->nightTex[RUN3].loadFromFile("Assets/nightRun3.png")) abort();
	if (!this->nightTex[DUCK0].loadFromFile("Assets/nightduck0.png", sf::IntRect(0, 0, 59, 30))) abort();
	if (!this->nightTex[DUCK2].loadFromFile("Assets/nightduck2.png", sf::IntRect(0, 0, 59, 30))) abort();
	if (!this->nightTex[END].loadFromFile("Assets/nightEnd.png")) abort();

	this->currentTex = START;
	this->dino.setTexture(dinoTex[currentTex]);
	this->dino.setPosition(sf::Vector2f(50.f, 266.f));
	this->dino.setColor(sf::Color(255, 255, 255, 255));

	this->velocity = sf::Vector2f(0.f, 0.f);
}


Player::~Player()
{
}
