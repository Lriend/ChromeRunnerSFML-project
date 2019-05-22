#include "obstacles.h"
//#include <iostream> //DEBUG


void Obstacles::update(bool day)
{
	deltaTime = dClock.restart();

	for (size_t i = 0; i < 5; i++) {
		this->obstacles[i].move(-.5f*deltaTime.asMicroseconds() / 1000, 0.f);
		day ? this->obstacles[i].setTexture(dayTex[STH]) : this->obstacles[i].setTexture(nightTex[STH]);
		if (this->obstacles[i].getPosition().x < -100) {
			this->obstacles[i].setPosition(sf::Vector2f(this->obstacles[i>0?i-1:4].getPosition().x+1000.f/freq, (float)(rand() % 250 + 30)));
			if (!i&&freq < 4.f) this->freq += .04f;
			//std::cout << freq<<std::endl;//DEBUG
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) gameOver = true;
}

void Obstacles::render(sf::RenderWindow &window)
{
	for (auto i : obstacles) window.draw(i);
}

bool Obstacles::getGameOver()
{
	return this->gameOver;
}

void Obstacles::restart()
{
	this->gameOver = false;
	this->freq = 1.f;
	for (size_t i = 0; i < 5; i++) {
		this->obstacles[i].setTexture(dayTex[STH]);
		this->obstacles[i].setPosition(sf::Vector2f((float)1000 * (i + 1)+500, (float)(rand() % 250 + 30)));
		this->obstacles[i].setColor(sf::Color::White);
	}
	deltaTime = dClock.restart();
}

Obstacles::Obstacles()
{
	this->gameOver = true;
	if (!this->dayTex[STH].loadFromFile("Assets/sthday.png")) abort();
	if (!this->nightTex[STH].loadFromFile("Assets/sthnight.png")) abort();
	this->freq = 1.f;
	for (size_t i = 0; i < 5; i++) {
		this->obstacles[i].setTexture(dayTex[STH]);
		this->obstacles[i].setPosition(sf::Vector2f((float)1000.f*(i+1)+500.f, (float)(rand() % 250 + 30)));
		this->obstacles[i].setColor(sf::Color::White);
	}
}


Obstacles::~Obstacles()
{
}
