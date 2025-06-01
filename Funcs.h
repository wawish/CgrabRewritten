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

class gameEngine
{
public:
	gameWindow window;
	Player player;
	Money coin[10];
	Bomb bomb[25];
	int activeCoins;
	int activeBombs;
	int lastcoinThreshold;
	int lastbombThreshold;

	gameEngine();
	void run();
	/*void spawnbombs();
	void spawncoins();
	void scoremultiplier();
	void clearbombs();
	void gainhealth();
	void slowbombs();*/
};


