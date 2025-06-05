#pragma once

#include <SFML/Graphics.hpp>

struct gameChoice {

	static const int showMenu = 0;
	static const int playGame = 1;
	static const int showOptions = 2;
	static const int exitGame = 3;
};

class Game {
private:

	sf::RenderWindow gameWindow;
	int selectChoice;
	sf::Font gameFont;

public:

	Game();
	void run();
};