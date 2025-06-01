#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFMl/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class gameMenu
{
public:
	Font mainfont;
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
};

class Player
{
private:
	float length, width;
	float playerX;
	float moveSpeed;
	
public:
	Texture textureplayer;
	Sprite* spriteplayer;
	void checkEvent(RenderWindow*, float);
	void moveRight(float);
	void moveLeft(float);
	void renderplayer(RenderWindow*);
	Player(RenderWindow*);
	int score;
	int scoremultiplier;
	int health;
	~Player();
};

class Money
	{
	public:
		SoundBuffer takeCoin;
		Sound* coinSounds;
		Texture texturecoin;
		Sprite* spritecoin;
		float randomValX;
		float coinFallspeed;
		float fallSpeed;
		void respawncoin();
		Money();
		void updatecoin(float);
		void rendercoin(RenderWindow*);
	private:
		int maxGoldCount;
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
	SoundBuffer takeBomb;
	Sound* bombSounds;
	Texture texturebomb;
	Sprite* spritebomb;
	float randomValX;
	float bombFallspeed;
	float fallSpeed;
	void respawnbomb();
	Bomb();
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
	gameWindow window;
	Player player;
	Money coin[10];
	Bomb bomb[25];
	Powerups power[5];
	int activeCoins;
	int activeBombs;
	int activePowerups;
	int lastcoinThreshold;
	int lastbombThreshold;
	int lastpowerThreshold;

	gameEngine();
	void run();
	void spawnbombs(float);
	void spawncoins(float);
	void spawnpowerups(float);
	void collisionchecker();
	void thresholdchecker();
};


