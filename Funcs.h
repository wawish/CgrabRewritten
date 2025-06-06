#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFMl/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>

#define PLAY_WIDTH 1280
#define PLAY_HEIGHT 720
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define PLAY_OFFSET_X ((WINDOW_WIDTH - PLAY_WIDTH) / 2)
#define PLAY_OFFSET_Y ((WINDOW_HEIGHT - PLAY_HEIGHT) / 2)

using namespace sf;
using namespace std;

class gameEngine;

class gameOver
{
public:
	gameOver();
	Texture textureOverTray, textureQuitButton, textureRetryButton;
	Sprite* spriteOverTray, *spriteQuitButton, *spriteRetryButton;
	void draw(RenderWindow* l);

	void checkEvent(RenderWindow* l, gameEngine* engine);

	Font gameoverFont;
	Text *lostHeader;
	SoundBuffer loseBuffer;
	Sound* loseSound;
	SoundBuffer hoverBuffer;
	Sound* hoverSound;
	bool wasOverRetry;
	bool wasOverQuit;
	SoundBuffer clickBuffer;
	Sound* clickSound;
};

class gameWindow
{
public:
	RenderWindow* window;
	gameWindow(RenderWindow* window);
	~gameWindow();
	Texture texturebg;
	Sprite* spritebg;
	Font gameFont;
	Text *T_health, *T_score, *T_bombs, *T_coins, *T_multiplier, *T_status;
};

class Player
{
private:
	float frameDuration;
	float frameTimer;
	int frameWidth;
	int frameHeight;
	int totalFrames;
	int currentFrame;
public:
	float moveSpeed;
	float playerX;
	Player(RenderWindow*);
	Texture textureplayer, textureheart;
	Sprite* spriteplayer, *spriteheart;
	void checkEvent(RenderWindow*, float);
	void moveRight(float);
	void moveLeft(float);
	void updateplayer(float);
	void renderplayer(RenderWindow*);
	int score;
	int scoremultiplier;
	int health;
	static const int MAX_HEALTH = 5;
	~Player();
};

class Money
{
private:
	float frameDuration;
	float frameTimer;
	int frameWidth;
	int frameHeight;
	int totalFrames;
	int currentFrame;
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
};

class Bomb
{
private:
	float frameDuration;
	float frameTimer;
	int frameWidth;
	int frameHeight;
	int totalFrames;
	int currentFrame;
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
};

class Powerups
{
private:
	vector<float> frameDurations;
	//float frameDuration;
	float frameTimer;
	int frameWidth;
	int frameHeight;
	int totalFrames;
	int currentFrame;
public:
	Powerups();
	SoundBuffer powerupBuffer;
	Sound* powerupSounds;
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
private:
	static const int NUM_PANELS = 10;
	Texture pageTextures[NUM_PANELS];
	Sprite *pageSprites[NUM_PANELS];

public:
	enum class GameState { Playing, GameOver, Paused, Cutscene };
	GameState state = GameState::Playing;

	explicit gameEngine(RenderWindow* window);
	static const int MAX_COINS = 5;
	static const int MAX_BOMBS = 5;
	static const int MAX_POWERUPS = 2;
	// In class gameEngine (public or private section)
	float coinThresholdTimer = 0.f;
	float bombThresholdTimer = 0.f;
	float powerupThresholdTimer = 0.f;

	float currentCoinSpeed;
	float currentBombSpeed;

	float coinThresholdInterval;
	float bombThresholdInterval;   
	float powerupThresholdInterval;

	gameOver gameover;
	gameWindow window;
	Player player;
	Money coin[MAX_COINS];
	Bomb bomb[MAX_BOMBS];
	Powerups power[MAX_POWERUPS];
	String status;

	int activeCoins;
	int activeBombs;
	int activePowerups;
	bool bombsSlowed;
	float slowBombTimer;
	float bombSlowFactor;
	Music playBGM;


	void run();
	void updatetext();
	void spawnbombs(float);
	void spawncoins(float);
	void spawnpowerups(float);
	void collisionchecker();
	void thresholdchecker(float);
	void bombSlowchecker(float);
	void clamp();
	void reset();
	void playCutscene();
};