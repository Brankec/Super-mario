#include "Player.h"



Player::Player()
	: walkingSound("footstep")
{
	entityRec.setSize({ 25,25 });
	entityRec.setPosition(900, 150);
	entityRec.setOrigin(entityRec.getSize().x / 2, entityRec.getSize().y / 2);
	loadTextureToRec();
	loadPlayerAnimation();
	entityRec.setTextureRect(sf::IntRect(0, 0, 7, 11));

	speedMAX = 3;
	stamina = 100;

	//gravity = 0.4;
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
	setPos();

	if ((int)velocity.y != 0)
	{
		isOnGround = false;
	}

	walkingSound.update(deltaTime);

	playerAnimation();
	frameDelay += deltaTime;
}

void Player::setPos()
{

	if (velocity.y < 20)
		//velocity.y += gravity;

	entityRec.move(velocity.x, velocity.y);
}

float Player::Lerp(float x, float y, float z) //acceleration or deceleration
{
	return ((1.0f - z) * x) + (z * y);
}

void Player::playerControl()
{
	//X axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = Lerp(velocity.x, speedMAX, 0.05f); //1) current speed ,2) max speed, 3)acceleration speed

		entityRec.setScale(1, 1); //for turning right
		Angle = 90;

		if (frameStage.x < 3)
		{
			if (frameDelay > 0.25f / abs(velocity.x))
			{
				frameDelay = 0;

				if (isOnGround &&
					(frameStage.x == 0 ||
						frameStage.x == 5))
					walkingSound.playSound(20);

				frameStage.x++;
			}
		}
		else
			frameStage.x = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = Lerp(velocity.x, -speedMAX, 0.05f);

		entityRec.setScale(-1, 1); //for turning left
		Angle = -90;

		if (frameStage.x < 3)
		{
			if (frameDelay > 0.25f / abs(velocity.x))
			{
				frameDelay = 0;

				if (isOnGround &&
					(frameStage.x == 0 ||
						frameStage.x == 5))
					walkingSound.playSound(20);

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isJumping == false)
	{
		isJumping = true;
		velocity.y = -16;
	}

	//Sprint
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && isStaminaFull)   //not sure if this will be in the game
	{
		if (stamina < 1)
			isStaminaFull = false;

		stamina -= 1;
		speedMAX = 6;
	}
	else
	{
		if (stamina >= 100)
			isStaminaFull = true;

		stamina += 0.3;
		speedMAX = 3;
	}

	//fire
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
	}*/
}

void Player::playerAnimation()
{

	if (velocity.x == 0)
	{
		entityRec.setTextureRect(playerFrame[0][0]); // stand still
	}
	else if(isOnGround)
	{
		entityRec.setTextureRect(playerFrame[frameStage.x][1]); //run
	}

	
	if (velocity.y < 0)
	{
		entityRec.setTextureRect(playerFrame[1][0]); // jump
	}

	else if (abs(velocity.y) > 0.81)
	{
		entityRec.setTextureRect(playerFrame[0][0]); // fall
	}
	
}


