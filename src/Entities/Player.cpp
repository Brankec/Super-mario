#include "Player.h"



Player::Player()
	: jumpSound("jump_super")
{
	entityRec.setSize({ 64,64 });
	entityRec.setPosition(30, 800);
	entityRec.setOrigin(entityRec.getSize().x / 2, entityRec.getSize().y / 2);
	loadTextureToRec();
	loadPlayerAnimation();
	entityRec.setTextureRect(sf::IntRect(0, 0, 7, 11));

	speedMAX = 8;
	stamina = 100;

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
	if (velocity.y != 0) //this is only temporary. atm isOnGround is true whenever I touch anything at any side
	{
		isOnGround = false;
	}

	if (velocity.y < 7 && isOnGround == false)
	{
		velocity.y += gravity;
	}
	else if (isOnGround == true)
	{
		isOnGround = false;
	}


	if ((entityRec.getPosition().x - entityRec.getSize().x / 2) <= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2))
	{
		entityRec.move(-velocity.x, 0);
		velocity.x = 0;
	}

	playerAnimation();

	frameDelay += deltaTime;
}

void Player::setPos()
{
	entityRec.move(velocity.x, velocity.y);
}

float Player::Lerp(float x, float y, float z) //acceleration or deceleration
{
	return ((1.0f - z) * x) + (z * y);
}

void Player::playerControl()
{
	//X axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && entityRec.getPosition().x)
	{
		velocity.x = Lerp(velocity.x, speedMAX, 0.02f); //1) current speed ,2) max speed, 3)acceleration speed

		entityRec.setScale(1, 1); //for turning right
		Angle = 90;

		if (frameStage.x < 3)
		{
			if (frameDelay > 0.3f / abs(velocity.x))
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

		entityRec.setScale(-1, 1); //for turning left
		Angle = -90;

		if (frameStage.x < 3)
		{
			if (frameDelay > 0.3f / abs(velocity.x))
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
		if (isOnGround)
		{
			frameStage.x = 0;
			velocity.x = Lerp(velocity.x, 0, 0.1f);

			if (abs(velocity.x) < 0.3f)
				velocity.x = round(velocity.x);
		}
	}

	//Y axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround && velocity.y == 0) //last parameter is only temp until isOnGround works properly
	{
		jumpSound.playSound(30);
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
		entityRec.setTextureRect(playerFrame[0][0]); // stand still
	}
	else if(isOnGround || velocity.y == 0)
	{
		entityRec.setTextureRect(playerFrame[frameStage.x][1]); //run
	}

	
	if (std::round(velocity.y) != 0)
	{
		entityRec.setTextureRect(playerFrame[1][0]); // jump
	}
	
}


