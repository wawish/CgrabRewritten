#include "main-menu.h"
#include "options-menu.h"
#include <iostream>
#include <string>

const string FONT_PATH = "Sprites/Fonts/ka1.ttf"; // Define the font path

static void positionText(Text& text, float x, float y, bool centered = true) {

	if (centered) {
		FloatRect bounds = text.getLocalBounds();

		text.setOrigin(Vector2f(bounds.position.x + (bounds.size.x / 2.0f),
			bounds.position.y + (bounds.size.y / 2.0f)));
		text.setPosition(Vector2f(x, y));
	}
	else {
		text.setPosition(Vector2f(x, y));
	}
}

mainMenu::mainMenu(RenderWindow& mainWindow) :

	window(mainWindow),
	font(),
	isMuted(false),

	menubgSprite(menubgTexture),
	playButtonSprite(playButtonTexture),
	optionsButtonSprite(optionsButtonTexture),
	quitButtonSprite(quitButtonTexture),
	speakerOnSprite(speakerOnTexture),
	speakerOffSprite(speakerOffTexture),
	logoSprite(logoTexture),

	playText(font, "Play", 30),
	optionsText(font, "Options", 30),
	exitText(font, "Exit", 30)


{

	if (!font.openFromFile(FONT_PATH)) {
		cerr << "Error loading font: " << FONT_PATH << endl;
	}

	playText.setFont(font);
	optionsText.setFont(font);
	exitText.setFont(font);

	loadAssets();



	setupMenu();
	sf::Listener::setGlobalVolume(isMuted ? 0.f : 100.f); // Set initial volume based on mute state

}

mainMenu::~mainMenu() {

}

void mainMenu::loadAssets() {
	// Load textures
	if (!menubgTexture.loadFromFile("Sprites/bg/menubg.png")) {
		cerr << "Error loading background.png" << endl;
	}
	if (!playButtonTexture.loadFromFile("Sprites/buttons/play_button.png") ||
		!optionsButtonTexture.loadFromFile("Sprites/buttons/options_button.png") ||
		!quitButtonTexture.loadFromFile("Sprites/buttons/quit_button.png") ||
		!speakerOnTexture.loadFromFile("Sprites/buttons/speaker_on.png") ||
		!speakerOffTexture.loadFromFile("Sprites/buttons/speaker_off.png") ||
		!logoTexture.loadFromFile("Sprites/bg/logo.png")) {
		cerr << "Error loading textures" << endl;
	}
	if (logoTexture.loadFromFile("Sprites/bg/logo.png")) {
		cout << "Loaded logo.png | Size: "
			<< logoTexture.getSize().x << "x" << logoTexture.getSize().y << endl;
	}

	// Load hover sound effect
	if (!hoverBuffer.loadFromFile("Sprites/soundfx/hover.wav")) {
		cerr << "Error loading hover sound" << endl;
	}
	hoverSound = new Sound(hoverBuffer);
	hoverSound->setBuffer(hoverBuffer);
	hoverSound->setVolume(optionsMenu::soundFX); // Adjust volume as needed

	// Load click sound effect
	if (!clickBuffer.loadFromFile("Sprites/soundfx/click.wav")) {
		cerr << "Error loading click sound" << endl;
	}
	clickSound = new Sound(clickBuffer);
	clickSound->setBuffer(clickBuffer);
	clickSound->setVolume(optionsMenu::soundFX); // Adjust volume as needed


	menubgSprite.setTexture(menubgTexture, true);
	logoSprite.setTexture(logoTexture, true);
	playButtonSprite.setTexture(playButtonTexture, true);
	optionsButtonSprite.setTexture(optionsButtonTexture, true);
	quitButtonSprite.setTexture(quitButtonTexture, true);
	speakerOnSprite.setTexture(speakerOnTexture, true);
	speakerOffSprite.setTexture(speakerOffTexture, true);

	//logoSprite.setTextureRect(IntRect({ 0, 0 }, { 900, 432 }));

	logoSprite.setScale(Vector2f(1.f, 1.f));
	playButtonSprite.setScale(Vector2f(1.f, 1.f));
	optionsButtonSprite.setScale(Vector2f(1.f, 1.f));
	quitButtonSprite.setScale(Vector2f(1.f, 1.f));
	speakerOnSprite.setScale(Vector2f(1.f, 1.f));
	speakerOffSprite.setScale(Vector2f(1.f, 1.f));


	/*playButtonSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(playButtonTexture.getSize())));
	optionsButtonSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(optionsButtonTexture.getSize())));
	quitButtonSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(quitButtonTexture.getSize())));
	speakerOnSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(speakerOnTexture.getSize())));
	speakerOffSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(speakerOffTexture.getSize())));*/
}

void mainMenu::setupMenu() {
	// Set up text properties

	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);

	float menuPos_x = windowWidth / 2.0f;
	float logoPos_y = windowHeight * 0.25f;
	float menu_START_y = windowHeight * 0.45f;
	float menu_SPACING = windowHeight * 0.12f;
	unsigned int fontSize = 30;

	const Vector2f buttonSize(396.f, 18.f);


	//titleText.setFont(font);
	playText.setFont(font);
	optionsText.setFont(font);
	exitText.setFont(font);

	playText.setFillColor(Color::White);
	optionsText.setFillColor(Color::White);
	exitText.setFillColor(Color::White);

	playText.setString("");
	optionsText.setString("");
	exitText.setString("");

	playText.setCharacterSize(fontSize);
	optionsText.setCharacterSize(fontSize);
	exitText.setCharacterSize(fontSize);


	positionText(playText, menuPos_x, menu_START_y);
	positionText(optionsText, menuPos_x, menu_START_y + menu_SPACING);
	positionText(exitText, menuPos_x, menu_START_y + 2 * menu_SPACING);

	FloatRect playBounds = playButtonSprite.getLocalBounds();
	FloatRect optionsBounds = optionsButtonSprite.getLocalBounds();
	FloatRect quitBounds = quitButtonSprite.getLocalBounds();
	FloatRect logoBounds = logoSprite.getLocalBounds();


	playButtonSprite.setOrigin(Vector2f(playBounds.size.x / 2.0f, playBounds.size.y / 2.0f));
	optionsButtonSprite.setOrigin(Vector2f(optionsBounds.size.x / 2.0f, optionsBounds.size.y / 2.0f));
	quitButtonSprite.setOrigin(Vector2f(quitBounds.size.x / 2.0f, quitBounds.size.y / 2.0f));
	logoSprite.setOrigin(Vector2f(logoBounds.size.x / 2.0f, logoBounds.size.y / 2.0f));

	logoSprite.setPosition(Vector2f(menuPos_x, logoPos_y + 50));
	playButtonSprite.setPosition(Vector2f(menuPos_x, menu_START_y + 150));
	optionsButtonSprite.setPosition(Vector2f(menuPos_x, menu_START_y + menu_SPACING + 150));
	quitButtonSprite.setPosition(Vector2f(menuPos_x, menu_START_y + 2 * menu_SPACING + 150));

	float speakerSpace = 30.f;

	FloatRect speakerBounds = speakerOnSprite.getLocalBounds();
	speakerOnSprite.setOrigin(Vector2f(speakerBounds.size.x, 0.f));
	speakerOnSprite.setPosition(Vector2f(windowWidth - speakerSpace, speakerSpace));

	speakerOffSprite.setOrigin(Vector2f(speakerBounds.size.x, 0.f));
	speakerOffSprite.setPosition(Vector2f(windowWidth - speakerSpace, speakerSpace));

	playButtonInitialScale = playButtonSprite.getScale();
	optionsButtonInitialScale = optionsButtonSprite.getScale();
	quitButtonInitialScale = quitButtonSprite.getScale();


	cout << "\n--- In-Depth Debug Info ---" << endl;
	cout << "Window Size: " << window.getSize().x << "x" << window.getSize().y << endl;

	// --- Check the Texture Directly ---
	cout << "logoTexture Size: (" << logoTexture.getSize().x << ", " << logoTexture.getSize().y << ")" << endl;

	// --- Check the Sprite's Internal State ---
	sf::IntRect texRect = logoSprite.getTextureRect();
	sf::FloatRect localBounds = logoSprite.getLocalBounds();

	cout << "Logo Sprite Texture Rect: "
		<< "(L:" << texRect.position.x << ", T:" << texRect.position.y
		<< ", W:" << texRect.size.x << ", H:" << texRect.size.y << ")" << endl;

	cout << "Logo Sprite Local Bounds: "
		<< "(L:" << localBounds.position.x << ", T:" << localBounds.position.y
		<< ", W:" << localBounds.size.x << ", H:" << localBounds.size.y << ")" << endl;

	cout << "Logo Sprite Scale: (" << logoSprite.getScale().x << ", "
		<< logoSprite.getScale().y << ")" << endl;

	cout << "Logo Sprite Position: (" << logoSprite.getPosition().x << ", "
		<< logoSprite.getPosition().y << ")" << endl;

	cout << "Logo Sprite Origin: (" << logoSprite.getOrigin().x << ", "
		<< logoSprite.getOrigin().y << ")" << endl;

	// --- Check the Final Global Bounds ---
	sf::FloatRect globalBounds = logoSprite.getGlobalBounds();
	cout << "Logo Sprite Global Bounds (Final): "
		<< "(L:" << globalBounds.position.x << ", T:" << globalBounds.position.y
		<< ", W:" << globalBounds.size.x << ", H:" << globalBounds.size.y << ")" << endl;



	cout << "--------------------------------\n" << endl;

}



int mainMenu::run() {
    Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
                return menuChoices::EXIT;
            }
            if (const auto* mouseEvent = event->getIf<Event::MouseButtonPressed>()) {
                if (mouseEvent->button == Mouse::Button::Left) {

                    Vector2f mousePos(static_cast<float>(mouseEvent->position.x),
                        static_cast<float>(mouseEvent->position.y));

                    if ((!isMuted && speakerOnSprite.getGlobalBounds().contains(mousePos)) ||
                        isMuted && speakerOffSprite.getGlobalBounds().contains(mousePos)) {
                        
						toggleMute();

                    }

                    else {
                        int redirect = inputMenu(*mouseEvent);
                        if (redirect != 0) {
                            return redirect;
                        }


                    }
                }
            }
        }
        updateHover();
        render();
    }
    return menuChoices::EXIT;
}


int mainMenu::inputMenu(const Event::MouseButtonPressed& mouseEvent) {

	Vector2f mouseClick(static_cast<float>(mouseEvent.position.x),
		static_cast<float>(mouseEvent.position.y));

	// --- CORRECTED DEBUGGING BLOCK ---
	sf::FloatRect playBounds = playButtonSprite.getGlobalBounds();
	cout << "--------------------------------" << endl;
	cout << "Mouse Clicked at: (" << mouseClick.x << ", " << mouseClick.y << ")" << endl;
	cout << "Checking against Play Button Bounds: "
		<< "Left: " << playBounds.position.x << ", Top: " << playBounds.position.y
		<< ", Width: " << playBounds.size.x << ", Height: " << playBounds.size.y << ")" << endl;
	// --- END DEBUGGING BLOCK ---

	if (playButtonSprite.getGlobalBounds().contains(mouseClick)) {
		if (clickSound) clickSound->play();
		cout << "Playing... Grab as many cash as you can!" << endl;
		return menuChoices::PLAY;
	}

	else if (optionsButtonSprite.getGlobalBounds().contains(mouseClick)) {
		if (clickSound) clickSound->play();
		return menuChoices::OPTIONS;
	}
	else if (quitButtonSprite.getGlobalBounds().contains(mouseClick)) {
		if (clickSound) clickSound->play();
		cout << "See you next time!" << endl;
		return menuChoices::EXIT;
	}

	return 0;
}

void mainMenu::updateHover() {

	const View& view = window.getView();

	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window), view);

	Color buttonHighlight(200, 200, 200);
	Color buttonNormal(255, 255, 255, 255);

	const float hoverScaleFactor = 1.1f;

	// Hover sound effect mechanics
	bool overPlay = playButtonSprite.getGlobalBounds().contains(mousePos);
	bool overOptions = optionsButtonSprite.getGlobalBounds().contains(mousePos);
	bool overQuit = quitButtonSprite.getGlobalBounds().contains(mousePos);
	bool overSpeaker = isMuted
		? speakerOffSprite.getGlobalBounds().contains(mousePos)
		: speakerOnSprite.getGlobalBounds().contains(mousePos);

	// Play hover sound when mouse enters a button
	if ((overPlay && !wasOverPlay) ||
		(overOptions && !wasOverOptions) ||
		(overQuit && !wasOverQuit) ||
		(overSpeaker && !wasOverSpeaker)) {
		if (hoverSound) hoverSound->play();
	}

	wasOverPlay = overPlay;
	wasOverOptions = overOptions;
	wasOverQuit = overQuit;
	wasOverSpeaker = overSpeaker;


	if (playButtonSprite.getGlobalBounds().contains(mousePos)) {
		playButtonSprite.setScale(playButtonInitialScale * hoverScaleFactor);
		playButtonSprite.setColor(buttonHighlight);
	}
	else {
		playButtonSprite.setScale(playButtonInitialScale);
		playButtonSprite.setColor(buttonNormal);
	}


	if (optionsButtonSprite.getGlobalBounds().contains(mousePos)) {
		optionsButtonSprite.setScale(optionsButtonInitialScale * hoverScaleFactor);
		optionsButtonSprite.setColor(buttonHighlight);
	}
	else {
		optionsButtonSprite.setScale(optionsButtonInitialScale);
		optionsButtonSprite.setColor(buttonNormal);
	}

	if (quitButtonSprite.getGlobalBounds().contains(mousePos)) {
		quitButtonSprite.setScale(quitButtonInitialScale * hoverScaleFactor);
		quitButtonSprite.setColor(buttonHighlight);
	}
	else {
		quitButtonSprite.setScale(quitButtonInitialScale);
		quitButtonSprite.setColor(buttonNormal);
	}


}

void mainMenu::render() {
    window.clear(Color::Black);
    window.draw(menubgSprite);


    window.draw(logoSprite);
    window.draw(playButtonSprite);
    window.draw(playText);

    window.draw(optionsButtonSprite);
    window.draw(optionsText);

    window.draw(quitButtonSprite);
    window.draw(exitText);

    sf::FloatRect textBounds = playText.getGlobalBounds();
    sf::RectangleShape boundsRect(sf::Vector2f(textBounds.size.x, textBounds.size.y));
    boundsRect.setPosition(Vector2f(textBounds.position.x, textBounds.position.y));
    boundsRect.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red
    window.draw(boundsRect);

    if (isMuted) {
        window.draw(speakerOffSprite);
    } else {
        window.draw(speakerOnSprite);
    }

    window.display();
}

void mainMenu::toggleMute() {
	if (clickSound) clickSound->play();

	isMuted = !isMuted;
	
	if (isMuted) {
		sf::Listener::setGlobalVolume(0.f);
	}
	else {
		sf::Listener::setGlobalVolume(100.f);
	}
	cout << (isMuted ? "Sound muted." : "Sound unmuted.") << endl;
}


