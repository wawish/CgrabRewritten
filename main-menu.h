#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Funcs.h"
#include <string>

using namespace sf;
using namespace std;

struct menuChoices {

	static const int PLAY = 1;
	static const int OPTIONS = 2;
	static const int EXIT = 3;
	
};

class mainMenu {
public:

	mainMenu(sf::RenderWindow& window);
	~mainMenu();

	int run();

private:
	RenderWindow& window;

	Font font;
	Text playText, optionsText, exitText;


	Texture menubgTexture;
	Sprite menubgSprite;

	//TEXTURE BUTTONS
	Texture playButtonTexture, optionsButtonTexture, quitButtonTexture, speakerOnTexture, speakerOffTexture, logoTexture;

	//SPRITE BUTTONS
	Sprite playButtonSprite, optionsButtonSprite, quitButtonSprite, speakerOnSprite, speakerOffSprite, logoSprite;

	//VECTOR
	Vector2f playButtonInitialScale, optionsButtonInitialScale, quitButtonInitialScale, speakerOnInitialScale, speakerOffInitialScale;

	

	
	void loadAssets();
	void setupMenu();
	int inputMenu(const Event::MouseButtonPressed&);
	void updateHover();
	void render();

	void toggleMute();

	
	SoundBuffer hoverBuffer;
	Sound* hoverSound;
	SoundBuffer clickBuffer;
	Sound* clickSound = nullptr;
	bool wasOverPlay = false;
	bool wasOverOptions = false;
	bool wasOverQuit = false;
	bool wasOverSpeaker = false;
};

