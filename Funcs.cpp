#include "Funcs.h"
#include <random>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

gameEngine::gameEngine()
    : window(), player(window.window)
{

}

void gameEngine::run()
{
    sf::Clock clock;
    while (window.window->isOpen()) {
        float delta = clock.restart().asSeconds();
        window.window->clear();
        player.checkEvent(window.window, delta);
        player.render(window.window);
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
    if (!textureplayer.loadFromFile("Sprites/player/playerwalk.png"))
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spriteplayer = new Sprite(textureplayer);
    spriteplayer->setTextureRect(IntRect({ 0, 0 }, { 32, 32 }));
    spriteplayer->setScale({ 3.0f, 3.0f });
    moveSpeed = 500.f;
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
        if (event->is<sf::Event::KeyPressed>())
        {
            auto keyEvent = event->getIf<Event::KeyPressed>();
       
            if (keyEvent->code == sf::Keyboard::Key::D)
            {
                float nextX = playerX + moveSpeed * x;
                float rightEdge = nextX + textureplayer.getSize().x;
                if (rightEdge <= l->getSize().x) {
                    cout << "Moved Right" << std::endl;
                    moveRight(x);
                } else {
                    playerX = l->getSize().x - textureplayer.getSize().x;
                    spriteplayer->setPosition({ playerX, 624.f });
                }
            }
            if (keyEvent->code == sf::Keyboard::Key::A)
            {
                float nextX = playerX - moveSpeed * x;
                if (nextX >= 0) {
                    cout << "Moved Left" << std::endl;
                    moveLeft(x);
                } else {
                    playerX = 0;
                    spriteplayer->setPosition({ playerX, 624.f });
                }
            }
        }
        if (event->is<sf::Event::Closed>())
        {
            l->close();
        }
    }
}

void Player::moveRight(float x)
{
    playerX += moveSpeed * x;
    spriteplayer->setPosition({ playerX, 624.f });
}

void Player::moveLeft(float x)
{
    playerX -= moveSpeed * x;
    spriteplayer->setPosition({ playerX, 624.f });
}

float getRandomNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

