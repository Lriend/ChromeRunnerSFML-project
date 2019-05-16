#pragma once
#include <SFML/Graphics.hpp>

enum SCENETEX{CLOUD, GROUND, STAR0, STAR1, STAR2, MOON0, MOON1, MOON2, MOON3, MOON4, MOON5, MOON6, MOON7, MOON8};

class Scene
{
	bool day;
	sf::Texture sceneTex[14];
	sf::Sprite ground[2];
	sf::Sprite clouds[3];
	int derSpeedSir[3];
	sf::Sprite moon;
	sf::Sprite stars[5];
public:
	bool getDay();
	void handleEvents(sf::Event &event);
	void update();
	void render(sf::RenderWindow &window);
	Scene();
	~Scene();
};

