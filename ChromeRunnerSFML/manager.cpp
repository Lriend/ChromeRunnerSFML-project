#include "manager.h"

void Manager::handleEvents()
{
	if (event.key.code == sf::Keyboard::Escape && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->close();
	//scene.handleEvents(this->event);
	player.handleEvents(this->event);
	if (event.type == event.KeyReleased) restart = true;
	if (this->obstacles.getGameOver() && event.type == event.KeyPressed && (event.key.code == sf::Keyboard::Up||event.key.code==sf::Keyboard::Space) &&restart) {
		this->start = false;
		this->restart = false;
		this->gameOver = false;
		obstacles.restart();
		player.restart();
		scene.restart();
	}
}

void Manager::update()
{
	this->obstacles.updateGameOver(player.getDinoSprite());
	if ((this->obstacles.getGameOver()&&!this->gameOver)||start) {
		this->scene.resetScore();
		this->gameOver = true;
	}
	if (!this->obstacles.getGameOver()&&!this->start) {
		this->scene.update();
		this->player.update(this->scene.getDay());
		this->obstacles.update(this->scene.getDay());
		this->scene.updateScore();
		//this->obstacles.updateGameOver(player.getDinoSize(), player.getDinoPosition());
	}
	else if(!start)player.die(scene.getDay());
}

void Manager::render()
{
	this->scene.render(this->window);
	this->obstacles.render(this->window);
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
	//this->window.clear(this->scene.getDay() ? sf::Color(204, 51, 102, 255) : sf::Color(0, 102, 0, 255));
	this->window.clear(this->obstacles.getGameOver()&&!start?sf::Color(153,0,51,255):this->scene.getDay() ? sf::Color(255, 255, 255, 255) : sf::Color(0, 0, 0, 255));
}

void Manager::display()
{
	this->window.display();
}

Manager::Manager() : window(sf::VideoMode(800, 400), "Lorem Ipsum Title v2", sf::Style::Close|sf::Style::Titlebar)
{
	srand(NULL);
	start = true;
	gameOver = true;
	restart = true;
}

Manager::~Manager() {}
