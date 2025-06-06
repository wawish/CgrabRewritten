#include "options-menu.h"
#include <iostream>

optionsMenu::optionsMenu(RenderWindow& window) :

	window(window),

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
	musictxtSprite(musictxtTexture)
	
{


	if (!optionsTexture.loadFromFile("Sprites/buttons/options.png") ||
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
		!highlightRectTexture.loadFromFile("Sprites/buttons/highlight.png")) {
		cerr << "Error loading textures [OPTIONS]" << endl;
	}
	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);

	float middle_x = windowWidth / 2.0f;

	optionsSprite.setTexture(optionsTexture);
	//displaySprite.setTexture(displayTexture);
	instructionSprite.setTexture(instructionTexture);
	creditSprite.setTexture(creditTexture);
	backSprite.setTexture(backTexture);
	soundleftArrowSprite.setTexture(soundleftArrowTexture);
	soundrightArrowSprite.setTexture(soundrightArrowTexture);
	musicleftArrowSprite.setTexture(musicleftArrowTexture);
	musicrightArrowSprite.setTexture(musicrightArrowTexture);

	unhighlightRectSprite.setTexture(unhighlightRectTexture);
	highlightRectSprite.setTexture(highlightRectTexture);
	soundtxtSprite.setTexture(soundtxtTexture);
	musictxtSprite.setTexture(musictxtTexture);

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

	soundtxtSprite.setPosition(Vector2f(125.f, 230.f));
	musictxtSprite.setPosition(Vector2f(125.f, 430.f));



	float rectangleSize_x = highlightRectTexture.getSize().x;
	float rectanglePos_x = 125.f + 70.f;
	float rectangleSpace_x = rectangleSize_x + 15.f;



	//SOUND SPRITE

	for (int i = 0; i < rectangleVolume; i++) {
		
		soundRectangle[i]->setPosition(Vector2f(rectanglePos_x, 230.f + 70.f));

		rectanglePos_x += rectangleSpace_x;
	}

	float soundRightArrow_x = soundRectangle[9]->getPosition().x + rectangleSize_x;

	soundleftArrowSprite.setPosition(Vector2f(125.f, 300.f));
	soundrightArrowSprite.setPosition(Vector2f(soundRightArrow_x, 230.f + 70.f));

	//MUSIC SPRITE

	rectanglePos_x = 125.f + 70.f;

	for (int i = 0; i < rectangleVolume; i++) {
		
		musicRectangle[i]->setPosition(Vector2f(rectanglePos_x, 430.f + 70.f));

		rectanglePos_x += rectangleSpace_x;
	}

	float musicRightArrow_x = musicRectangle[9]->getPosition().x + rectangleSize_x;

	musicleftArrowSprite.setPosition(Vector2f(125.f, 500.f));
	musicrightArrowSprite.setPosition(Vector2f(musicRightArrow_x, 430.f + 70.f));

	instructionSprite.setPosition(Vector2f(50.f, 40.f));
	creditSprite.setPosition(Vector2f(50.f, 40.f));


	//displaySprite.setPosition(Vector2f(50.f, 40.f));

}

optionsMenu::~optionsMenu() {
	for (int i = 0; i < rectangleVolume; i++) {
		delete soundRectangle[i];
		delete musicRectangle[i];
	}
}
	

void optionsMenu::render() {

	for (int i = 0; i < rectangleVolume; i++) {

		window.draw(*soundRectangle[i]);
		window.draw(*musicRectangle[i]);
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

			float minusVol = Listener::getGlobalVolume() - volumeIncrement;
			if (minusVol < 0) {
				minusVol = 0;
			}
			Listener::setGlobalVolume(minusVol);

		}
		else if (soundrightArrowSprite.getGlobalBounds().contains(mousePos)) {

			float addVol = Listener::getGlobalVolume() + volumeIncrement;
			if (addVol > 100) {
				addVol = 100;
			}
			Listener::setGlobalVolume(addVol);

		}
		else if (musicleftArrowSprite.getGlobalBounds().contains(mousePos)) {

			musicDB -= volumeIncrement;
			if (musicDB < 0) musicDB = 0;

		}
		else if (musicrightArrowSprite.getGlobalBounds().contains(mousePos)) {

			musicDB += volumeIncrement;
			if (musicDB > 100) musicDB = 100;

		}


	}

	return 0;


}

	
	





