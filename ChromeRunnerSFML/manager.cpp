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
		endText < 8 ? endText++: endText = 1;
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
		this->player.update(this->scene.getDay(), event);
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
	if(obstacles.getGameOver()&&!start)this->window.draw(DEATH[0]);
	if(obstacles.getGameOver()&&!start)this->window.draw(DEATH[endText]);
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
	this->window.clear(this->scene.getDay() ? sf::Color(255, 255, 255, 255) : sf::Color(0, 0, 0, 255));
}

void Manager::display()
{
	this->window.display();
}

Manager::Manager() : window(sf::VideoMode(800, 400), "Chrome Runner SFML by Lriend", sf::Style::Close | sf::Style::Titlebar)
{
	srand(NULL);
	start = true;
	gameOver = true;
	restart = true;
	if (!font.loadFromFile("Assets/8bitOperatorPlus8-Bold.ttf")) abort();
	for (size_t i = 0; i < 9; i++) DEATH[i].setFont(font);
	DEATH[0].setString("DEAD!");

	DEATH[1].setString("K.O.");
	DEATH[2].setString("And that's how dinosaurs become extinct!");
	DEATH[3].setString("You motherf****r! You murdered him!");
	DEATH[4].setString("Fatality!");
	DEATH[5].setString("Are you proud of yourself?");
	DEATH[6].setString("Not even funny anymore");
	DEATH[7].setString("Even my mother could beat you in this game.");
	DEATH[8].setString("Don't be fooled. Earth is flat.");

	DEATH[0].setPosition(150.f, -50.f);
	DEATH[0].setCharacterSize(192);
	DEATH[0].setRotation(20.f);
	for (size_t i = 1; i < 9; i++) {
		DEATH[i].setPosition(100.f, 150.f);
		DEATH[i].setCharacterSize(20);
		DEATH[i].setRotation(20.f);
	}
	for (size_t i = 0; i < 9; i++) DEATH[i].setFillColor(sf::Color(153, 0, 51, 255));

	endText = rand() % 8 + 1;
}

Manager::~Manager() {}
