#include "mainGame.h"
#include "main-menu.h"
#include "Funcs.h"
#include <iostream>

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
	cout << "Game initialized" << endl;
};

void Game::run() {
	int choice;

	while (selectChoice != gameChoice::exitGame && gameWindow.isOpen()) {
		if (selectChoice == gameChoice::showMenu) {
			mainMenu menuScreen(gameWindow);
			choice = menuScreen.run();
			if (choice == menuChoices::PLAY) {
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
			gameEngine gamingRun;
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
		else if (selectChoice == gameChoice::showOptions) {

			while (selectChoice == gameChoice::showOptions && gameWindow.isOpen()) {
				while (const optional event = gameWindow.pollEvent()) {
					if (event->is<Event::Closed>()) {

						selectChoice = gameChoice::exitGame;
						gameWindow.close();
					}

					if (const auto* pressedKey = event->getIf<Event::KeyPressed>()) {
						if (pressedKey->code == Keyboard::Key::Escape) {
							selectChoice = gameChoice::showMenu;
						}
					}
				}
				gameWindow.clear(Color(50, 50, 100));


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