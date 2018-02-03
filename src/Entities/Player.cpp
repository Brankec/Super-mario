#include "Player.h"



Player::Player()
{
	playerRec.setSize({ 64,64 });
	playerRec.setPosition(8*64, 800);
	playerRec.setOrigin(playerRec.getSize().x / 2, playerRec.getSize().y / 2);

	if (playerTex.loadFromFile("res/entities/sprite/mario_small.png"))
		playerRec.setTexture(&playerTex);

	loadPlayerAnimation();
	playerRec.setTextureRect(sf::IntRect(0, 0, 7, 11));

	speedMAX = 2;

	gravity = 0.3;

	isBig = true;
}

void Player::loadPlayerAnimation()
{
	//Idle stage
	playerFrame[0][0] = { 3, 0, 16, 16 };

	//Jump stage
	playerFrame[1][0] = { 86, 0, 16, 16 };

	//moving stage
	playerFrame[0][1] = { 19, 0, 16, 16 };
	playerFrame[1][1] = { 36, 0, 16, 16 };
	playerFrame[2][1] = { 52, 0, 16, 16 };
}

void Player::playerUpdate(float deltaTime)
{
	jumpSound.update();
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

	frameDelay += deltaTime;

	if (isMoving)
	{
		animationSpeed = Lerp(animationSpeed, speedMAX, 0.02f);
	}
	else
	{
		animationSpeed = Lerp(animationSpeed, 0, 0.01f);
	}

	if (frameStage.x < 3)
	{
		if (velocity.x != 0 && frameDelay > 0.2f / animationSpeed)
		{
			frameDelay = 0;
			frameStage.x++;
		}
	}
	else
	{
		frameStage.x = 0;
	}

	playerAnimation();

	if ((playerRec.getPosition().x - playerRec.getSize().x / 2 + 15) <= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2)) //The moving invisible left wall
	{
		playerRec.setPosition((Camera::getView().getCenter().x - Camera::getView().getSize().x / 2) + 0.01 + playerRec.getSize().x / 2 - 15, playerRec.getPosition().y);
		velocity.x = 0;
	}

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

		isMoving = true;

		if(isOnGround)
		playerRec.setScale(1, 1); //for turning right
		Angle = 90;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = Lerp(velocity.x, -speedMAX, 0.02f);

		isMoving = true;

		if(isOnGround)
		playerRec.setScale(-1, 1); //for turning left
		Angle = -90;
	}
	else
	{
		isMoving = false;
		if (isOnGround)
		{
			velocity.x = Lerp(velocity.x, 0, 0.03f);

			if (abs(velocity.x) < 0.3f)
				velocity.x = round(velocity.x);
		}
	}

	//Y axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround == true && isJumping == false)
	{
		isJumping = true;
		jumpSound.playSound(30);
		velocity.y = -13;
	}

	//Sprint
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))   //only for bugtesting
	{
		speedMAX = 6;
	}
	else
	{
		speedMAX = 4;
	}
}

void Player::playerAnimation()
{
	if (velocity.x == 0)
	{
		playerRec.setTextureRect(playerFrame[0][0]); // stand still
	}
	else if(frameStage.x < 3)
	{
		playerRec.setTextureRect(playerFrame[frameStage.x][1]); //run
	}

	
	if (velocity.y != 0 && isJumping)
	{
		playerRec.setTextureRect(playerFrame[1][0]); // jump
	}
	
}


