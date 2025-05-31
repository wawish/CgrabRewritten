#include "Funcs.h"
#include <random>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

gameEngine::gameEngine()
    : window(), player(window.window)
{
    activeCoins = 5;
    activeBombs = 3;
    lastcoinThreshold = 0;   // <-- initialize here
    lastbombThreshold = 0;   // <-- and here
}

void gameEngine::run()
{
    sf::Clock clock;
    while (window.window->isOpen()) {
        float delta = clock.restart().asSeconds();
        window.window->clear();
        player.checkEvent(window.window, delta);
        player.renderplayer(window.window);

        for (int i = 0; i < activeCoins; i++) {
            coin[i].updatecoin(delta);
            coin[i].rendercoin(window.window);
        }
        for (int i = 0; i < activeBombs; i++) {
            bomb[i].updatebomb(delta);
            bomb[i].renderbomb(window.window);
        }
        for (int i = 0; i < activeCoins; i++) {
            if (coin[i].spritecoin->getGlobalBounds().findIntersection(player.spriteplayer->getGlobalBounds())) {
                player.score += 100;
                cout << "hit! " << player.score << endl;
                coin[i].respawncoin();
            }
        }
        for (int i = 0; i < activeBombs; i++) {
            if (bomb[i].spritebomb->getGlobalBounds().findIntersection(player.spriteplayer->getGlobalBounds())) {
                player.health -= 1;
                cout << "explode! " << player.health << endl;
                bomb[i].respawnbomb();
            }
        }

        int cointhreshold = player.score / 100;
        if (cointhreshold > lastcoinThreshold && activeCoins < 10) {
            cout << "THRESHOLD REACHED! " << player.score << endl;
            activeCoins++;
            for (int i = 0; i < activeCoins; ++i) {
                coin[i].coinFallspeed += 50.f;
            }
            lastcoinThreshold = cointhreshold;
        }


        int bombthreshold = player.score / 1000;
        if (bombthreshold > lastbombThreshold && activeBombs < 100) {
            cout << "THRESHOLD REACHED! Amount of Bombs: " << activeBombs << endl;
            activeBombs++;
            for (int i = 0; i < activeBombs; ++i) {
                bomb[i].bombFallspeed += 50.f;
            }
            lastbombThreshold = bombthreshold;
        }

        window.window->display();
    }
}

gameWindow::gameWindow()
{
    window = new RenderWindow(VideoMode({ 1280, 720 }), "Minecraft");
    window->setFramerateLimit(144);
}

gameWindow::~gameWindow()
{
    delete window;
}

Player::~Player()
{
    delete spriteplayer;
}
 
Player::Player(RenderWindow* l)
{  
    score = 0;
    health = 25;
    if (!textureplayer.loadFromFile("Sprites/player/playerwalk.png"))
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spriteplayer = new Sprite(textureplayer);
    spriteplayer->setTextureRect(IntRect({ 0, 0 }, { 24, 32 }));
    spriteplayer->setScale({ 3.0f, 3.0f });
    moveSpeed = 2000.f;
    length = 40.f;  
    width = 120.f;
    playerX = 600.f;
    spriteplayer->setPosition({ playerX, 624.f });

}

void Player::renderplayer(RenderWindow* l)
{
    l->draw(*spriteplayer); 

}

void Player::checkEvent(RenderWindow* l, float x)
{
    while (auto event = l->pollEvent())
    {
        if (event->is<Event::KeyPressed>())
        {
            auto keyEvent = event->getIf<Event::KeyPressed>();
       
            if (keyEvent->code == Keyboard::Key::D)
            {
                cout << "Moved Right" << endl;
                moveRight(x);
               
            }
            if (keyEvent->code == Keyboard::Key::A)
            {
                cout << "Moved Left" << endl;
                moveLeft(x);
            }
        }
        if (event->is<Event::Closed>())
        {
            l->close();
        }
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
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

Money::Money()
{
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
    bombFallspeed = 200.f;
    frameDuration = 0.1f;
    frameTimer = 0.f;
    frameWidth = 64;
    frameHeight = 64;
    totalFrames = 2;
    currentFrame = 0;
    if (!texturebomb.loadFromFile("Sprites/bomb/bomb.png"))
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spritebomb = new Sprite(texturebomb);
    spritebomb->setTextureRect(IntRect({ 0, 0 }, { 32, 32 }));
    spritebomb->setScale({ 2.f, 2.f });
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
