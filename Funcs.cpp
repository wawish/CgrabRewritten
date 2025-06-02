#include "Funcs.h"
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

void randomNumber()
{
    srand(time(NULL));
}

gameEngine::gameEngine()
    : window(), player(window.window)
{
    activeCoins = 1; //coins currently onscreen
    activeBombs = 0; //bombs currently onscreen
    activePowerups = 0;
    lastcoinThreshold = 0; //stores the current threshold for coins
    lastbombThreshold = 0; //stores the current threshold for bombs
    activePowerups = 0;
}

void gameEngine::clamp()
{
    if (activeCoins > MAX_COINS) activeCoins = MAX_COINS;
    if (activeBombs > MAX_BOMBS) activeBombs = MAX_BOMBS;
    if (activePowerups > MAX_POWERUPS) activePowerups = MAX_POWERUPS;
    if (activeBombs < 0) activeBombs = 0;
    if (activePowerups < 0) activePowerups = 0;
}

void gameEngine::spawncoins(float x)
{
    clamp();
    for (int i = 0; i < activeCoins; i++) { //falling coins
        coin[i].updatecoin(x);
        coin[i].rendercoin(window.window);
    }
}

void gameEngine::spawnbombs(float x)
{
    clamp();
    for (int i = 0; i < activeBombs && i < MAX_BOMBS; i++) { //falling bombs
        bomb[i].updatebomb(x);
        bomb[i].renderbomb(window.window);
    }
}

void gameEngine::spawnpowerups(float x)
{
    clamp();
    for (int i = 0; i < activePowerups; i++) { //falling powerup
        power[i].updatePowerup(x);
        power[i].renderPowerup(window.window);
    }
}

void gameEngine::collisionchecker()
{
    clamp();
    for (int i = 0; i < activeCoins; i++) { //collision checker for coins
        if (coin[i].spritecoin->getGlobalBounds().findIntersection(player.spriteplayer->getGlobalBounds())) {
            player.score += 100 * player.scoremultiplier;
            if (rand() % 10 + 1 == 1 && activeBombs < MAX_BOMBS)activeBombs += 1;
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
            bomb[i].respawnbomb(0);
        }
    }
    for (int i = 0; i < activePowerups; i++) { //collision checker for bombs
        if (power[i].randomPowerSprite->getGlobalBounds().findIntersection(player.spriteplayer->getGlobalBounds())) {
            coin[i].coinSounds->play();
            int chosen = rand() % 30 + 1;
            
            switch (chosen)
            {
            case 1:case 2:case 3:case 4: case 5:
                cout << "1 Health Added!" << endl;
                player.health += 1;
                break;
            case 6:case 7:case 8:case 9: case 10:
                cout << "Bombs are slowed!" << endl;
                break;
            case 11:
                cout << player.scoremultiplier + 1 << " Multiplier! " << endl;
                player.scoremultiplier += 1;
                break;
            case 12:
                cout << "Clearing Bombs..." << endl;
                activeBombs = 0;
                break;
            case 13:case 14: case 15: case 16: case 17:
                cout << "Unlucky! Added 1 Bomb" << endl;
                activeBombs += 1;
                break;
            default:
                cout << "Nothing! (Be happy)" << endl;
                break;
            }

            power[i].respawnPowerup();
        }
    }

}

void gameEngine::thresholdchecker()
{
    clamp();
    int cointhreshold = player.score / 500; //coin ramp up
    if (cointhreshold > lastcoinThreshold && activeCoins < 10) {
        cout << "THRESHOLD REACHED! Amount of Coins: " << activeCoins << " Score: " << player.score << endl;
        if(activeCoins < MAX_COINS) activeCoins++;
        for (int i = 0; i < activeCoins; ++i) {
            coin[i].coinFallspeed += 50.f;
        }
        lastcoinThreshold = cointhreshold;
    }


    int bombthreshold = player.score / 1000; //bomb ramp up
    int oldActiveBombs = activeBombs;
    if (bombthreshold > lastbombThreshold && activeBombs < 25) {
        cout << "THRESHOLD REACHED! Amount of Bombs: " << activeBombs << endl;
        if (activeBombs < MAX_BOMBS) activeBombs++;
        for (int i = 0; i < activeBombs; ++i) {
            bomb[i].bombFallspeed += 5.f;
            // Only respawn new bombs
            if (i >= oldActiveBombs) {
                bomb[i].respawnbomb(0);
            }
        }
        lastbombThreshold = bombthreshold;
    }

    int powerthreshold = player.score / 1500; //Power ramp up
    if (powerthreshold > lastpowerThreshold && activePowerups < 5) {
        cout << "THRESHOLD REACHED! Amount of Powerups: " << activePowerups << endl;
        if (activePowerups < MAX_POWERUPS) activePowerups++;
        for (int i = 0; i < activePowerups; ++i) {
            power[i].powerupFallspeed += 25.f;
        }
        lastpowerThreshold = powerthreshold;
    }

    
}

void gameEngine::run()
{
    clamp();
    sf::Clock clock;
    while (window.window->isOpen()) {
        if (player.health <= 0) //this is temporary
        {
            window.window->close();
        }
        float delta = clock.restart().asSeconds(); //delta time var
        window.window->clear(); //clears the window
        window.window->draw(*window.spritebg);
        player.checkEvent(window.window, delta); //keystroke checker
        player.renderplayer(window.window); //draws the player
        spawncoins(delta);
        spawnbombs(delta);
        spawnpowerups(delta);
        collisionchecker();
        thresholdchecker();
        

        window.window->display(); //draws the screen
    }
}

gameWindow::gameWindow()
{
    window = new RenderWindow(VideoMode({ 1920, 1080 }), "Cash Grab!"); //initializes the window
    window->setFramerateLimit(60);
    if (!texturebg.loadFromFile("Sprites/bg/testbg.png")) //checks if it load properly
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spritebg = new Sprite(texturebg);
    spritebg->setPosition({ 0.f, 0.f });

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
    scoremultiplier = 1;
    score = 0;
    health = 5;
    if (!textureplayer.loadFromFile("Sprites/player/playerwalk.png")) //checks if it load properly
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spriteplayer = new Sprite(textureplayer); //init for player sprite
    spriteplayer->setTextureRect(IntRect({ 0, 0 }, { 24, 32 })); //sets the sprite as a rectangle
    spriteplayer->setScale({ 3.0f, 3.0f }); //triples the size
    moveSpeed = 700.f; //init for player ms
    playerX = WINDOW_WIDTH / 2; //init for startpos
    spriteplayer->setPosition({ playerX, PLAY_OFFSET_Y + PLAY_HEIGHT - spriteplayer->getGlobalBounds().size.y });

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
    float minX = PLAY_OFFSET_X;
    float maxX = PLAY_OFFSET_X + PLAY_WIDTH - spriteWidth;
    if (playerX > maxX) {
        playerX = maxX;
    }
    spriteplayer->setPosition({ playerX, PLAY_OFFSET_Y + PLAY_HEIGHT - spriteplayer->getGlobalBounds().size.y });
}

void Player::moveLeft(float x)
{
    playerX -= moveSpeed * x;
    float minX = PLAY_OFFSET_X;
    if (playerX < minX) {
        playerX = minX;
    }
    spriteplayer->setPosition({ playerX, PLAY_OFFSET_Y + PLAY_HEIGHT - spriteplayer->getGlobalBounds().size.y });
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
    randomValX = PLAY_OFFSET_X + (PLAY_WIDTH - 32) * getRandomNumber();
    float y = PLAY_OFFSET_Y;
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

    if (spritecoin->getPosition().y > PLAY_OFFSET_Y + PLAY_HEIGHT - spritecoin->getGlobalBounds().size.y) {
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
    bombAcceleration = 1.f;
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
    respawnbomb(0);
}

void Bomb::respawnbomb(float y) {
    randomValX = PLAY_OFFSET_X + (PLAY_WIDTH - 32) * getRandomNumber();
    spritebomb->setPosition({ randomValX, PLAY_OFFSET_Y + y });
    fallSpeed = bombFallspeed + getRandomNumber() * 100.f * bombAcceleration;
}

void Bomb::updatebomb(float x) {
    frameTimer += x;

    if (frameTimer >= frameDuration) {
        currentFrame = (currentFrame + 1) % totalFrames;
        spritebomb->setTextureRect(IntRect({ currentFrame * frameWidth, 0 }, { frameWidth, frameHeight }));
        frameTimer = 0.f;
    }

    auto Xpos = spritebomb->getPosition().x;
    auto Ypos = spritebomb->getPosition().y;
    spritebomb->setPosition({ Xpos, Ypos + fallSpeed * x * bombAcceleration });

    if (spritebomb->getPosition().y > PLAY_OFFSET_Y + PLAY_HEIGHT - spritebomb->getGlobalBounds().size.y) {
        respawnbomb(0);
    }
}

void Bomb::renderbomb(RenderWindow* l)
{
    l->draw(*spritebomb);
}

Powerups::Powerups()
{
    powerupFallspeed = 200.f;
    if (!PowerTexture.loadFromFile("Sprites/powerups/powerups.png")) //checks if it load properly
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    randomPowerSprite = new Sprite(PowerTexture);
    randomPowerSprite->setTextureRect(IntRect({ 1009, 1 }, { 47, 47 }));
    randomPowerSprite->setScale({ 1.f, 1.f });
    respawnPowerup();

}

void Powerups::respawnPowerup()
{
    randomValue = PLAY_OFFSET_X + (PLAY_WIDTH - 32) * getRandomNumber();
    float y = PLAY_OFFSET_Y;
    randomPowerSprite->setPosition({ randomValue, y });
    fallSpeed = powerupFallspeed + getRandomNumber() * 100.f;
}

void Powerups::updatePowerup(float y)
{
    auto Xpos = randomPowerSprite->getPosition().x;
    auto Ypos = randomPowerSprite->getPosition().y;
    randomPowerSprite->setPosition({ Xpos, Ypos + fallSpeed * y });

    if (randomPowerSprite->getPosition().y > PLAY_OFFSET_Y + PLAY_HEIGHT - randomPowerSprite->getGlobalBounds().size.y && rand() % 8 + 1 >= 4) {
        respawnPowerup();
    }

}

void Powerups::renderPowerup(RenderWindow* l)
{
    l->draw(*randomPowerSprite);
}