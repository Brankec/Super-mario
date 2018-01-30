#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "EntitySounds/Jump.h"
#include <iostream>
#include <algorithm>
#include "../Util/Camera.h"

#pragma once
class Player
{
public:
	Player();

public:
	void loadPlayerAnimation();
	void playerUpdate(float deltaTime);
	void setPos();
	void playerControl();
	void playerAnimation();

	bool isJumping = false;
	bool isColliding[4] = { false, false, false, false }; //collision goes clock wise 0) is left, 1) is bottom, 2) is right, 3) is top
	bool isFinished = false;

private:
	float Lerp(float x, float y, float z);
	sf::IntRect playerFrame[12][2];
	sf::Vector2u frameStage = { 0,0 };
	float frameDelay = 0;
	Jump jumpSound;

public:
	sf::RectangleShape playerRec;
	sf::Texture playerTex;

	float speedMAX;
	float gravity;
	sf::Vector2f velocity = { 0, 0 };

	int Angle = 90;

};

