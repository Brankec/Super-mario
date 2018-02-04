#include "Goomba.h"

Goomba::Goomba(sf::Vector2f position)
{
	entityRec.setTextureRect(sf::IntRect(0, 16, 16, 16));
	entityRec.setSize({ 48,48 });
	entityRec.setOrigin(entityRec.getSize().x / 2, entityRec.getSize().y / 2);
	entityRec.setPosition(position);
}

void Goomba::loadGumboAnimation()
{
}

void Goomba::GumboUpdate(float deltaTime)
{
	GumboAnimation(deltaTime);
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

	velocity.x = -1.5;

	entityRec.move(velocity.x, velocity.y);
}

sf::Vector2f Goomba::getGoombaPos()
{
	return entityRec.getPosition();
}

void Goomba::GumboAnimation(float deltaTime)
{
}
