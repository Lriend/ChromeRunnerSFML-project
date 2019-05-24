#include "scene.h"
//#include <iostream>

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
	deltaTime = dClock.restart();

	this->moon.move(-.05f*deltaTime.asMicroseconds()/1000, 0.f);
	if (this->moon.getPosition().x < -100) { this->day = !this->day; this->moon.setPosition(sf::Vector2f(800.f, 100.f)); }
	this->moon.setTexture(sceneTex[14-(int)(200+this->moon.getPosition().x)/100]);
	this->moon.setColor(this->day ? sf::Color(255, 255, 255, 0) : sf::Color(220, 220, 220, 255));

	for (size_t i = 0; i < 3; i++) {
		this->clouds[i].move((float)(this->derSpeedSir[i]*(-.01f)*deltaTime.asMicroseconds() / 1000), 0.f);
		if (this->clouds[i].getPosition().x < -100) {
			this->clouds[i].setPosition(sf::Vector2f((float)(rand() % 400 + 800), (float)(rand() % 200 + 30))); 
			this->derSpeedSir[i] = rand() % 5 + 1;
		}
		this->clouds[i].setColor(this->day ? sf::Color(235, 235, 235, 255) : sf::Color(50, 50, 50, 255));
	}

	for (size_t i = 0; i < 5; i++) {
		this->stars[i].move(-.05f*deltaTime.asMicroseconds() / 1000, 0.f);
		if((int)this->stars[i].getPosition().x % 25 ==0) this->stars[i].setTexture(sceneTex[rand() % 3 + 2]);
		if (this->stars[i].getPosition().x < -100) this->stars[i].setPosition(sf::Vector2f((float)(rand() % 1000), (float)(rand() % 200 + 30)));
		this->stars[i].setColor(this->day ? sf::Color(50, 50, 50, 0) : sf::Color(175, 175, 175, 200));
	}

	for (size_t i = 0; i < 2; i++) {
		this->ground[i].move(sf::Vector2f(-.5f*deltaTime.asMicroseconds() / 1000, 0.f));
		if (this->ground[i].getPosition().x < -1400) this->ground[i].move(sf::Vector2f(2400.f, 0.f));
		this->ground[i].setColor(this->day ? sf::Color(50, 50, 50, 255) : sf::Color(215, 215, 215, 255));
	}

	scoreText.setFillColor(day?sf::Color(64, 64, 64, 255):sf::Color(192,192,192,255));
}

void Scene::render(sf::RenderWindow & window)
{
	for (auto i : this->stars) window.draw(i);
	window.draw(this->moon);
	for (auto i : this->clouds) window.draw(i);
	for (auto i : ground) window.draw(i);
	window.draw(scoreText);
	if(hScore)window.draw(hScoreText);
}

void Scene::restart()
{
	this->day = true;

	for (size_t i = 0; i < 5; i++) {
		this->stars[i].setTexture(sceneTex[rand() % 3 + 2]);
		this->stars[i].setPosition(sf::Vector2f((float)(rand() % 1000), (float)(rand() % 200 + 30)));
		this->stars[i].setColor(this->day ? sf::Color(50, 50, 50, 0) : sf::Color(175, 175, 175, 200));
	}

	this->moon.setTexture(sceneTex[MOON4]);
	this->moon.setPosition(sf::Vector2f(800.f, 100.f));
	this->moon.setColor(this->day ? sf::Color(255, 255, 255, 0) : sf::Color(220, 220, 220, 255));

	deltaTime = dClock.restart();
}

void Scene::updateScore()
{
	if (score != scoreClock.getElapsedTime().asSeconds()) { 
		score = (unsigned)scoreClock.getElapsedTime().asSeconds(); 
		std::string scoreString = std::to_string(score);
		score >= 10000 ? scoreText.setString(scoreString) : score >= 1000 ? scoreText.setString("0" + scoreString) : score >= 100 ? scoreText.setString("00" + scoreString) : score >= 10 ? scoreText.setString("000" + scoreString) : scoreText.setString("0000" + scoreString);
		if (hScore < score) { hScore = score; hScoreText.setString("HI " + scoreText.getString()); }
	}
}

void Scene::resetScore()
{
	if(hScore<score)hScore = score;
	scoreClock.restart();
	//std::cout << "highscore: " << hScore << std::endl;
	//std::cout << "score: " << score << std::endl;
	score = 0;
}

Scene::Scene() : day(true), score(0), hScore(0){

	if (!this->sceneTex[CLOUD].loadFromFile("Assets/cloud.png")) abort();
	if (!this->sceneTex[GROUND].loadFromFile("Assets/ground.png")) abort();
	if (!this->sceneTex[STAR0].loadFromFile("Assets/star0.png")) abort();
	if (!this->sceneTex[STAR1].loadFromFile("Assets/star1.png")) abort();
	if (!this->sceneTex[STAR2].loadFromFile("Assets/star2.png")) abort();
	if (!this->sceneTex[MOON0].loadFromFile("Assets/moon0.png")) abort();
	if (!this->sceneTex[MOON1].loadFromFile("Assets/moon1.png")) abort();
	if (!this->sceneTex[MOON2].loadFromFile("Assets/moon2.png")) abort();
	if (!this->sceneTex[MOON3].loadFromFile("Assets/moon3.png")) abort();
	if (!this->sceneTex[MOON4].loadFromFile("Assets/moon4.png")) abort();
	if (!this->sceneTex[MOON5].loadFromFile("Assets/moon5.png")) abort();
	if (!this->sceneTex[MOON6].loadFromFile("Assets/moon6.png")) abort();
	if (!this->sceneTex[MOON7].loadFromFile("Assets/moon7.png")) abort();
	if (!this->sceneTex[MOON8].loadFromFile("Assets/moon8.png")) abort();

	for (size_t i = 0; i < 2; i++) {
		this->ground[i].setTexture(sceneTex[GROUND]);
		this->ground[i].setPosition(sf::Vector2f(0.f+i*1200.f, 300.f));
		this->ground[i].setColor(this->day ? sf::Color(50, 50, 50, 255) : sf::Color(215, 215, 215, 255));
	}

	for (size_t i = 0; i < 5; i++) {
		this->stars[i].setTexture(sceneTex[rand()%3+2]);
		this->stars[i].setPosition(sf::Vector2f((float)(rand() % 1000), (float)(rand() % 200 + 30)));
		this->stars[i].setColor(this->day ? sf::Color(50, 50, 50, 0) : sf::Color(175, 175, 175, 200));
	}

	this->moon.setTexture(sceneTex[MOON4]);
	this->moon.setPosition(sf::Vector2f(800.f, 100.f));
	this->moon.setColor(this->day ? sf::Color(255, 255, 255, 0) : sf::Color(220, 220, 220, 255));

	for (size_t i = 0; i < 3;i++) {
		this->clouds[i].setTexture(sceneTex[CLOUD]);
		this->clouds[i].setScale(sf::Vector2f(2.f,2.f));
		this->clouds[i].setPosition(sf::Vector2f((float)(rand()%2000), (float)(rand()%200+30)));
		this->clouds[i].setColor(this->day ? sf::Color(235, 235, 235, 255) : sf::Color(50, 50, 50, 255)); 
		this->derSpeedSir[i] = rand() % 3+1;
	}
	if(!font8Bit.loadFromFile("Assets/8bitOperatorPlus8-Bold.ttf")) abort();
	scoreText.setFont(font8Bit);
	scoreText.setString("00000");
	scoreText.setPosition(725.f,5.f);
	scoreText.setFillColor(sf::Color(64, 64, 64, 255));
	scoreText.setCharacterSize(20);
	hScoreText.setFont(font8Bit);
	hScoreText.setString("HI 00000");
	hScoreText.setPosition(615.f,5.f);
	hScoreText.setFillColor(sf::Color(128, 128, 128, 255));
	hScoreText.setCharacterSize(20);
}

Scene::~Scene(){}
