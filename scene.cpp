#include "scene.h"

bool Scene::getDay()
{
	return this->day;
}

void Scene::handleEvents(sf::Event & event)
{
	//if (event.key.code == sf::Keyboard::Enter && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) this->day = !day;
}

void Scene::update()
{
	this->moon.move(-.005f, 0.f);
	if (this->moon.getPosition().x < -100) { this->day = !this->day; this->moon.setPosition(sf::Vector2f(800.f, 100.f)); }
	for (size_t i = 0; i < 3; i++) {
		this->clouds[i].move((float)(this->derSpeedSir[i]*(-.01f)), 0.f);
		if (this->clouds[i].getPosition().x < -100) { this->clouds[i].setPosition(sf::Vector2f((float)(rand() % 400 + 800), (float)(rand() % 200 + 30))); this->derSpeedSir[i] = rand() % 3+1; }
	}

	this->ground.setFillColor(this->day ? sf::Color(40, 40, 40, 255) : sf::Color(215, 215, 215, 255));
	for (size_t i = 0; i < 3; i++) this->clouds[i].setFillColor(this->day ? sf::Color(235, 235, 235, 255) : sf::Color(20, 20, 20, 255));
	this->moon.setFillColor(this->day ? sf::Color(255, 255, 255, 255) : sf::Color(30, 30, 30, 255));
}

void Scene::render(sf::RenderWindow & window)
{
	window.draw(this->ground);
	window.draw(this->moon);
	for (auto i : this->clouds) window.draw(i);
}

Scene::Scene() : day(true){
	this->ground.setSize(sf::Vector2f(800.f, 100.f));
	this->ground.setPosition(sf::Vector2f(0.f, 300.f));
	this->ground.setFillColor(this->day ? sf::Color(40, 40, 40, 255) : sf::Color(215, 215, 215, 255));

	this->moon.setSize(sf::Vector2f(100.f, 100.f));
	this->moon.setPosition(sf::Vector2f(800.f, 100.f));
	this->moon.setFillColor(this->day ? sf::Color(255, 255, 255, 255) : sf::Color(20, 20, 20, 255));

	for (size_t i = 0; i < 3;i++) {
		this->clouds[i].setSize(sf::Vector2f(50.f, 30.f));
		this->clouds[i].setPosition(sf::Vector2f((float)(rand()%1000), (float)(rand()%200+30)));
		this->clouds[i].setFillColor(this->day ? sf::Color(235, 235, 235, 255) : sf::Color(20, 20, 20, 255)); this->derSpeedSir[i] = rand() % 3+1;
	}
}

Scene::~Scene(){}
