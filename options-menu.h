#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class optionsMenu {
	public:	
		optionsMenu();
		optionsMenu(RenderWindow& window);
		~optionsMenu();

		void run();
		float musicDB = 100.f;

	private:

		void inputOptions();
		void changeSettings();
		void render();

		RenderWindow& window;

		Texture optionsTexture, displayTexture, instructionTexture, creditTexture, backTexture, leftArrowTexture, rightArrowTexture, unhighlightRectTexture, highlightRectTexture;
		Sprite optionsSprite, displaySprite, instructionSprite, creditSprite, backSprite, leftArrowSprite, rightArrowSprite, unhighlightRectSprite, highlightRectSprite;
		Vector2f optionsVector, displayVector, instructionVector, creditVector, backVector;

		static const int rectangleVolume = 10;

		Sprite soundRectangle[rectangleVolume];
		Sprite musicRectanlge[rectangleVolume];


};
