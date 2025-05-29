#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFMl/System.hpp>
#include <iostream>

using namespace sf;
using namespace std;

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
	void render(RenderWindow*);
	Player(RenderWindow*);
	~Player();
};

class Money
	{
	public:
		Texture texturecoin;
		Sprite* spritecoin;
		float frameDuration = 0.025f;
		float frameTimer = 0.f;
		int frameWidth = 64;
		int frameHeight = 64;
		int totalFrames = 25;
		int currentFrame = 0;
		Money();
		void update(float);
		void rendering(RenderWindow*);
	private:
		int maxGoldCount;
	};

class gameEngine
{
public:
	gameWindow window;
	Player player;
	Money coin;

	gameEngine();
	void run();
};

