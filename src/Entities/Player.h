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
	void playerControl();
	void playerAnimation();

	bool isJumping = false;
	bool isOnGround = false;
	bool isFinished = false;
	bool isMoving = false;

	bool isBig = false;

private:
	float Lerp(float x, float y, float z);
	sf::IntRect playerFrame[2][5];
	sf::Vector2u frameStage = { 0,0 };
	float frameDelay = 0;
	Jump jumpSound;

	sf::Vector2f playerSize = { 64,64 };

	float animationSpeed = 0;

public:
	sf::RectangleShape playerRec;
	sf::Texture playerTex;

	float speedMAX;
	float gravity = 0.3;
	sf::Vector2f velocity = { 0, 0 };

	int Angle = 90;

};

