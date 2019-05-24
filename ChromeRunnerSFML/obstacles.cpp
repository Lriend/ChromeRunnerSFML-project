#include "obstacles.h"
//#include <iostream> //DEBUG


void Obstacles::update(bool day)
{
	deltaTime = dClock.restart();

	for (size_t i = 0; i < 3; i++) {
		this->standingObs[i].move(-.5f*deltaTime.asMicroseconds() / 1000, 0.f);
		day ? this->standingObs[i].setTexture(dayTex[STH]) : this->standingObs[i].setTexture(nightTex[STH]);
		if (this->standingObs[i].getPosition().x < -100) {
			//this->standingObs[i].setPosition(sf::Vector2f(this->standingObs[i>0?i-1:2].getPosition().x+1000.f/freq, (float)(rand() % 250 + 30)));
			this->standingObs[i].setPosition(sf::Vector2f(this->standingObs[i>0?i-1:2].getPosition().x+1000.f/freq, 250.f));
			if (!i&&freq < 4.f) this->freq += .04f;
			//std::cout << freq<<std::endl;//DEBUG
		}
	}
	//if(freq>2.f)
	for (size_t i = 0; i < 2; i++) {
		this->flyingObs[i].move((flyingObs[i].getPosition().x>750?-.2f:-.75f)*deltaTime.asMicroseconds() / 1000, 0.f);
		day ? this->flyingObs[i].setTexture(dayTex[STH]) : this->flyingObs[i].setTexture(nightTex[STH]);
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
		this->standingObs[i].setTexture(dayTex[STH]);
		this->standingObs[i].setPosition(sf::Vector2f((float)1000 * (i + 1)+500, 250.f));
		//this->standingObs[i].setPosition(sf::Vector2f((float)1000 * (i + 1)+500, (float)(rand() % 250 + 30)));
		this->standingObs[i].setColor(sf::Color::White);
	}
	for (size_t i = 0; i < 2; i++) {
		this->flyingObs[i].setTexture(dayTex[STH]);
		this->flyingObs[i].setPosition(sf::Vector2f((float)5000 * (i + 1)+500, (float)(rand() % 200 + 30)));
		this->flyingObs[i].setColor(sf::Color::White);
		this->flyingObs[i].setRotation(90.f);
	}
	deltaTime = dClock.restart();
}

void Obstacles::updateGameOver(sf::Sprite player)
{
	player.setScale(.25f,.9f);
	player.move(player.getTexture()->getSize().x *(.5f-player.getScale().x/2), player.getTexture()->getSize().y *(.5f - player.getScale().y / 2));
	for (size_t i = 0; i < 3; i++)	if(player.getGlobalBounds().intersects(standingObs[i].getGlobalBounds()))gameOver=true;
	for (size_t i = 0; i < 2; i++)	if(player.getGlobalBounds().intersects(flyingObs[i].getGlobalBounds()))gameOver=true;
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
	}*/
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	//for (size_t i = 0; i < 3; i++) {
	//	if (//UpperLeft
	//		(playerPosition.x > standingObs[i].getPosition().x && playerPosition.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
	//			playerPosition.y > standingObs[i].getPosition().y && playerPosition.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y)
	//		||//Lowerleft
	//		(playerPosition.x > standingObs[i].getPosition().x && playerPosition.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
	//			playerPosition.y + playerSize.y > standingObs[i].getPosition().y && playerPosition.y + playerSize.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y)
	//		||//UpperRight
	//		(playerPosition.x + playerSize.x > standingObs[i].getPosition().x && playerPosition.x + playerSize.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
	//			playerPosition.y > standingObs[i].getPosition().y && playerPosition.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y)
	//		||//LowerRight
	//		(playerPosition.x + playerSize.x > standingObs[i].getPosition().x && playerPosition.x + playerSize.x < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().x &&
	//			playerPosition.y + playerSize.y > standingObs[i].getPosition().y && playerPosition.y + playerSize.y < standingObs[i].getPosition().x + standingObs[i].getTexture()->getSize().y)
	//		)
	//		gameOver = true;
	//}
	//for (size_t i = 0; i < 2; i++) {
	//	if (//UpperLeft
	//		(playerPosition.x > flyingObs[i].getPosition().x && playerPosition.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x &&
	//			playerPosition.y > flyingObs[i].getPosition().y && playerPosition.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y)
	//		||//Lowerleft
	//		(playerPosition.x > flyingObs[i].getPosition().x && playerPosition.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x &&
	//			playerPosition.y + playerSize.y > flyingObs[i].getPosition().y && playerPosition.y + playerSize.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y)
	//		||//UpperRight
	//		(playerPosition.x + playerSize.x > flyingObs[i].getPosition().x && playerPosition.x + playerSize.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x &&
	//			playerPosition.y > flyingObs[i].getPosition().y && playerPosition.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y)
	//		||//LowerRight
	//		(playerPosition.x + playerSize.x > flyingObs[i].getPosition().x && playerPosition.x + playerSize.x < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().x &&
	//			playerPosition.y + playerSize.y > flyingObs[i].getPosition().y && playerPosition.y + playerSize.y < flyingObs[i].getPosition().x + flyingObs[i].getTexture()->getSize().y)
	//		)
	//		gameOver = true;
	//}
}

Obstacles::Obstacles()
{
	this->gameOver = true;
	if (!this->dayTex[STH].loadFromFile("Assets/sthdaysq.png")) abort();
	if (!this->nightTex[STH].loadFromFile("Assets/sthnightsq.png")) abort();
	this->freq = 1.f;
	for (size_t i = 0; i < 3; i++) {
		this->standingObs[i].setTexture(dayTex[STH]);
		//this->standingObs[i].setPosition(sf::Vector2f((float)1000.f*(i+1)+500.f, (float)(rand() % 250 + 30)));
		this->standingObs[i].setPosition(sf::Vector2f((float)1000.f*(i+1)+500.f, 250.f));
		this->standingObs[i].setColor(sf::Color::White);
	}
	for (size_t i = 0; i < 2; i++) {
		this->flyingObs[i].setTexture(dayTex[STH]);
		this->flyingObs[i].setPosition(sf::Vector2f((float)5000.f*(i+1)+500.f, (float)(rand() % 200 + 30)));
		this->flyingObs[i].setColor(sf::Color::White);
		this->flyingObs[i].setRotation(90.f);
	}
}


Obstacles::~Obstacles()
{
}
