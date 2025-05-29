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

//class Money
//	{
//	public:
//		CircleShape gold;
//		Money();
//		float update();
//		float respawn();
//	private:
//		float radius;
//		int maxGoldCount;
//	};

class gameEngine
{
public:
	gameWindow window;
	Player player;

	gameEngine();
	void run();
};

