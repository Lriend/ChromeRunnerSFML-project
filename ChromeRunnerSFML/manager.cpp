#include "manager.h"

void Manager::handleEvents()
{
	if (event.key.code == sf::Keyboard::Q && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) this->close();
	if (!gameOver &&event.type == event.KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P)) { this->pause = !this->pause; if (!pause) hint<8?hint++:hint=1; }
	//scene.handleEvents(this->event);
	if (!pause) {
		if (this->obstacles.getGameOver() && event.type == event.KeyPressed &&restart) {
			this->start = false;
			this->restart = false;
			this->gameOver = false;
			this->scene.resetScore();
			obstacles.restart();
			player.restart();
			scene.restart();
			endText < 13 ? endText++ : endText = 1;
		}
	}
}

void Manager::update()
{
	delta = lCock.restart();
	if (!pause) {
		this->obstacles.updateGameOver(player.getDinoSprite());
		if ((this->obstacles.getGameOver() && !this->gameOver) || start) {
			this->scene.resetScore();
			this->gameOver = true;
		}
		if (!obstacles.getGameOver() && !this->start) {
			this->scene.update(delta);
			this->player.update(this->scene.getDay(), event, delta);
			this->obstacles.update(this->scene.getDay(), delta);
			this->scene.updateScore(pause);
			//this->obstacles.updateGameOver(player.getDinoSize(), player.getDinoPosition());
		}
		else if (!start)player.die(scene.getDay());
	}
	else this->scene.updateScore(pause);
}

void Manager::render()
{
	this->scene.render(this->window);
	this->obstacles.render(this->window);
	this->player.render(this->window);
	if (obstacles.getGameOver() && !start) {
		this->window.draw(DEATH[0]);
		this->window.draw(DEATH[endText]);
		if (event.type == event.KeyReleased) restart = true;
	}if (pause) {
		PAUSE[3].setString("I was launched exactly\n        " + std::to_string((int)hClock.getElapsedTime().asSeconds()) + "\n                seconds ago.");
		this->window.draw(PAUSE[0]);
		this->window.draw(PAUSE[hint]);
	}if (start) { window.draw(START); window.draw(HOWTOPLAY); }
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

int Manager::getHighScore()
{
	return scene.getHighScore();
}

Manager::Manager() : window(sf::VideoMode(800, 400), "Chrome Runner SFML by Lriend", sf::Style::Close | sf::Style::Titlebar)
{
	srand(NULL);
	start = gameOver = restart = true;
	pause = false;

	if (!font.loadFromFile("Assets/8bitOperatorPlus8-Bold.ttf")) abort();
	for (size_t i = 0; i < 14; i++) DEATH[i].setFont(font);
	for (size_t i = 0; i < 9; i++) PAUSE[i].setFont(font);
	START.setFont(font);
	HOWTOPLAY.setFont(font);
	DEATH[0].setString("DEAD!");
	PAUSE[0].setString("PAUSE");
	START.setString("ChromeRunnerSFML");
	HOWTOPLAY.setString("Movement - arrows, quit - 'Q', pause - 'Escape'/'P'\n\n\n\n\n\n\n\n\n\nPress any key to continue...");

	DEATH[1].setString("K.O.");
	DEATH[2].setString("And that's how dinosaurs become extinct!");
	DEATH[3].setString("You motherf****r! You murdered him!");
	DEATH[4].setString("Fatality!");
	DEATH[5].setString("Are you proud of yourself?");
	DEATH[6].setString("Not even funny anymore...");
	DEATH[7].setString("Even my mother could beat you in this game!");
	DEATH[8].setString("Don't be fooled. Earth is flat.");
	DEATH[9].setString("You had one job.");
	DEATH[10].setString("Caroline told me that if you quit now\n        you will get a cake.");
	DEATH[11].setString("Go home and be a family man!");
	DEATH[12].setString("It's super effective!");
	DEATH[13].setString("This way you will never knew what's above 99999.");

	PAUSE[1].setString("To cheat a little bit - press 'Q'!");
	PAUSE[2].setString("Press 'P' and see what will happen!");
	PAUSE[3].setString("Amount of seconds you're in\n" + (int)hClock.getElapsedTime().asSeconds());
	PAUSE[4].setString("Give up. Just close the game and let him die.");
	PAUSE[5].setString("There is no escape.");
	PAUSE[6].setString("You have to avoid obstacles.");
	PAUSE[7].setString("Oh, come on. Hi. Welcome. AGAIN...");
	PAUSE[8].setString("\"Hint: That's not a hint.\"\n        Is the above a hint?");

	DEATH[0].setPosition(150.f, -50.f);
	DEATH[0].setCharacterSize(192);
	DEATH[0].setRotation(20.f);
	PAUSE[0].setPosition(50.f, 200.f);
	PAUSE[0].setCharacterSize(192);
	PAUSE[0].setRotation(-20.f);

	START.setPosition(50.f, 50.f);
	HOWTOPLAY.setPosition(75.f, 125.f);
	START.setCharacterSize(60);
	HOWTOPLAY.setCharacterSize(20);

	for (size_t i = 1; i < 14; i++) {
		DEATH[i].setPosition(100.f, 150.f);
		DEATH[i].setCharacterSize(20);
		DEATH[i].setRotation(20.f);
	}
	for (size_t i = 0; i < 14; i++) {
		DEATH[i].setFillColor(sf::Color(153, 0, 51, 255));
		DEATH[i].setOutlineThickness(2.f);
		DEATH[i].setOutlineColor(sf::Color(255,255,255, 255));
	}
	for (size_t i = 1; i < 9; i++) {
		PAUSE[i].setPosition(250.f, 350.f);
		PAUSE[i].setCharacterSize(20);
		PAUSE[i].setRotation(-20.f);
	}
	for (size_t i = 0; i < 9; i++) {
		PAUSE[i].setFillColor(sf::Color(0, 102, 153, 255));
		PAUSE[i].setOutlineThickness(2.f);
		PAUSE[i].setOutlineColor(sf::Color(255, 255, 255, 255));
	}
	hint = 1;
	endText = rand() % 13 + 1;
	START.setFillColor(sf::Color(153,128,0,255));
	HOWTOPLAY.setFillColor(sf::Color(153,128,0,255));
	START.setOutlineThickness(2.f);
	HOWTOPLAY.setOutlineThickness(2.f);
	START.setOutlineColor(sf::Color::White);
	HOWTOPLAY.setOutlineColor(sf::Color::White);
}

Manager::~Manager() {}
