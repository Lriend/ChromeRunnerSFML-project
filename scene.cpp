#include "scene.h"

bool Scene::getDay()
{
	return this->day;
}

void Scene::handleEvents(sf::Event & event)
{
	if (event.key.code == sf::Keyboard::Enter && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) this->day = !day;
	this->ground.setFillColor(this->day ? sf::Color(40, 40, 40, 255) : sf::Color(215, 215, 215, 255));
}

void Scene::render(sf::RenderWindow & window)
{
	window.draw(ground);
}

Scene::Scene() : day(true){
	this->ground.setSize(sf::Vector2f(800.f, 100.f));
	this->ground.setPosition(sf::Vector2f(0.f, 300.f));
	this->ground.setFillColor(this->day ? sf::Color(40, 40, 40, 255) : sf::Color(215, 215, 215, 255));
}

Scene::~Scene(){}
