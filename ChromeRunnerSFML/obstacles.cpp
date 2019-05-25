#include "obstacles.h"
//#include <iostream> //DEBUG


void Obstacles::update(bool day, sf::Time deltaTime)
{

	for (size_t i = 0; i < 3; i++) {
		this->standingObs[i].move(-.5f*deltaTime.asMicroseconds() / 1000, 0.f);
		day ? this->standingObs[i].setTexture(tex[1][standingType[i]]) : this->standingObs[i].setTexture(tex[0][standingType[i]]);
		if (this->standingObs[i].getPosition().x < -200) {
			standingType[i] = (unsigned)rand() % 4;
			//this->standingObs[i].setPosition(sf::Vector2f(this->standingObs[i>0?i-1:2].getPosition().x+1000.f/freq, (float)(rand() % 250 + 30)));
			switch (standingType[i])
			{
			case SMALL:
				standingObs[i].setTextureRect(sf::IntRect(0, 0, 75,117));
				standingObs[i].setScale(1.f, 1.f);
				this->standingObs[i].setPosition(sf::Vector2f(this->standingObs[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq, 250.f));
				break;
			case WIDE:
				standingObs[i].setTextureRect(sf::IntRect(0, 0, 150, 117));
				standingObs[i].setScale(1.f, 1.f);
				this->standingObs[i].setPosition(sf::Vector2f(this->standingObs[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq, 250.f));
				break;
			case HIGH:
				standingObs[i].setTextureRect(sf::IntRect(0, 0, 75, 700));
				standingObs[i].setScale(.5f, .5f);
				this->standingObs[i].setPosition(sf::Vector2f(this->standingObs[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq, -75.f));
				break;
			case TALL:
				standingObs[i].setTextureRect(sf::IntRect(0, 0, 75, 700));
				standingObs[i].setScale(.5f, .5f);
				this->standingObs[i].setPosition(sf::Vector2f(this->standingObs[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq, 150.f));
				break;
			}
			if (!i&&freq < 3.f) this->freq += .03f;
			//std::cout << freq<<std::endl;//DEBUG
		}
	}
	//if(freq>2.f)
	for (size_t i = 0; i < 2; i++) {
		this->flyingObs[i].move((flyingObs[i].getPosition().x>750?-.2f:-.75f)*deltaTime.asMicroseconds() / 1000, 0.f);
		day ? this->flyingObs[i].setTexture(tex[1][FLYING]) : this->flyingObs[i].setTexture(tex[0][FLYING]);
		if (this->flyingObs[i].getPosition().x < -100) {
			this->flyingObs[i].setPosition(sf::Vector2f(this->flyingObs[i>0?i-1:1].getPosition().x+5000.f/freq, (float)(rand() % 200 + 30)));
			this->flyingObs[i].setRotation(90.f);
			//std::cout << freq<<std::endl;//DEBUG
		}
	}
}

void Obstacles::render(sf::RenderWindow &window)
{
	for (auto i : standingObs) window.draw(i);
	for (auto i : flyingObs) window.draw(i);
}

bool Obstacles::getGameOver()
{
	return this->gameOver;
}

void Obstacles::restart()
{
	this->gameOver = false;
	this->freq = 1.f;
	for (size_t i = 0; i < 3; i++) {
		standingType[i] = 0;
		standingObs[i].setTextureRect(sf::IntRect(0, 0, 75, 117));
		standingObs[i].setScale(1.f, 1.f);
		this->standingObs[i].setTexture(tex[1][SMALL]);
		this->standingObs[i].setPosition(sf::Vector2f((float)1000 * (i + 1)+500, 250.f));
		//this->standingObs[i].setPosition(sf::Vector2f((float)1000 * (i + 1)+500, (float)(rand() % 250 + 30)));
		this->standingObs[i].setColor(sf::Color::White);
	}
	for (size_t i = 0; i < 2; i++) {
		this->flyingObs[i].setTexture(tex[1][FLYING]);
		this->flyingObs[i].setPosition(sf::Vector2f((float)5000 * (i + 1)+500, (float)(rand() % 200 + 30)));
		this->flyingObs[i].setColor(sf::Color::White);
		this->flyingObs[i].setRotation(90.f);
	}
}

void Obstacles::updateGameOver(sf::Sprite player)
{
	player.setScale(.5f, .9f);
	player.move(player.getTexture()->getSize().x *player.getScale().x / 4, player.getTexture()->getSize().y *(.5f - player.getScale().y / 2));
	for (size_t i = 0; i < 3; i++)	if (player.getGlobalBounds().intersects(standingObs[i].getGlobalBounds()))gameOver = true;
	for (size_t i = 0; i < 2; i++)	if (player.getGlobalBounds().intersects(flyingObs[i].getGlobalBounds()))gameOver = true;
}

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	/*sf::Vector2f collider(playerPosition.x + playerSize.x / 2, playerPosition.y + playerSize.y / 2);
	for (size_t i = 0; i < 3; i++) {
		if (collider.x > standingObs[i].getPosition().x && collider.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
			collider.y > standingObs[i].getPosition().y && collider.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y) {
			gameOver = true;
		}
	}
	for (size_t i = 0; i < 2; i++) {
		if (collider.x > flyingObs[i].getPosition().x && collider.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y &&
			collider.y > flyingObs[i].getPosition().y && collider.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x) {
			gameOver = true;
		}
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	for (size_t i = 0; i < 3; i++) {
		if (//UpperLeft
			(playerPosition.x > standingObs[i].getPosition().x && playerPosition.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
				playerPosition.y > standingObs[i].getPosition().y && playerPosition.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y)
			||//Lowerleft
			(playerPosition.x > standingObs[i].getPosition().x && playerPosition.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
				playerPosition.y + playerSize.y > standingObs[i].getPosition().y && playerPosition.y + playerSize.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y)
			||//UpperRight
			(playerPosition.x + playerSize.x > standingObs[i].getPosition().x && playerPosition.x + playerSize.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
				playerPosition.y > standingObs[i].getPosition().y && playerPosition.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y)
			||//LowerRight
			(playerPosition.x + playerSize.x > standingObs[i].getPosition().x && playerPosition.x + playerSize.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
				playerPosition.y + playerSize.y > standingObs[i].getPosition().y && playerPosition.y + playerSize.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y)
			)
			gameOver = true;
	}
	for (size_t i = 0; i < 2; i++) {
		if (//UpperLeft
			(playerPosition.x > flyingObs[i].getPosition().x && playerPosition.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x &&
				playerPosition.y > flyingObs[i].getPosition().y && playerPosition.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y)
			||//Lowerleft
			(playerPosition.x > flyingObs[i].getPosition().x && playerPosition.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x &&
				playerPosition.y + playerSize.y > flyingObs[i].getPosition().y && playerPosition.y + playerSize.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y)
			||//UpperRight
			(playerPosition.x + playerSize.x > flyingObs[i].getPosition().x && playerPosition.x + playerSize.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x &&
				playerPosition.y > flyingObs[i].getPosition().y && playerPosition.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y)
			||//LowerRight
			(playerPosition.x + playerSize.x > flyingObs[i].getPosition().x && playerPosition.x + playerSize.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x &&
				playerPosition.y + playerSize.y > flyingObs[i].getPosition().y && playerPosition.y + playerSize.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y)
			)
			gameOver = true;
	}*/

Obstacles::Obstacles()
{
	this->gameOver = true;

	if (!this->tex[1][SMALL].loadFromFile("Assets/sthdaysq.png")) abort();
	if (!this->tex[0][SMALL].loadFromFile("Assets/sthnightsq.png")) abort();
	if (!this->tex[1][FLYING].loadFromFile("Assets/sthday.png")) abort();
	if (!this->tex[0][FLYING].loadFromFile("Assets/sthnight.png")) abort();
	if (!this->tex[1][WIDE].loadFromFile("Assets/wat.png")) abort();
	if (!this->tex[0][WIDE].loadFromFile("Assets/watnight.png")) abort();
	if (!this->tex[1][HIGH].loadFromFile("Assets/hi.png")) abort();
	if (!this->tex[0][HIGH].loadFromFile("Assets/hinight.png")) abort();
	if (!this->tex[1][TALL].loadFromFile("Assets/tall.png")) abort();
	if (!this->tex[0][TALL].loadFromFile("Assets/tallnight.png")) abort();

	for (size_t i = 0; i < 3;i++) standingType[i] = 0;
	this->freq = 1.f;
	for (size_t i = 0; i < 3; i++) {
		this->standingObs[i].setTexture(tex[1][SMALL]);
		//this->standingObs[i].setPosition(sf::Vector2f((float)1000.f*(i+1)+500.f, (float)(rand() % 250 + 30)));
		this->standingObs[i].setPosition(sf::Vector2f((float)1000.f*(i+1)+500.f, 250.f));
		this->standingObs[i].setColor(sf::Color::White);
	}
	for (size_t i = 0; i < 2; i++) {
		this->flyingObs[i].setTexture(tex[1][FLYING]);
		this->flyingObs[i].setPosition(sf::Vector2f((float)5000.f*(i+1)+500.f, (float)(rand() % 200 + 30)));
		this->flyingObs[i].setColor(sf::Color::White);
		this->flyingObs[i].setRotation(90.f);
	}
}


Obstacles::~Obstacles()
{
}
