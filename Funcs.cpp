#include "Funcs.h"
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;
using namespace std;

gameEngine::gameEngine()
    : window(), player(window.window)
{
    activeCoins = 5; //coins currently onscreen
    activeBombs = 3; //bombs currently onscreen
    lastcoinThreshold = 0; //stores the current threshold for coins
    lastbombThreshold = 0; //stores the current threshold for bombs
}

void gameEngine::run()
{
    sf::Clock clock;
    while (window.window->isOpen()) {
        float delta = clock.restart().asSeconds(); //delta time var
        window.window->clear(); //clears the window
        player.checkEvent(window.window, delta); //keystroke checker
        player.renderplayer(window.window); //draws the player

        for (int i = 0; i < activeCoins; i++) { //falling coins
            coin[i].updatecoin(delta);
            coin[i].rendercoin(window.window);
        }
        for (int i = 0; i < activeBombs; i++) { //falling bombs
            bomb[i].updatebomb(delta);
            bomb[i].renderbomb(window.window);
        }
        for (int i = 0; i < activeCoins; i++) { //collision checker for coins
            if (coin[i].spritecoin->getGlobalBounds().findIntersection(player.spriteplayer->getGlobalBounds())) {
                player.score += 100;
                coin[i].coinSounds->play();
                cout << "hit! " << player.score << endl;
                coin[i].respawncoin();
            }
        }
        for (int i = 0; i < activeBombs; i++) { //collision checker for bombs
            if (bomb[i].spritebomb->getGlobalBounds().findIntersection(player.spriteplayer->getGlobalBounds())) {
                player.health -= 1;
                bomb[i].bombSounds->play();
                cout << "explode! " << player.health << endl;
                bomb[i].respawnbomb();
            }
        }

        int cointhreshold = player.score / 100; //coin ramp up
        if (cointhreshold > lastcoinThreshold && activeCoins < 10) {
            cout << "THRESHOLD REACHED! " << player.score << endl;
            activeCoins++;
            for (int i = 0; i < activeCoins; ++i) {
                coin[i].coinFallspeed += 50.f;
            }
            lastcoinThreshold = cointhreshold;
        }


        int bombthreshold = player.score / 1000; //bomb ramp up
        if (bombthreshold > lastbombThreshold && activeBombs < 25) {
            cout << "THRESHOLD REACHED! Amount of Bombs: " << activeBombs << endl;
            activeBombs++;
            for (int i = 0; i < activeBombs; ++i) {
                bomb[i].bombFallspeed += 50.f;
            }   
            lastbombThreshold = bombthreshold;
        }

        window.window->display(); //draws the screen
    }
}

gameWindow::gameWindow()
{
    window = new RenderWindow(VideoMode({ 1280, 720 }), "Cash Grab!"); //initializes the window
    window->setFramerateLimit(60);
}

gameWindow::~gameWindow() //deconstructor
{
    delete window;
}

Player::~Player() //deconstructor
{
    delete spriteplayer;
}
 
Player::Player(RenderWindow* l)
{  
    score = 0;
    health = 25;
    if (!textureplayer.loadFromFile("Sprites/player/playerwalk.png")) //checks if it load properly
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spriteplayer = new Sprite(textureplayer); //init for player sprite
    spriteplayer->setTextureRect(IntRect({ 0, 0 }, { 24, 32 })); //sets the sprite as a rectangle
    spriteplayer->setScale({ 3.0f, 3.0f }); //triples the size
    moveSpeed = 700.f; //init for player ms
    playerX = 600.f; //init for startpos
    spriteplayer->setPosition({ playerX, 624.f });

}

void Player::renderplayer(RenderWindow* l) //draws the player
{
    l->draw(*spriteplayer); 

}

void Player::checkEvent(RenderWindow* l, float x)
{
    while (auto event = l->pollEvent()) //checks for event
    {
        
        if (event->is<Event::Closed>()) //when x is clicked
        {
            l->close();
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::D))
    {
        moveRight(x);

    }
    if (Keyboard::isKeyPressed(Keyboard::Key::A))
    {
        moveLeft(x);
    }
}

void Player::moveRight(float x)
{
    playerX += moveSpeed * x;
    float spriteWidth = spriteplayer->getGlobalBounds().size.x;
    float windowWidth = 1280.f;
    if (playerX + spriteWidth > windowWidth) {
        playerX = windowWidth - spriteWidth;
    }
    spriteplayer->setPosition({ playerX, 624.f });
}

void Player::moveLeft(float x)
{
    playerX -= moveSpeed * x;
    spriteplayer->setPosition({ playerX, 624.f });
    auto bounds = spriteplayer->getGlobalBounds();
    if (bounds.position.x < 0.f) {
        playerX = 0.f;
        spriteplayer->setPosition({ 0.f, 624.f });
    }
}

float getRandomNumber() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

Money::Money()
{

    if (!takeCoin.loadFromFile("Sprites/soundfx/pickupCoin.wav")) {
        cout << "ERROR LOADING COIN SOUND" << endl;
    }
    coinSounds = new Sound(takeCoin);
    coinSounds->setBuffer(takeCoin);
    coinFallspeed = 250.f;
    frameDuration = 0.025f;
    frameTimer = 0.f;
    frameWidth = 64;
    frameHeight = 64;
    totalFrames = 25;
    currentFrame = 0;
    if (!texturecoin.loadFromFile("Sprites/money/coin.png"))
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spritecoin = new Sprite(texturecoin);
    spritecoin->setTextureRect(IntRect({ 0, 0 }, { 64, 64 }));
    spritecoin->setScale({ .5f, .5f });
    respawncoin();
}

void Money::respawncoin() {
    randomValX = (1280 - 32) * getRandomNumber();
    float y = 0.f;
    spritecoin->setPosition({ randomValX, y });
    fallSpeed = coinFallspeed + getRandomNumber() * 100.f;
}

void Money::updatecoin(float deltaTime) {
    frameTimer += deltaTime;

    if (frameTimer >= frameDuration) {
        currentFrame = (currentFrame + 1) % totalFrames;
        spritecoin->setTextureRect(IntRect({ currentFrame * frameWidth, 0 }, { frameWidth, frameHeight }));
        frameTimer = 0.f;
    }

    auto Xpos = spritecoin->getPosition().x;
    auto Ypos = spritecoin->getPosition().y;
    spritecoin->setPosition({ Xpos, Ypos + fallSpeed * deltaTime });

    if (spritecoin->getPosition().y > 720) {
        respawncoin();
    }
}

void Money::rendercoin(RenderWindow* l)
{
    l->draw(*spritecoin);
}

Bomb::Bomb()
{
    if (!takeBomb.loadFromFile("Sprites/soundfx/explosion.wav")) {
        cout << "ERROR LOADING COIN SOUND" << endl;
    }
    bombSounds = new Sound(takeBomb);
    bombSounds->setBuffer(takeBomb);
    bombFallspeed = 200.f;
    frameDuration = 0.1f;
    frameTimer = 0.f;
    frameWidth = 20;
    frameHeight = 26;
    totalFrames = 6;
    currentFrame = 0;
    if (!texturebomb.loadFromFile("Sprites/bomb/bomb.png"))
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spritebomb = new Sprite(texturebomb);
    spritebomb->setTextureRect(IntRect({ 0, 0 }, { 20, 26 }));
    spritebomb->setScale({ 1.6f, 1.2307f });
    respawnbomb();
}

void Bomb::respawnbomb() {
    randomValX = (1280 - 32) * getRandomNumber();
    float y = 0.f;
    spritebomb->setPosition({ randomValX, y });
    fallSpeed = bombFallspeed + getRandomNumber() * 100.f;
}

void Bomb::updatebomb(float deltaTime) {
    frameTimer += deltaTime;

    if (frameTimer >= frameDuration) {
        currentFrame = (currentFrame + 1) % totalFrames;
        spritebomb->setTextureRect(IntRect({ currentFrame * frameWidth, 0 }, { frameWidth, frameHeight }));
        frameTimer = 0.f;
    }

    auto Xpos = spritebomb->getPosition().x;
    auto Ypos = spritebomb->getPosition().y;
    spritebomb->setPosition({ Xpos, Ypos + fallSpeed * deltaTime });

    if (spritebomb->getPosition().y > 720) {
        respawnbomb();
    }
}

void Bomb::renderbomb(RenderWindow* l)
{
    l->draw(*spritebomb);
}
