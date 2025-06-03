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
    lastpowerThreshold = 0;
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
            status = "hit! " + to_string(player.score);
            coin[i].respawncoin();
        }
    }
    for (int i = 0; i < activeBombs; i++) { //collision checker for bombs
        if (bomb[i].spritebomb->getGlobalBounds().findIntersection(player.spriteplayer->getGlobalBounds())) {
            player.health -= 1;
            bomb[i].bombSounds->play();
            cout << "explode! " << player.health << endl;
            status = "explode! " + to_string(player.health);
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
                status = "1 Health Added!";
                player.health += 1;
                break;
            case 6:case 7:case 8:case 9: case 10:
                cout << "Bombs are slowed!" << endl;
                status = "Bombs are slowed!";
                break;
            case 11:
                cout << player.scoremultiplier + 1 << " Multiplier! " << endl;
                status = to_string(player.scoremultiplier + 1) + " Multiplier!";
                player.scoremultiplier += 1;
                break;
            case 12:
                cout << "Clearing Bombs..." << endl;
                status = "Clearing Bombs...";
                activeBombs = 0;
                break;
            case 13:case 14: case 15: case 16: case 17:
                cout << "Unlucky! Added 1 Bomb" << endl;
                status = "Unlucky! Added 1 Bomb";
                activeBombs += 1;
                break;
            default:
                cout << "Nothing! (Be happy)" << endl;
                status = "Nothing! (Be happy)";
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

void gameEngine::updatetext()
{
    window.T_health->setString("Health: " + to_string(player.health));
    window.T_score->setString("Score: " + to_string(player.score));
    window.T_bombs->setString("Bombs: " + to_string(activeBombs));
    window.T_coins->setString("Coins: " + to_string(activeCoins));
    window.T_multiplier->setString("Multiplier: x" + to_string(player.scoremultiplier));
    window.T_status->setString(status);

    window.window->draw(*window.T_health);
    window.window->draw(*window.T_score);
    window.window->draw(*window.T_bombs);
    window.window->draw(*window.T_coins);
    window.window->draw(*window.T_multiplier);
    window.window->draw(*window.T_status);
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
        updatetext();
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
    if (!gameFont.openFromFile("Sprites/Fonts/ka1.ttf"))
    {
        cout << "ERROR LOADING FONT" << endl;
    }
    T_health = new Text(gameFont);
    T_score = new Text(gameFont);
    T_bombs = new Text(gameFont);
    T_coins = new Text(gameFont);
    T_multiplier = new Text(gameFont);
    T_status = new Text(gameFont);

    T_health->setCharacterSize(32);
    T_score->setCharacterSize(32);
    T_bombs->setCharacterSize(32);
    T_coins->setCharacterSize(32);
    T_multiplier->setCharacterSize(32);
    T_status->setCharacterSize(24);
    
    T_health->setPosition({ 0, PLAY_OFFSET_Y + 0.f });
    T_score->setPosition({ 0, PLAY_OFFSET_Y + 40.f });
    T_bombs->setPosition({ 0, PLAY_OFFSET_Y + 80.f });
    T_coins->setPosition({ 0, PLAY_OFFSET_Y + 120.f });
    T_multiplier->setPosition({ 0, PLAY_OFFSET_Y + 160.f });
    T_status->setPosition({ 0, PLAY_OFFSET_Y + 200.f });

    T_health->setFillColor({ 0, 0, 0 });
    T_score->setFillColor({ 0, 0, 0 });
    T_bombs->setFillColor({ 0, 0, 0 });
    T_coins->setFillColor({ 0, 0, 0 });
    T_multiplier->setFillColor({ 0, 0, 0 });
    T_status->setFillColor({ 0, 0, 0 });
    
    
    
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
    delete spritebg;
    delete T_health;
    delete T_coins;
    delete T_bombs;
    delete T_status;
    delete T_score;
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
    if (!textureplayer.loadFromFile("Sprites/player/player.png")) //checks if it load properly
    {
        cout << "ERROR LOADING SPRITE" << endl;
    }
    spriteplayer = new Sprite(textureplayer); //init for player sprite
    spriteplayer->setTextureRect(IntRect({ 0, 0 }, { 64, 64 })); //sets the sprite as a rectangle
	spriteplayer->setOrigin({ 32.f, 0.f }); //sets the origin to the center of the sprite
    spriteplayer->setScale({ 2.5f, 2.5f }); //triples the size
    moveSpeed = 700.f; //init for player ms
    frameDuration = 0.025f;
    frameTimer = 0.f;
    frameWidth = 64;
    frameHeight = 64;
    totalFrames = 4;
    currentFrame = 0;
    
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
    spriteplayer->setScale({ -2.5f, 2.5f });
    playerX += moveSpeed * x;
    float spriteWidth = spriteplayer->getGlobalBounds().size.x;
    float minX = PLAY_OFFSET_X;
    float maxX = PLAY_OFFSET_X + PLAY_WIDTH - (spriteWidth/2) ;
    if (playerX > maxX) {
        playerX = maxX;
    }
    spriteplayer->setPosition({ playerX, PLAY_OFFSET_Y + PLAY_HEIGHT - spriteplayer->getGlobalBounds().size.y });
}

void Player::moveLeft(float x)
{
    spriteplayer->setScale({ 2.5f, 2.5f });
    playerX -= moveSpeed * x;
    float spriteWidth = spriteplayer->getGlobalBounds().size.x;
    float minX = PLAY_OFFSET_X + (spriteWidth/2);
    if (playerX < minX){
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