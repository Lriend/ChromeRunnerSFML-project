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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) gameOver = true;
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

Obstacles::Obstacles()
{
	this->gameOver = true;
	if (!this->dayTex[STH].loadFromFile("Assets/sthday.png")) abort();
	if (!this->nightTex[STH].loadFromFile("Assets/sthnight.png")) abort();
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
