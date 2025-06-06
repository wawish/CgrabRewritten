#include "options-menu.h"
#include <iostream>

optionsMenu::optionsMenu(RenderWindow& window) : window(window) {

	if (!optionsTexture.loadFromFile("Sprites/buttons/options.png") ||
		!displayTexture.loadFromFile("Sprites/buttons/display.png") ||
		!instructionTexture.loadFromFile("Sprites/buttons/instructions.png") ||
		!creditTexture.loadFromFile("Sprites/buttons/credit.png") ||
		!backTexture.loadFromFile("Sprites/buttons/back.png") ||
		!leftArrowTexture.loadFromFile("Sprites/buttons/leftarrow.png") ||
		!rightArrowTexture.loadFromFile("Sprites/buttons/rightarrow.png") ||
		!unhighlightRectTexture.loadFromFile("Sprites/buttons/unhighlight.png") ||
		!highlightRectTexture.loadFromFile("Sprites/buttons/highlight.png")) {
		cerr << "Error loading textures [OPTIONS]" << endl;
	}

	optionsSprite.setTexture(optionsTexture);
	displaySprite.setTexture(displayTexture);
	instructionSprite.setTexture(instructionTexture);
	creditSprite.setTexture(creditTexture);
	backSprite.setTexture(backTexture);
	leftArrowSprite.setTexture(leftArrowTexture);
	rightArrowSprite.setTexture(rightArrowTexture);
	unhighlightRectSprite.setTexture(unhighlightRectTexture);
	highlightRectSprite.setTexture(highlightRectTexture);

	optionsSprite.setPosition(Vector2f(50.f, 40.f));
	displaySprite.setPosition(Vector2f(50.f, 40.f));
	instructionSprite.setPosition(Vector2f(50.f, 40.f));
	creditSprite.setPosition(Vector2f(50.f, 40.f));
	backSprite.setPosition(Vector2f(50.f, 40.f));
	leftArrowSprite.setPosition(Vector2f(50.f, 40.f));
	rightArrowSprite.setPosition(Vector2f(50.f, 40.f));
	unhighlightRectSprite.setPosition(Vector2f(50.f, 40.f));
	highlightRectSprite.setPosition(Vector2f(50.f, 40.f));
	





}