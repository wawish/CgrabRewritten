#include "mainGame.h"
#include "main-menu.h"
#include "Funcs.h"
#include <iostream>
#include "options-menu.h"

using namespace std;
using namespace sf;

Game::Game() :

	gameWindow(sf::VideoMode::getDesktopMode(), "Cash Grab!", sf::Style::None)
{
	selectChoice = gameChoice::showMenu;
	gameWindow.setFramerateLimit(60);

	if (!gameFont.openFromFile("Sprites/Fonts/ka1.ttf")) {
		cerr << "Error loading font" << endl;
	}

	if (!menuBGM.openFromFile("Sprites/soundfx/menuBGM.wav")) {
		cerr << "Error loading BGM Music" << endl;
	}
	
	else {
		menuBGM.setLooping(true);
		menuBGM.setVolume(optionsMenu::musicVol);
		menuBGM.play();
	}
	cout << "Game initialized" << endl;
};

void Game::run() {
	int choice;

	while (selectChoice != gameChoice::exitGame && gameWindow.isOpen()) {
		menuBGM.setVolume(optionsMenu::musicVol);
		if (selectChoice == gameChoice::showMenu) {
			mainMenu menuScreen(gameWindow);
			choice = menuScreen.run();
			if (choice == menuChoices::PLAY) {
				menuBGM.stop();
				selectChoice = gameChoice::playGame;
			}
			else if (choice == menuChoices::OPTIONS) {
				selectChoice = gameChoice::showOptions;
			}
			else if (choice == menuChoices::EXIT) {
				selectChoice = gameChoice::exitGame;
			}
		}
		else if (selectChoice == gameChoice::playGame) {
			gameEngine gamingRun(&gameWindow);
			gamingRun.run();


			if (gameWindow.isOpen()) {
				selectChoice = gameChoice::showMenu;
			}
			else {
				selectChoice = gameChoice::exitGame;
			}


			/*GameMechanics gameMechanics(gameWindow, font);
			selectChoice = gameMechanics.run();*/
		}
		else if(selectChoice == gameChoice::showOptions) {
			optionsMenu options(gameWindow, menuBGM);
			options.run();

			if (gameWindow.isOpen()) {
				selectChoice = gameChoice::showMenu;
			}
			else {
				selectChoice = gameChoice::exitGame;
			}
						
		}
		else if (selectChoice == gameChoice::exitGame) {
			gameWindow.close();
			cout << "Exiting game..." << endl;
		}
		else {
			cerr << "Invalid game choice!" << endl;
			selectChoice = gameChoice::exitGame;
		}

	}

	if (gameWindow.isOpen()) {
		gameWindow.close();
	}

}