#include "Player.h"



Player::Player()
	: jumpSound("jump_super")
{
	playerRec.setSize({ 64,64 });
	playerRec.setPosition(8*64, 400);
	playerRec.setOrigin(playerRec.getSize().x / 2, playerRec.getSize().y / 2);

	if (playerTex.loadFromFile("res/entities/sprite/mario_small.png"))
		playerRec.setTexture(&playerTex);

	loadPlayerAnimation();
	playerRec.setTextureRect(sf::IntRect(0, 0, 7, 11));

	speedMAX = 8;

	gravity = 0.4;
}

void Player::loadPlayerAnimation()
{
	//Idle stage
	playerFrame[0][0] = { 3, 0, 16, 16 };

	//Jump stage
	playerFrame[1][0] = { 86, 0, 16, 16 };

	//moving stage
	playerFrame[0][1] = { 19, 0, 16, 16 };
	playerFrame[1][1] = { 38, 0, 14, 16 };
	playerFrame[2][1] = { 52, 0, 16, 16 };
}

void Player::playerUpdate(float deltaTime)
{
	if(isColliding[1] == true)
	{
		//playerRec.setPosition(playerRec.getPosition().x, playerRec.getPosition().y);
		//playerRec.move(0, -abs(velocity.y) - 1);
		velocity.y = 0;
	}
	if (velocity.y < 7 && isColliding[1] == false)
	{
		velocity.y += gravity;
	}

	if (isColliding[0])
	{
		//std::cout << "Left!" << std::endl;
	}
	if (isColliding[2])
	{
		//std::cout << "Right!" << std::endl;
	}
	if (isColliding[1])
	{
		//std::cout << "bottom!" << std::endl;
	}

	if ((playerRec.getPosition().x - playerRec.getSize().x / 2) <= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2)) //The moving invisible left wall
	{
		playerRec.move(-velocity.x, 0);
		velocity.x = 0;
	}

	playerAnimation();

	frameDelay += deltaTime;

	setPos();

	isColliding[0] = false; //left
	isColliding[1] = false; //bottom
	isColliding[2] = false; //right
	isColliding[3] = false; //top

}

void Player::setPos()
{
	playerRec.move(velocity.x, velocity.y);
}

float Player::Lerp(float x, float y, float z) //acceleration or deceleration
{
	return ((1.0f - z) * x) + (z * y);
}

void Player::playerControl()
{
	//X axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerRec.getPosition().x)
	{
		velocity.x = Lerp(velocity.x, speedMAX, 0.02f); //1) current speed ,2) max speed, 3)acceleration speed

		playerRec.setScale(1, 1); //for turning right
		Angle = 90;

		if (frameStage.x < 2)
		{
			if (frameDelay > 0.5f / abs(velocity.x))
			{
				frameDelay = 0;
				frameStage.x++;
			}
		}
		else
			frameStage.x = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = Lerp(velocity.x, -speedMAX, 0.02f);

		playerRec.setScale(-1, 1); //for turning left
		Angle = -90;

		if (frameStage.x < 2)
		{
			if (frameDelay > 0.5f / abs(velocity.x))
			{
				frameDelay = 0;
				frameStage.x++;
			}
		}
		else
			frameStage.x = 0;
	}
	else
	{
		if (isColliding[1])
		{
			frameStage.x = 0;
			velocity.x = Lerp(velocity.x, 0, 0.1f);

			if (abs(velocity.x) < 0.3f)
				velocity.x = round(velocity.x);
		}
	}

	//Y axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isColliding == false && isJumping == false)
	{
		isJumping = true;
		//jumpSound.playSound(30);
		velocity.y = -15;
	}

	//Sprint
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))   //not sure if this will be in the game
	{
		speedMAX = 15;
	}
	else
	{
		speedMAX = 6;
	}
}

void Player::playerAnimation()
{

	if (velocity.x == 0)
	{
		playerRec.setTextureRect(playerFrame[0][0]); // stand still
	}
	//else if(isColliding[1] || velocity.y == 0)
	//{
	//	playerRec.setTextureRect(playerFrame[frameStage.x][1]); //run
	//}

	
	if (std::round(velocity.y) != 0)
	{
		playerRec.setTextureRect(playerFrame[1][0]); // jump
	}
	
}


