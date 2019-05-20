#include "manager.h"

void Manager::handleEvents()
{
	if (event.key.code == sf::Keyboard::Escape && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->close();
	//scene.handleEvents(this->event);
	player.handleEvents(this->event);
}

void Manager::update()
{
	this->scene.update();
	this->player.update(this->scene.getDay());
}

void Manager::render()
{
	this->scene.render(this->window);
	this->player.render(this->window);
}

bool Manager::isOpen()
{
	return this->window.isOpen();
}

bool Manager::pollEvent()
{
	return this->window.pollEvent(this->event);
}

sf::Event::EventType Manager::getEventType()
{
	return this->event.type;
}

void Manager::close()
{
	this->window.close();
}

void Manager::clear()
{
	this->window.clear(this->scene.getDay() ? sf::Color(255, 255, 255, 255) : sf::Color(0, 0, 0, 255));
}

void Manager::display()
{
	this->window.display();
}

Manager::Manager() : window(sf::VideoMode(800, 400), "Lorem Ipsum Title v2", sf::Style::Close|sf::Style::Titlebar)
{
	srand(NULL);
}

Manager::~Manager() {}
