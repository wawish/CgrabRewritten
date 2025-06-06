#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;
using namespace std;

class optionsMenu {
	public:	
		
		optionsMenu(RenderWindow& window, Music& BGM);
		~optionsMenu();

		void run();
		
		static float soundFX;
		static float musicVol;

	private:

		int inputOptions(const Event::MouseButtonPressed&);

		void changeSettings();
		void render();

		RenderWindow& window;

		Texture optionsTexture, displayTexture, instructionTexture, creditTexture, backTexture;
		Texture soundleftArrowTexture, soundrightArrowTexture, musicleftArrowTexture, musicrightArrowTexture, unhighlightRectTexture, highlightRectTexture, musictxtTexture, soundtxtTexture;
		Texture sameBGTexture;

		Sprite optionsSprite, displaySprite, instructionSprite, creditSprite, backSprite;
		Sprite soundleftArrowSprite, soundrightArrowSprite, musicleftArrowSprite, musicrightArrowSprite, unhighlightRectSprite, highlightRectSprite, musictxtSprite, soundtxtSprite;
		Sprite sameBGSprite;

		Vector2f optionsVector, displayVector, instructionVector, creditVector, backVector;

		static const int rectangleVolume = 10;

		Sprite* soundRectangle[rectangleVolume];
		Sprite* musicRectangle[rectangleVolume];

		Music& menuBGM;


};
