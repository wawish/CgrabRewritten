#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFMl/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#define PLAY_WIDTH 1280
#define PLAY_HEIGHT 720
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define PLAY_OFFSET_X ((WINDOW_WIDTH - PLAY_WIDTH) / 2)
#define PLAY_OFFSET_Y ((WINDOW_HEIGHT - PLAY_HEIGHT) / 2)

using namespace sf;
using namespace std;

class gameMenu
{
public:
	/*Font mainfont;*/
	Sprite* spritebuttonPlay, spritebuttonQuit, spritebuttonSettings, spriteLogo;
	Sound onClick, onHover;
	Music* bgmMusic;
};

class gameWindow
{
	
public:
	RenderWindow* window;
	gameWindow();
	~gameWindow();	
	Texture texturebg;
	Sprite* spritebg;
	Font gameFont;
	Text *T_health, *T_score, *T_bombs, *T_coins, *T_multiplier, *T_status;
};

class Player
{
private:
	float playerX;
	float moveSpeed;
	float frameDuration;
	float frameTimer;
	int frameWidth;
	int frameHeight;
	int totalFrames;
	int currentFrame;
public:
	Player(RenderWindow*);
	Texture textureplayer;
	Sprite* spriteplayer;
	void checkEvent(RenderWindow*, float);
	void moveRight(float);
	void moveLeft(float);
	void renderplayer(RenderWindow*);
	int score;
	int scoremultiplier;
	int health;
	~Player();
};

class Money
	{
	public:
		Money();
		SoundBuffer takeCoin;
		Sound* coinSounds;
		Texture texturecoin;
		Sprite* spritecoin;
		float randomValX;
		float coinFallspeed;
		float fallSpeed;
		void respawncoin();
		void updatecoin(float);
		void rendercoin(RenderWindow*);
	private:
		float frameDuration;
		float frameTimer;
		int frameWidth;
		int frameHeight;
		int totalFrames;
		int currentFrame;
};

class Bomb
{
public:
	Bomb();
	SoundBuffer takeBomb;
	Sound* bombSounds;
	Texture texturebomb;
	Sprite* spritebomb;
	float randomValX;
	float bombFallspeed;
	float fallSpeed;
	float bombAcceleration;
	void respawnbomb(float);
	void updatebomb(float);
	void renderbomb(RenderWindow*);
private:
	float frameDuration;
	float frameTimer;
	int frameWidth;
	int frameHeight;
	int totalFrames;
	int currentFrame;

};

class Powerups
{
public:
	Powerups();
	float randomValue;
	float powerupFallspeed;
	float fallSpeed;
	Texture PowerTexture;
	Sprite* randomPowerSprite;
	void respawnPowerup();
	void updatePowerup(float);
	void renderPowerup(RenderWindow*);

};

class gameEngine
{
public:
	gameEngine();
	static const int MAX_COINS = 15;
	static const int MAX_BOMBS = 25;
	static const int MAX_POWERUPS = 3;

	gameWindow window;
	Player player;
	Money coin[MAX_COINS];
	Bomb bomb[MAX_BOMBS];
	Powerups power[MAX_POWERUPS];
	String status;
	int activeCoins;
	int activeBombs;
	int activePowerups;
	int lastcoinThreshold;
	int lastbombThreshold;
	int lastpowerThreshold;

	
	void run();
	void updatetext();
	void spawnbombs(float);
	void spawncoins(float);
	void spawnpowerups(float);
	void collisionchecker();
	void thresholdchecker();
	void clamp();
};


