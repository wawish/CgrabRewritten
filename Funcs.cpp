#include "Funcs.h"
#include <random>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

gameEngine::gameEngine()
    : window(), player(window.window)
{
    activeCoins = 5;
}

void gameEngine::run()
{
    sf::Clock clock;
    while (window.window->isOpen()) {
        float delta = clock.restart().asSeconds();
        window.window->clear();
        player.checkEvent(window.window, delta);
        player.render(window.window);

        for (int i = 0; i < activeCoins; i++) {
            coin[i].update(delta);
            coin[i].rendering(window.window);
        }
        for (int i = 0; i < activeCoins; i++) {
            if (coin[i].spritecoin->getGlobalBounds().findIntersection(player.spriteplayer->getGlobalBounds())) {
                player.score += 100;
                cout << "hit! " << player.score << endl;
                coin[i].respawn();
            }
        }

        static int lastThreshold = 0;
        int threshold = player.score / 500;
        if (threshold > lastThreshold && activeCoins < 20) {
            cout << "THRESHOLD REACHED! " << player.score << endl;
            activeCoins++;
            lastThreshold = threshold;
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

void Player::render(RenderWindow* l)
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
    spritecoin->setScale({ .75f, .75f });
    respawn();
}

void Money::respawn() {
    randomValX = (1280 - 32) * getRandomNumber();
    float y = 0.f;
    spritecoin->setPosition({ randomValX, y });
    fallSpeed = 200.f + getRandomNumber() * 400.f; // 200-600 px/sec
}

void Money::update(float deltaTime) {
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
        respawn();
    }
}

void Money::rendering(RenderWindow* l)
{

    l->draw(*spritecoin);

}
