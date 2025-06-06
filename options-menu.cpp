#include "options-menu.h"
#include "Funcs.h"
#include <iostream>

float optionsMenu::soundFX = 80;
float optionsMenu::musicVol = 80;
const float globalScale = 0.80f, decrementScale = 0.10f;

optionsMenu::optionsMenu(RenderWindow& window, Music& BGM) :

	window(window),
	menuBGM(BGM),
	optionsSprite(optionsTexture),
	displaySprite(displayTexture),
	instructionSprite(instructionTexture),
	creditSprite(creditTexture),
	backSprite(backTexture),
	soundleftArrowSprite(soundleftArrowTexture),
	soundrightArrowSprite(soundrightArrowTexture),
	musicleftArrowSprite(musicleftArrowTexture),
	musicrightArrowSprite(musicrightArrowTexture),
	unhighlightRectSprite(unhighlightRectTexture),
	highlightRectSprite(highlightRectTexture),
	soundtxtSprite(soundtxtTexture),
	musictxtSprite(musictxtTexture),
	sameBGSprite(sameBGTexture)
	
{

	

	if (!optionsTexture.loadFromFile("Sprites/buttons/options_button.png") ||
		//!displayTexture.loadFromFile("Sprites/buttons/display.png") ||
		!instructionTexture.loadFromFile("Sprites/buttons/instructions.png") ||
		!creditTexture.loadFromFile("Sprites/buttons/credit.png") ||
		!backTexture.loadFromFile("Sprites/buttons/back.png") ||
		!soundleftArrowTexture.loadFromFile("Sprites/buttons/leftarrow.png") ||
		!soundrightArrowTexture.loadFromFile("Sprites/buttons/rightarrow.png") ||
		!musicleftArrowTexture.loadFromFile("Sprites/buttons/leftarrow.png") ||
		!musicrightArrowTexture.loadFromFile("Sprites/buttons/rightarrow.png") ||
		!unhighlightRectTexture.loadFromFile("Sprites/buttons/unhighlight.png") ||
		!soundtxtTexture.loadFromFile("Sprites/buttons/soundtxt.png") ||
		!musictxtTexture.loadFromFile("Sprites/buttons/musictxt.png") ||
		!highlightRectTexture.loadFromFile("Sprites/buttons/highlight.png") ||
		!sameBGTexture.loadFromFile("Sprites/bg/menubg.png")) {
		cerr << "Error loading textures [OPTIONS]" << endl;
	}

	backSprite.setScale(Vector2f(globalScale, globalScale));
	optionsSprite.setScale(Vector2f(globalScale, globalScale));

	soundtxtSprite.setScale(Vector2f(1.4, 1.4));
	musictxtSprite.setScale(Vector2f(1.4, 1.4));

	soundleftArrowSprite.setScale(Vector2f(globalScale, globalScale));
	soundrightArrowSprite.setScale(Vector2f(globalScale, globalScale));
	musicleftArrowSprite.setScale(Vector2f(globalScale, globalScale));
	musicrightArrowSprite.setScale(Vector2f(globalScale, globalScale));
	instructionSprite.setScale(Vector2f(globalScale, globalScale));
	creditSprite.setScale(Vector2f(globalScale, globalScale));

	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);

	float middle_x = windowWidth / 2.0f;

	optionsSprite.setTexture(optionsTexture, true);
	//displaySprite.setTexture(displayTexture);
	instructionSprite.setTexture(instructionTexture, true);
	creditSprite.setTexture(creditTexture, true);
	backSprite.setTexture(backTexture, true);
	soundleftArrowSprite.setTexture(soundleftArrowTexture, true);
	soundrightArrowSprite.setTexture(soundrightArrowTexture, true);
	musicleftArrowSprite.setTexture(musicleftArrowTexture, true);
	musicrightArrowSprite.setTexture(musicrightArrowTexture, true);

	unhighlightRectSprite.setTexture(unhighlightRectTexture, true);
	highlightRectSprite.setTexture(highlightRectTexture, true);
	soundtxtSprite.setTexture(soundtxtTexture, true);
	musictxtSprite.setTexture(musictxtTexture, true);
	sameBGSprite.setTexture(sameBGTexture, true);

	soundRectangle[0] = new Sprite(unhighlightRectTexture);
	soundRectangle[1] = new Sprite(unhighlightRectTexture);
	soundRectangle[2] = new Sprite(unhighlightRectTexture);
	soundRectangle[3] = new Sprite(unhighlightRectTexture);
	soundRectangle[4] = new Sprite(unhighlightRectTexture);
	soundRectangle[5] = new Sprite(unhighlightRectTexture);
	soundRectangle[6] = new Sprite(unhighlightRectTexture);
	soundRectangle[7] = new Sprite(unhighlightRectTexture);
	soundRectangle[8] = new Sprite(unhighlightRectTexture);
	soundRectangle[9] = new Sprite(unhighlightRectTexture);

	musicRectangle[0] = new Sprite(unhighlightRectTexture);
	musicRectangle[1] = new Sprite(unhighlightRectTexture);
	musicRectangle[2] = new Sprite(unhighlightRectTexture);
	musicRectangle[3] = new Sprite(unhighlightRectTexture);
	musicRectangle[4] = new Sprite(unhighlightRectTexture);
	musicRectangle[5] = new Sprite(unhighlightRectTexture);
	musicRectangle[6] = new Sprite(unhighlightRectTexture);
	musicRectangle[7] = new Sprite(unhighlightRectTexture);
	musicRectangle[8] = new Sprite(unhighlightRectTexture);
	musicRectangle[9] = new Sprite(unhighlightRectTexture);



	backSprite.setPosition(Vector2f(50.f, 40.f));

	optionsSprite.setOrigin(Vector2f(optionsSprite.getLocalBounds().size.x / 2.f, 0.f));
	optionsSprite.setPosition(Vector2f(middle_x, 40.f));

	soundtxtSprite.setOrigin(Vector2f(soundtxtSprite.getLocalBounds().size.x / 2.f, 0.f));
	soundtxtSprite.setPosition(Vector2f(WINDOW_WIDTH/2, 190.f));

	musictxtSprite.setOrigin(Vector2f(musictxtSprite.getLocalBounds().size.x / 2.f, 0.f));
	musictxtSprite.setPosition(Vector2f(WINDOW_WIDTH/2, 390.f));



	float rectangleSize_x = highlightRectTexture.getSize().x;
	float rectanglePos_x = 145.f + 70.f;
	float rectangleSpace_x = rectangleSize_x - 20.0f;



	//SOUND SPRITE

	for (int i = 0; i < rectangleVolume; i++) {
		
		soundRectangle[i]->setPosition(Vector2f(350 + rectanglePos_x, 230.f + 70.f));
		soundRectangle[i]->setScale(Vector2f(globalScale-decrementScale, globalScale - decrementScale));

		rectanglePos_x += rectangleSpace_x;
	}

	float soundRightArrow_x = soundRectangle[9]->getPosition().x + rectangleSize_x;

	soundleftArrowSprite.setPosition(Vector2f(350 + 125.f - 10.f, 300.f - 5.f));
	soundrightArrowSprite.setPosition(Vector2f(soundRightArrow_x - 10.f, 230.f + 70.f - 5.f));

	//MUSIC SPRITE

	rectanglePos_x = 145.f + 70.f;

	for (int i = 0; i < rectangleVolume; i++) {
		
		musicRectangle[i]->setPosition(Vector2f(350 + rectanglePos_x, 430.f + 70.f));
		musicRectangle[i]->setScale(Vector2f(globalScale - decrementScale, globalScale - decrementScale));

		rectanglePos_x += rectangleSpace_x;
	}

	float musicRightArrow_x = musicRectangle[9]->getPosition().x + rectangleSize_x;

	musicleftArrowSprite.setPosition(Vector2f(350 + 125.f - 10.f, 500.f - 5.f));
	musicrightArrowSprite.setPosition(Vector2f(musicRightArrow_x - 10.f, 430.f + 70.f - 5.f));


	instructionSprite.setOrigin(Vector2f(instructionSprite.getLocalBounds().size.x, 0.f));
	instructionSprite.setPosition(Vector2f(50.f, 40.f));

	creditSprite.setOrigin(Vector2f(creditSprite.getLocalBounds().size.x, 0.f));
	creditSprite.setPosition(Vector2f(50.f, 40.f));


	//displaySprite.setPosition(Vector2f(50.f, 40.f));

}

optionsMenu::~optionsMenu() {
	for (int i = 0; i < rectangleVolume; i++) {
		delete soundRectangle[i];
		delete musicRectangle[i];
	}
}
	



int optionsMenu::inputOptions(const Event::MouseButtonPressed& mouseEvent) {

	if (mouseEvent.button == Mouse::Button::Left) {

		Vector2f mousePos(static_cast<float>(mouseEvent.position.x),
			static_cast<float>(mouseEvent.position.y));


		if (backSprite.getGlobalBounds().contains(mousePos)){
			return 1;
		}

		const float volumeIncrement = 100.f / rectangleVolume;

		if (soundleftArrowSprite.getGlobalBounds().contains(mousePos)) {

			soundFX -= volumeIncrement;
			if (soundFX < 0) {
				soundFX = 0;
			}

		}
		else if (soundrightArrowSprite.getGlobalBounds().contains(mousePos)) {

			soundFX += volumeIncrement;
			if (soundFX > 100) {
				soundFX = 100;
			}

		}
		else if (musicleftArrowSprite.getGlobalBounds().contains(mousePos)) {

			musicVol -= volumeIncrement;
			if (musicVol < 0) {
				musicVol = 0;
			}
			menuBGM.setVolume(musicVol);

		}
		else if (musicrightArrowSprite.getGlobalBounds().contains(mousePos)) {

			musicVol += volumeIncrement;
			if (musicVol > 100) {
				musicVol = 100;
			} 
			menuBGM.setVolume(musicVol);

		}


	}

	return 0;


}

void optionsMenu::run() {
	Clock clock;
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>()) {
				window.close();
				return;
			}
			
			if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPress->code == sf::Keyboard::Key::Escape) {
					return;
				}
			}

			if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
				
				int redirect = inputOptions(*mouseEvent);				
				if (redirect!= 0) {
					return;
				}
			}

		}
		changeSettings();
		render();
	}
	return;

	
}

void optionsMenu::changeSettings() {

	int highlightedSound = (soundFX / 10.f);
	int highlightedMusic = (musicVol / 10.f);

	for (int i = 0; i < rectangleVolume; i++) {
		if (i < highlightedSound) {
			soundRectangle[i]->setTexture(highlightRectTexture);
			
		}
		else {
			soundRectangle[i]->setTexture(unhighlightRectTexture);
			
		}
	}

	

	for (int i = 0; i < rectangleVolume; i++) {
		if (i < highlightedMusic) {
			musicRectangle[i]->setTexture(highlightRectTexture);
			
		}
		else {
			musicRectangle[i]->setTexture(unhighlightRectTexture);
			
		}
	}

}

void optionsMenu::render() {

	window.clear();
	window.draw(sameBGSprite);

	window.draw(backSprite);
	window.draw(optionsSprite);
	window.draw(soundtxtSprite);
	window.draw(musictxtSprite);
	window.draw(soundleftArrowSprite);
	window.draw(soundrightArrowSprite);
	window.draw(musicleftArrowSprite);
	window.draw(musicrightArrowSprite);


	for (int i = 0; i < rectangleVolume; i++) {

		window.draw(*soundRectangle[i]);
		window.draw(*musicRectangle[i]);
	}

	window.display();
}

	
	





