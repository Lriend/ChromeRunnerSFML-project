#include "manager.h"

int main()
{
	Manager game;

	while (game.isOpen()) {
		while (game.pollEvent()) {
			if (game.getEventType() == sf::Event::Closed) {
				game.close();
			}
			game.handleEvents();
		}
		game.update();
		game.clear();
		game.render();
		game.display();
	}

	return 0;
}